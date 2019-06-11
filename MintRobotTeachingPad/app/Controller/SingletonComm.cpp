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

#include "SingletonComm.h"

//--- Constructor ---//
SingletonComm::SingletonComm(QObject *parent) : InterfaceRobot (parent) {

    // Register Meta structure for connect
    qRegisterMetaType<STATUS_RECEIVE_ALL>("STATUS_RECEIVE_ALL");

    __pSocketCommand = new BlockingTCPSocket(this);
    __pSocketStatus = new BlockingTCPSocket(this);
}

SingletonComm::~SingletonComm() {

}

//--- Public ---//
void SingletonComm::init() {

    __IPAddress = SingletonConfiguration::GetInstance().IPAddress;

    // Init connection handler
    __pThreadConnection = new QThread;
    __pWorkerConnectionHandler = new WorkerConnectionHandler();
    __pWorkerConnectionHandler->moveToThread(__pThreadConnection);
    __pWorkerConnectionHandler->changeIPAddress(__IPAddress);
    __pWorkerConnectionHandler->setSocket(__pSocketCommand, __pSocketStatus);
    __pWorkerConnectionHandler->setSocketControlThread(this->thread());
    __pWorkerConnectionHandler->setActivation(false);
    connect(__pThreadConnection, SIGNAL(started()), __pWorkerConnectionHandler, SLOT(process()));
    connect(__pWorkerConnectionHandler, SIGNAL(signalReadyToCommunicate()), this, SLOT(slotPrepareCommunication()));


    // Init status updator
    __pThreadStatus = new QThread;
    __pWorkerStatusUpdater = new WorkerStatusUpdater();
    __pWorkerStatusUpdater->moveToThread(__pThreadStatus);
    __pWorkerStatusUpdater->setSocket(__pSocketStatus);
    __pWorkerStatusUpdater->setSocketControlThread(this->thread());
    __pWorkerStatusUpdater->setActivation(false);
    connect(__pThreadStatus, SIGNAL(started()), __pWorkerStatusUpdater, SLOT(process()));
    connect(__pWorkerStatusUpdater, SIGNAL(signalStatusUpdated(const STATUS_RECEIVE_ALL&)), this, SLOT(slotUpdateStatus(const STATUS_RECEIVE_ALL&)));

    // Start each thread
    __pThreadConnection->start();
    __pThreadStatus->start();

    // Toss sockets to connection handler thread
    __tossSocketToConnectionHandler();
    __pWorkerConnectionHandler->receiveSocketFromSocketController();
}

void SingletonComm::setIPAddress(QString IPAddress) {

    __mutaxOperation.lock();
    __flagOperable = false;

    __IPAddress = IPAddress;
    __pWorkerConnectionHandler->changeIPAddress(__IPAddress);
    __mutaxOperation.unlock();
}

// Override functions for InterfaceRobotCommand
// Move Robot Function
bool SingletonComm::moveRobotJointAbs(QVector<double> vecJointTarget, double vel, double accel) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        memcpy(__packetMoveJointAbs.vecJoint, vecJointTarget.data(), sizeof(double) * 6);
        for (int i = 0; i < 6; i++) {
            __packetMoveJointAbs.vecJoint[i] = qDegreesToRadians(__packetMoveJointAbs.vecJoint[i]);
        }
        __packetMoveJointAbs.vMax = qDegreesToRadians(vel);
        __packetMoveJointAbs.aMax = qDegreesToRadians(accel);
        __header[1] = sizeof(MOVE_JOINT_ABS) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetMoveJointAbs), sizeof(__packetMoveJointAbs));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - moveRobotJointAbs";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - moveRobotJointAbs";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - moveRobotJointAbs";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

bool SingletonComm::moveRobotJointRel(QVector<double> vecJointTarget, double vel, double accel) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        memcpy(__packetMoveJointRel.vecJoint, vecJointTarget.data(), sizeof(double) * 6);
        for (int i = 0; i < 6; i++) {
            __packetMoveJointRel.vecJoint[i] = qDegreesToRadians(__packetMoveJointRel.vecJoint[i]);
        }
        __packetMoveJointRel.vMax = qDegreesToRadians(vel);
        __packetMoveJointRel.aMax = qDegreesToRadians(accel);
        __header[1] = sizeof(MOVE_JOINT_REL) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetMoveJointRel), sizeof(__packetMoveJointRel));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - moveRobotJointRel";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - moveRobotJointRel";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - moveRobotJointRel";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

bool SingletonComm::moveRobotTCPAbs(QVector<double> vecTCPTarget, double vel, double accel) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        memcpy(__packetMoveTCPLinearAbs.vecTCP, vecTCPTarget.data(), sizeof(double) * 6);
        __packetMoveTCPLinearAbs.vMax = vel;
        __packetMoveTCPLinearAbs.aMax = accel;
        __header[1] = sizeof(MOVE_TCP_LINEAR_ABS) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetMoveTCPLinearAbs), sizeof(__packetMoveTCPLinearAbs));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - moveRobotTCPAbs";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - moveRobotTCPAbs";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - moveRobotTCPAbs";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

bool SingletonComm::moveRobotTCPRel(QVector<double> vecTCPTarget, double vel, double accel) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        memcpy(__packetMoveTCPLinearRel.vecTCP, vecTCPTarget.data(), sizeof(double) * 6);
        __packetMoveTCPLinearRel.vMax = vel;
        __packetMoveTCPLinearRel.aMax = accel;
        __header[1] = sizeof(MOVE_TCP_LINEAR_REL) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetMoveTCPLinearRel), sizeof(__packetMoveTCPLinearRel));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - moveRobotTCPRel";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - moveRobotTCPRel";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - moveRobotTCPRel";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

bool SingletonComm::stopRobot() {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        __bufferSend.clear();
        __bufferSend.append(START_PACKET);
        __bufferSend.append(0x01);
        __bufferSend.append(OPERATION_TYPE_STOP);

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - stopRobot";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - stopRobot";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - stopRobot";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

// Jog Functions
bool SingletonComm::jogJoint(int index, int direction, double vel, double accel) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        __packetJogJoint.index = static_cast<char>(index);
        __packetJogJoint.direction = static_cast<char>(direction);
        __packetJogJoint.vMax = vel;
        __packetJogJoint.aMax = accel;
        __header[1] = sizeof(JOG_JOINT) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetJogJoint), sizeof(__packetJogJoint));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - jogJoint";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - jogJoint";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - jogJoint";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

bool SingletonComm::jotTCP(int type, int axis, int direction, double vel, double accel) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        __packetJogTCP.type = static_cast<char>(type);
        __packetJogTCP.axis = static_cast<char>(axis);
        __packetJogTCP.direction = static_cast<char>(direction);
        __packetJogTCP.vMax = vel;
        __packetJogTCP.aMax = accel;
        __header[1] = sizeof(JOG_JOINT) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetJogTCP), sizeof(__packetJogTCP));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - jotTCP";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - jotTCP";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - jotTCP";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

bool SingletonComm::startDirectTeaching() {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        __header[1] = sizeof(START_DIRECT_TEACHING) + 3;
        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetStartDirectTeaching), sizeof(__packetStartDirectTeaching));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - startDirectTeaching";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - startDirectTeaching";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - startDirectTeaching";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

// IO Functions
bool SingletonComm::setIOStatus(int index, bool status) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        __packetSetDigitalOut.index = static_cast<char>(index);
        __packetSetDigitalOut.value = static_cast<char>(status);
        __header[1] = sizeof(SET_DIGITAL_OUT) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetSetDigitalOut), sizeof(__packetSetDigitalOut));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - setIOStatus";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - setIOStatus";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - setIOStatus";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

bool SingletonComm::waitIOStatus(int index, bool status, unsigned int timeout) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        __packetWaitDigitalIn.index = static_cast<char>(index);
        __packetWaitDigitalIn.value = static_cast<char>(status);
        __header[1] = sizeof(WAIT_DIGITAL_IN) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetWaitDigitalIn), sizeof(__packetWaitDigitalIn));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - waitIOStatus";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3, timeout) != 3) {
                qWarning() << "Transmission error - waitIOStatus";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - waitIOStatus";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

// Robot Configuration
bool SingletonComm::configureTCPOffset(QVector<double> vecOffset, QVector<double> vecWeightCenter, double weight) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        memcpy(&__packetSetTCPOffset.vecOffset, vecOffset.data(), sizeof(double) * 3);
        memcpy(&__packetSetTCPOffset.vecCenter, vecWeightCenter.data(), sizeof(double) * 3);
        __packetSetTCPOffset.weight = weight;
        __header[1] = sizeof(SET_TCP_OFFSET) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetSetTCPOffset), sizeof(__packetSetTCPOffset));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - configureTCPOffset";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - configureTCPOffset";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - configureTCPOffset";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

bool SingletonComm::setServoActiveStatus(bool flagStatus) {
    bool res = false;
    __mutaxOperation.lock();
    if (__flagOperable) {
        __packetServoOnOff.flagStatus = static_cast<unsigned char>(flagStatus);
        __header[1] = sizeof(SERVO_ON_OFF) + 3;

        __bufferSend.clear();
        __bufferSend.append(__header, sizeof(__header));
        __bufferSend.append(reinterpret_cast<char*>(&__packetSetTCPOffset), sizeof(__packetSetTCPOffset));
        __bufferSend.append(__userIndex, sizeof(__userIndex));

        if (__pSocketCommand->blockingWrite(__bufferSend.data(), __bufferSend.length()) != __bufferSend.length()) {
            qWarning() << "Transmission error - setServoActiveStatus";
            res = false;
        }
        else {
            if (__pSocketCommand->blockingRead(__bufferAck, 3) != 3) {
                qWarning() << "Transmission error - setServoActiveStatus";
                res = false;
            }
            else {
                if (__bufferAck[0] != 0x77 || __bufferAck[1] != 0x01 || __bufferAck[2] != 0x01) {
                    qWarning() << "Transmission error - setServoActiveStatus";
                    res = false;
                }
                res = true;
            }
        }
    }
    else {
        qWarning() << "Connection is not established";
    }
    __mutaxOperation.unlock();
    return res;
}

bool SingletonComm::setBrakeActiveStatus(bool flagStatus) {
    Q_UNUSED(flagStatus)
    return true;
}

bool SingletonComm::activateRobot() {
    return true;
}

bool SingletonComm::deactivateRobot() {
    return true;
}



// Get Robot Status
bool SingletonComm::isCommandRunning() {
    if (__isRunning == 0x02) {
        return false;
    }
    else {
        return true;
    }
}

bool SingletonComm::getRobotKinematics(QVector<double>* vecJoint, QVector<double>* vecTCP) {
    memcpy(vecJoint->data(), __vecJoint.data(), sizeof(double) * 6);
    memcpy(vecTCP->data(), __vecTCP.data(), sizeof(double) * 6);
    return true;
}

bool SingletonComm::getRobotJoint(QVector<double>* vecJoint) {
    memcpy(vecJoint->data(), __vecJoint.data(), sizeof(double) * 6);
    return true;
}

bool SingletonComm::getRobotTCP(QVector<double>* vecTCP) {
    memcpy(vecTCP->data(), __vecTCP.data(), sizeof(double) * 6);
    return true;
}

bool SingletonComm::getIOStatus(QVector<bool>* vecIO) {
    memcpy(vecIO->data(), __vecDigitalIn.data(), sizeof(bool) * 8);
    return true;
}


//--- Private ---//
void SingletonComm::__tossSocketToConnectionHandler() {
    disconnect(__pSocketCommand);
    disconnect(__pSocketStatus);
    __pSocketCommand->setParent(nullptr);
    __pSocketStatus->setParent(nullptr);
    __pSocketCommand->moveToThread(__pWorkerConnectionHandler->thread());
    __pSocketStatus->moveToThread(__pWorkerConnectionHandler->thread());
    __flagStatusSocketReceived = false;
}


//--- Slots ---//
void SingletonComm::slotPrepareCommunication() {

    __mutaxOperation.lock();

    // Init command socket
    connect(__pSocketCommand, SIGNAL(disconnected()), this, SLOT(slotRetryConnection()));

    // Toss status socket to status thread
    disconnect(__pSocketStatus);
    __pSocketStatus->setParent(nullptr);
    __pSocketStatus->moveToThread(__pWorkerStatusUpdater->thread());
    __pWorkerStatusUpdater->receiveSocketFromSocketController();

    __flagOperable = true;
    __isConnected = true;
    __mutaxOperation.unlock();

    emit signalUpdateConnectionStatus(__isConnected);

}


void SingletonComm::slotRetryConnection() {

    __isConnected = false;
    emit signalUpdateConnectionStatus(__isConnected);
    qWarning() << "Disconnected from server";

    while (true) {
        __mutaxOperation.lock();
        if (__pSocketStatus->thread() == this->thread()) {
            __mutaxOperation.unlock();
            break;
        }
        else {
            __mutaxOperation.unlock();
            QThread::msleep(10);
        }
    }

    __mutaxOperation.lock();

    __flagOperable = false;
    __tossSocketToConnectionHandler();
    __pWorkerConnectionHandler->receiveSocketFromSocketController();

    __mutaxOperation.unlock();
}

void SingletonComm::slotUpdateStatus(const STATUS_RECEIVE_ALL& status) {

    __isRunning = status.statusCommandRunning;

    // Pos
    memcpy(__vecJoint.data(),status.vectorJoint, sizeof(double) * 6);
    memcpy(__vecTCP.data(), status.vectorTCP, sizeof(double) * 6);

    // IO
    for(int i = 0; i < 6; i++) {
        __vecJoint[i] = qRadiansToDegrees(__vecJoint[i]);
    }
    for (int i = 0; i < 8; i++) {
        __vecDigitalIn[i] = static_cast<bool>(status.digitalIn[i]);
        __vecDigitalOut[i] = static_cast<bool>(status.digitalOut[i]);
    }

    // Robot Status
    switch(status.statusRobotRunning) {
    case 0x01:
        __robotStatus = InterfaceRobot::ROBOT_STATUS_NOT_READY;
        break;

    case 0x02:
        __robotStatus = InterfaceRobot::ROBOT_STATUS_PREPARING;
        break;

    case 0x03:
        __robotStatus = InterfaceRobot::ROBOT_STATUS_READY;
        break;

    case 0x04:
        __robotStatus = InterfaceRobot::ROBOT_STATUS_OPEARTING;
        break;
    }

    switch(status.statusController) {
    case 0x01:
        __controllerStatus = InterfaceRobot::CONTROLLER_SERVO_ON_BRAKE_OFF;
        break;

    case 0x02:
        __controllerStatus = InterfaceRobot::CONTROLLER_SERVO_OFF_BRAKE_ON;
        break;

    case 0x03:
        __controllerStatus = InterfaceRobot::CONTROLLER_SERVO_ON_BRAKE_ON;
        break;

    case 0x04:
        __controllerStatus = InterfaceRobot::CONTROLLER_SERVO_OFF_BRAKE_OFF;
        break;
    }

    switch(status.statusError) {
    case 0x01:
        __errorStatus = InterfaceRobot::ERROR_STATUS_NO_ERROR;
        break;

    case 0x02:
        __errorStatus = InterfaceRobot::ERROR_STATUS_SELF_COLLISION_WARNING;
        break;

    case 0x03:
        __errorStatus = InterfaceRobot::ERROR_STATUS_JOINT_LIMIT_ERROR;
        break;

    case 0x04:
        __errorStatus = InterfaceRobot::ERROR_STATUS_TRAJECTORY_FAILED_ERROR;
        break;

    case 0x05:
        __errorStatus = InterfaceRobot::ERROR_STATUS_COLLISION_DETECTION_ERROR;
        break;
    }

    emit signalUpdatedPos(__vecJoint, __vecTCP);
    emit signalUpdatedIO(__vecDigitalIn, __vecDigitalOut);
    emit signalUpdateStatus(__robotStatus, __controllerStatus, __errorStatus);

}
