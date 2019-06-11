/*
********************************************************************************************
* Copyright (c) 2019 MINTROBOT Co., Ltd.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the <MINTROBOT Co, Ltd.> nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************************
**/

#include "WorkerConnectionHandler.h"

//--- Constructor ---//
WorkerConnectionHandler::WorkerConnectionHandler(QObject *parent) : QObject (parent) {

}

WorkerConnectionHandler::~WorkerConnectionHandler() {

}


//--- Public ---//
void WorkerConnectionHandler::setSocket(BlockingTCPSocket* pSocketCommand, BlockingTCPSocket* pSocketStatus) {
    __pSocketCommand = pSocketCommand;
    __pSocketStatus = pSocketStatus;
}

void WorkerConnectionHandler::setSocketControlThread(QThread* pThreadSocketController) {
    __pThreadSocketController = pThreadSocketController;
}

void WorkerConnectionHandler::receiveSocketFromSocketController() {
    connect(__pSocketCommand, SIGNAL(disconnected()), this, SLOT(slotResetConnection()));
    connect(__pSocketStatus, SIGNAL(disconnected()), this, SLOT(slotResetConnection()));
    __resetConnection();
    __flagAuthority = true;
    setActivation(true);
}

void WorkerConnectionHandler::tossSocketToSocketController() {
    disconnect(__pSocketCommand);
    disconnect(__pSocketStatus);
    __pSocketCommand->setParent(nullptr);
    __pSocketStatus->setParent(nullptr);
    __pSocketCommand->moveToThread(__pThreadSocketController);
    __pSocketStatus->moveToThread(__pThreadSocketController);
    __flagAuthority = false;
    setActivation(false);
}

void WorkerConnectionHandler::changeIPAddress(QString IPAddress) {

    // Lock Operation Setting
    __mutexOperation.lock();
    __IPAddress = IPAddress;

    if (__flagConnectionCommandServer) {
        while(__pSocketCommand->state() == QTcpSocket::ConnectedState) {
            __pSocketCommand->waitForDisconnected(__connectionWaitTimeout);
        }
        __flagConnectionCommandServer = false;
    }

    if (__flagConnectionStatusServer) {
        while(__pSocketStatus->state() == QTcpSocket::ConnectedState) {
            __pSocketStatus->waitForDisconnected(__connectionWaitTimeout);
        }
        __flagConnectionStatusServer = false;
    }

    __flagEstablishedConnection = false;
    // Unlock Operation Setting
    __mutexOperation.unlock();
}

void WorkerConnectionHandler::setActivation(bool activation) {
    __mutexOperation.lock();
    if (activation && __flagAuthority) {
        __flagOperation = true;
    }
    else {
        __flagOperation = false;
    }
    __mutexOperation.unlock();
}



//--- Private ---//
void WorkerConnectionHandler::__resetConnection() {
    __pSocketCommand->disconnect();
    __pSocketStatus->disconnect();
    __pSocketCommand->disconnectFromHost();
    __pSocketStatus->disconnectFromHost();
    __pSocketCommand->waitForDisconnected();
    __pSocketStatus->waitForDisconnected();
    __flagConnectionCommandServer = false;
    __flagConnectionStatusServer = false;
    __flagEstablishedConnection = false;
}


bool WorkerConnectionHandler::__handShake() {

    char packetHandShake[4] = {0x77, 0x02, 0x00, 0x01};
    char bufferCommand[10];
    char bufferStatus[10];
    char magicByteCommand;
    char magicByteStatus;

    for (int i =0; i < 10; i++) {
        bufferCommand[i] = 0;
        bufferStatus[i] = 0;
    }

    // Send handshake start packet to each server
    if (!__pSocketCommand->blockingWrite(packetHandShake, sizeof(packetHandShake))) {
        qWarning() << "Failed to handshake with command server - Handshake packet transmission";
        return false;
    }

    if (!__pSocketStatus->blockingWrite(packetHandShake, sizeof(packetHandShake))) {
        qWarning() << "Failed to handshake with status server - Handshake packet transmission";
        return false;
    }

    // Read response packet from each server
    if (!__pSocketCommand->blockingRead(bufferCommand, 4)) {

    }
    if (bufferCommand[0] != 0x77 || bufferCommand[1] != 0x02) {
        qWarning() << "Failed to handshake with command server - Wrong response";
        return false;
    }
    if (bufferCommand[2] != 0x01) {
        qWarning() << "Failed to handshake with command server - permission failed";
        return false;
    }

    if (!__pSocketStatus->blockingRead(bufferStatus, 4)) {

    }
    if (bufferStatus[0] != 0x77 || bufferStatus[1] != 0x02 || bufferStatus[2] != 0x01) {
        qWarning() << "Failed to handshake with status server - Wrong response";
        return false;
    }

    // Assign magic packet from the received response packets
    magicByteCommand = bufferCommand[3];
    magicByteStatus = bufferStatus[3];

    // Send the magic packet to each server by crossing
    if (!__pSocketCommand->blockingWrite(&magicByteStatus, 1)) {
        qWarning() << "Failed to handshake with command server - magic packet transmission";
        return false;
    }
    if (!__pSocketStatus->blockingWrite(&magicByteCommand, 1)) {
        qWarning() << "Failed to handshake with status server - magic packet transmission";
        return false;
    }

    // Check the response from each server
    if (!__pSocketCommand->blockingRead(bufferCommand, 1)) {

    }
    if (!__pSocketStatus->blockingRead(bufferStatus, 1)) {

    }
    if (bufferCommand[0] == 0x01 || bufferStatus[0] == 0x01) {
        return true;
    }
    else {
        qWarning() << "Failed to handshake - wrong magic packet response";
        return false;
    }
}


//--- Slots ---//
void WorkerConnectionHandler::slotResetConnection() {
    __resetConnection();
    qWarning() << "Disconnected from server connection handler";
}


void WorkerConnectionHandler::process() {

    while(!__flagStop) {
        // Lock Operation Setting
        QThread::msleep(10);
        __mutexOperation.lock();
        if (__flagOperation) {

            try {
                // Try to connect command server if not connected
                if (!__flagConnectionCommandServer) {
                    __pSocketCommand->connectToHost(__IPAddress, PORT_COMMAND_SERVER);
                    if (__pSocketCommand->waitForConnected(__connectionWaitTimeout)) {
                        __flagConnectionCommandServer = true;
                        qInfo() << "Connected to command server";
                    }
                    else {
                        qWarning() << "Cannot connect to command server";
                    }
                }

                // Try to connect status server if not connected
                if (!__flagConnectionStatusServer) {
                    __pSocketStatus->connectToHost(__IPAddress, PORT_STATUS_SERVER);
                    if (__pSocketStatus->waitForConnected(__connectionWaitTimeout)) {
                        __flagConnectionStatusServer = true;
                        qInfo() << "Connected to status server";
                    }
                    else {
                        qWarning() << "Cannot connect to status server";
                    }
                }
            }
            catch (...) {

            }

            if (__flagConnectionCommandServer && __flagConnectionStatusServer && !__flagEstablishedConnection) {
                if (__handShake()) {
                    __flagEstablishedConnection = true;

                    // Move sockets socket controller thread
                    disconnect(__pSocketCommand);
                    disconnect(__pSocketStatus);
                    __pSocketCommand->setParent(nullptr);
                    __pSocketStatus->setParent(nullptr);
                    __pSocketCommand->moveToThread(__pThreadSocketController);
                    __pSocketStatus->moveToThread(__pThreadSocketController);

                    // Notify to socket controller that the connection is ready
                    emit signalReadyToCommunicate();

                    qInfo() << "Handshake process success";
                }
                else {
                    // Disconnect
                    __resetConnection();
                    qWarning() << "Handshake failed";
                }
            }

            // Unlock Operation Setting
            __mutexOperation.unlock();
        }
        QThread::msleep(1000);
    }
}

