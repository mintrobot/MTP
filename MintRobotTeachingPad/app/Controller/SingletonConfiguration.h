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

#ifndef SINGLETONCONFIGURATION_H
#define SINGLETONCONFIGURATION_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "app/Controller/Comm/ConfigureComm.h"

#define CONFIG_FILE_NAME                    "mtp.config"

// Network
#define JSON_ATTRIBUTE_NETWORK_IPADDRESS    "IP_ADDRESS"

// TCP Setting
#define JSON_ATTRIBUTE_TCP_OFFSET_X         "TCP_OFFSET_X"
#define JSON_ATTRIBUTE_TCP_OFFSET_Y         "TCP_OFFSET_Y"
#define JSON_ATTRIBUTE_TCP_OFFSET_Z         "TCP_OFFSET_Z"
#define JSON_ATTRIBUTE_TCP_COG_X            "TCP_COG_X"
#define JSON_ATTRIBUTE_TCP_COG_Y            "TCP_COG_Y"
#define JSON_ATTRIBUTE_TCP_COG_Z            "TCP_COG_Z"
#define JSON_ATTRIBUTE_TCP_OFFSET_WEIGHT    "TCP_OFFSET_WEIGHT"

// Joint Angle Limit
#define JSON_ATTRIBUTE_JOINT_ANGLE_MIN      "JOINT_ANGLE_MIN"
#define JSON_ATTRIBUTE_JOINT_ANGLE_MAX      "JOINT_ANGLE_MAX"

// User projects path
#define JSON_ATTRIBUTE_USER_PROJECT_PATH    "userprojects"

class SingletonConfiguration : public QObject
{    
    Q_OBJECT

public:
    explicit SingletonConfiguration(QObject *parent = nullptr);
    virtual ~SingletonConfiguration() override;

    static SingletonConfiguration &GetInstance() {
        static SingletonConfiguration instance;
        return instance;
    }

    //--- Robot Configuration
    // Network setting
    QString IPAddress = DEFAULT_TARGET_IP;

    // TCP setting
    double TCPOffsetX = 0;
    double TCPOffsetY = 0;
    double TCPOffsetZ = 0;
    double TCPCOGX = 0;
    double TCPCOGY = 0;
    double TCPCOGZ = 0;
    double TCPWeight = 0;

    // Max Vel and Acc
    double vMaxJoint = 225;
    double aMaxJoint = 2250;
    double vMaxTCP = 0.5;
    double aMaxTCP = 5;

    // Max Min of Joints
    QVector<double> vecMaxAngle;
    QVector<double> vecMinAngle;

    //--- Path configuration
    QString userProjectsFolderPath = "userprojects";

    void saveToJson();
    void loadFromJson();

};

#endif // SINGLETONCONFIGURATION_H
