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

#include "WorkerStatusUpdater.h"

//--- Constructor
WorkerStatusUpdater::WorkerStatusUpdater(QObject *parent) : QObject(parent) {


}

WorkerStatusUpdater::~WorkerStatusUpdater() {

}

//--- Public
void WorkerStatusUpdater::setSocket(BlockingTCPSocket* pSocket) {
    __pSocketStatus = pSocket;
}

void WorkerStatusUpdater::setSocketControlThread(QThread* pThreadSocketController) {
    __pThreadSocketController = pThreadSocketController;
}

void WorkerStatusUpdater::receiveSocketFromSocketController() {
    connect(__pSocketStatus, SIGNAL(disconnected()), this, SLOT(slotTossSocketToSocketcontroller()));
    __flagAuthority = true;
    setActivation(true);
}

void WorkerStatusUpdater::tossSocketToSocketController() {
    disconnect(__pSocketStatus);
    __pSocketStatus->setParent(nullptr);
    __pSocketStatus->moveToThread(__pThreadSocketController);
    __flagAuthority = false;
    setActivation(false);
}

void WorkerStatusUpdater::setActivation(bool activation) {
//    __mutaxOperation.lock();
    if (activation && __flagAuthority) {
        __flagOperable = true;
    }
    else {
        __flagOperable = false;
    }
//    __mutaxOperation.unlock();
}


//--- Private


//--- Slots ---//
void WorkerStatusUpdater::process() {

    char buffer[255];
    STATUS_RECEIVE_ALL status;

    while(!__flagStop) {
        QThread::msleep(10);
        __mutaxOperation.lock();
        if (__flagOperable) {
            try {
                if (__pSocketStatus->state() == QTcpSocket::ConnectedState) {
                    // Send request packet
                    buffer[0] = START_PACKET;
                    buffer[1] = sizeof(STATUS_REQUEST_ALL) + 1;
                    buffer[2] = OPERATION_TYPE_IMMEDIATE_EXECUTION;
                    memcpy(&buffer[3], &__packetStatusRequestAll, sizeof(STATUS_REQUEST_ALL));
                    __pSocketStatus->blockingWrite(buffer, 3 + sizeof(STATUS_REQUEST_ALL));

                    // Receive response packet
                    __pSocketStatus->blockingRead(buffer, 3 + sizeof(STATUS_RECEIVE_ALL));
                    if (buffer[0] == 0x77 && buffer[1] == sizeof(STATUS_RECEIVE_ALL) + 1 && buffer[2] == 0x01) {
                        memcpy(&status, &buffer[3], sizeof(STATUS_RECEIVE_ALL));
                    }
                    else {
                        qWarning() << "Status packet error";
                    }
                    emit signalStatusUpdated(status);
                    QThread::msleep(10); // Polling in 100Hz
                }
                else {
                    __flagOperable = false;
                    tossSocketToSocketController();
                    emit signalDisconnected();
                    QThread::msleep(1000);
                }
            }
            catch (...) {

            }
        }
        else {
            QThread::msleep(1000);
        }
        __mutaxOperation.unlock();
    }
}

void WorkerStatusUpdater::slotTossSocketToSocketcontroller() {
    tossSocketToSocketController();
    __flagOperable = false;
    emit signalDisconnected();
}
