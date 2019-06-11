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

#ifndef INTERFACEROBOTCOMMAND_H
#define INTERFACEROBOTCOMMAND_H

#include <QObject>

class InterfaceRobot : public QObject
{
    Q_OBJECT
public:
    typedef enum {
        ROBOT_STATUS_NOT_READY,
        ROBOT_STATUS_PREPARING,
        ROBOT_STATUS_READY,
        ROBOT_STATUS_OPEARTING
    } ROBOT_STATUS;

    typedef enum {
        CONTROLLER_SERVO_ON_BRAKE_OFF,
        CONTROLLER_SERVO_OFF_BRAKE_ON,
        CONTROLLER_SERVO_ON_BRAKE_ON,
        CONTROLLER_SERVO_OFF_BRAKE_OFF
    } CONTROLLER_STATUS;

    typedef enum {
        ERROR_STATUS_NO_ERROR,
        ERROR_STATUS_SELF_COLLISION_WARNING,
        ERROR_STATUS_JOINT_LIMIT_ERROR,
        ERROR_STATUS_TRAJECTORY_FAILED_ERROR,
        ERROR_STATUS_COLLISION_DETECTION_ERROR,
    } ERROR_STATUS;

    explicit InterfaceRobot(QObject *parent = nullptr);
    virtual ~InterfaceRobot();

signals:
    void signalUpdateConnectionStatus(bool connection);
    void signalUpdatedPos(const QVector<double>& vecJoint, const QVector<double>& vecTCP);
    void signalUpdatedIO(const QVector<bool>& vecDigitalIn, const QVector<bool>& vecDigitalOut);
    void signalUpdateStatus(InterfaceRobot::ROBOT_STATUS robotStatus,
                                 InterfaceRobot::CONTROLLER_STATUS controllerStatus,
                                 InterfaceRobot::ERROR_STATUS errorStatus);

public:
    // Move Robot
    virtual bool moveRobotJointAbs(QVector<double> vecJointTarget, double vel, double accel) = 0;
    virtual bool moveRobotJointRel(QVector<double> vecJointTarget, double vel, double accel) = 0;
    virtual bool moveRobotTCPAbs(QVector<double> vecTCPTarget, double vel, double accel) = 0;
    virtual bool moveRobotTCPRel(QVector<double> vecTCPTarget, double vel, double accel) = 0;
    virtual bool stopRobot() = 0;

    // Jog
    virtual bool jogJoint(int index, int direction, double vel, double accel) = 0;
    virtual bool jotTCP(int type, int axis, int direction, double vel, double accel) = 0;
    virtual bool startDirectTeaching() = 0;

    // IO Functions
    virtual bool setIOStatus(int index, bool status) = 0;
    virtual bool waitIOStatus(int index, bool status, unsigned int timeout) = 0;

    // Robot Configuration
    virtual bool configureTCPOffset(QVector<double> vecOffset, QVector<double> vecWeightCenter, double weight) = 0;
    virtual bool setServoActiveStatus(bool flagStatus) = 0;
    virtual bool setBrakeActiveStatus(bool flagSTatus) = 0;
    virtual bool activateRobot() = 0;
    virtual bool deactivateRobot() = 0;

    // Get Robot Status
    virtual bool isCommandRunning() = 0;
    virtual bool getRobotKinematics(QVector<double>* vecJoint, QVector<double>* vecTCP) = 0;
    virtual bool getRobotJoint(QVector<double>* vecJoint) = 0;
    virtual bool getRobotTCP(QVector<double>* vecTCP) = 0;
    virtual bool getIOStatus(QVector<bool>* vecIO) = 0;
};

#endif // INTERFACEROBOTCOMMAND_H
