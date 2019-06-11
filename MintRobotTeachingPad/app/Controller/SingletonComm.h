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

#ifndef SINGLETONCOMM_H
#define SINGLETONCOMM_H

#include <QObject>
#include <QTcpSocket>
#include <QMutex>
#include <QtMath>

#include "app/model/interface/InterfaceRobot.h"

#include "app/controller/SingletonConfiguration.h"
#include "app/controller/comm/ConfigureComm.h"
#include "app/controller/comm/WorkerConnectionHandler.h"
#include "app/controller/comm/WorkerStatusUpdater.h"


class SingletonComm : public InterfaceRobot
{
    Q_OBJECT

public:
    explicit SingletonComm(QObject *parent = nullptr);
    virtual ~SingletonComm() override;

    static SingletonComm &GetInstance() {
        static SingletonComm instance;
        return instance;
    }

    void init();
    void setIPAddress(QString IPAddress);

private:
    // Variables for socket communication
    QString __IPAddress = DEFAULT_TARGET_IP;
    BlockingTCPSocket* __pSocketCommand;
    BlockingTCPSocket* __pSocketStatus;
    void __tossSocketToConnectionHandler();

    // Robot status
    char __isRunning = 0x00;
    bool __isConnected = false;
    QVector<double> __vecJoint = QVector<double>(6);
    QVector<double> __vecTCP = QVector<double>(6);
    QVector<bool> __vecDigitalIn = QVector<bool>(8);
    QVector<bool> __vecDigitalOut = QVector<bool>(8);
    ROBOT_STATUS __robotStatus;
    CONTROLLER_STATUS __controllerStatus;
    ERROR_STATUS __errorStatus;

    // Threading Variables
    QThread* __pThreadConnection;
    QThread* __pThreadStatus;
    WorkerConnectionHandler* __pWorkerConnectionHandler;
    WorkerStatusUpdater* __pWorkerStatusUpdater;

    QMutex __mutaxOperation;
    bool __flagOperable = false;
    bool __flagStatusSocketReceived = false;


    // Packets
    QByteArray __bufferSend;
    char __bufferAck[3] = {0,};
    char __userIndex[2] = {0x00, 0x00};
    char __header[3] = {START_PACKET, 0x00, OPERATION_TYPE_IMMEDIATE_EXECUTION};
    MOVE_JOINT_ABS __packetMoveJointAbs;
    MOVE_JOINT_REL __packetMoveJointRel;
    MOVE_TCP_LINEAR_ABS __packetMoveTCPLinearAbs;
    MOVE_TCP_LINEAR_REL __packetMoveTCPLinearRel;
    JOG_JOINT __packetJogJoint;
    JOG_TCP __packetJogTCP;
    START_DIRECT_TEACHING __packetStartDirectTeaching;
    SET_DIGITAL_OUT __packetSetDigitalOut;
    WAIT_DIGITAL_IN __packetWaitDigitalIn;
    SET_TCP_OFFSET __packetSetTCPOffset;
    SERVO_ON_OFF __packetServoOnOff;
    BRAKE_ON_OFF __packetBrakeOnOff;
    ACTIVATE_ROBOT __packetActivateRobot;

public:
    // Override functions for InterfaceRobotCommand
    // Move Robot Function
    virtual bool moveRobotJointAbs(QVector<double> vecJointTarget, double vel, double accel) override;
    virtual bool moveRobotJointRel(QVector<double> vecJointTarget, double vel, double accel) override;
    virtual bool moveRobotTCPAbs(QVector<double> vecTCPTarget, double vel, double accel) override;
    virtual bool moveRobotTCPRel(QVector<double> vecTCPTarget, double vel, double accel) override;
    virtual bool stopRobot() override;

    // Jog
    virtual bool jogJoint(int index, int direction, double vel, double accel) override;
    virtual bool jotTCP(int type, int axis, int direction, double vel, double accel) override;
    virtual bool startDirectTeaching() override;

    // IO Functions
    virtual bool setIOStatus(int index, bool status) override;
    virtual bool waitIOStatus(int index, bool status, unsigned int timeout) override;

    // Robot Configuration
    virtual bool configureTCPOffset(QVector<double> vecOffset, QVector<double> vecWeightCenter, double weight) override;
    virtual bool setServoActiveStatus(bool flagStatus);
    virtual bool setBrakeActiveStatus(bool flagSTatus);
    virtual bool activateRobot();
    virtual bool deactivateRobot();


    // Get Robot Status
    virtual bool isCommandRunning() override;
    virtual bool getRobotKinematics(QVector<double>* vecJoint, QVector<double>* vecTCP) override;
    virtual bool getRobotJoint(QVector<double>* vecJoint) override;
    virtual bool getRobotTCP(QVector<double>* vecTCP) override;
    virtual bool getIOStatus(QVector<bool>* vecIO) override;


signals:
    void signalTossAuthorityToConnectionThread();

private slots:
    void slotPrepareCommunication();
    void slotRetryConnection();
    void slotUpdateStatus(const STATUS_RECEIVE_ALL& status);

};

#endif // SINGLETONCOMM_H

