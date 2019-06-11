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

#include "SingletonConfiguration.h"

SingletonConfiguration::SingletonConfiguration(QObject *parent) : QObject(parent) {

    for (int i = 0; i < 6; i++) {
        vecMaxAngle.append(360);
        vecMinAngle.append(-360);
    }
}

SingletonConfiguration::~SingletonConfiguration() {

}


void SingletonConfiguration::saveToJson() {

    QString path = CONFIG_FILE_NAME;
    QFile writeFile(QDir::currentPath() + "/" + path);

    if (!writeFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Write configuration failed";
        return ;
    }

    QJsonObject configObj;
    configObj[JSON_ATTRIBUTE_NETWORK_IPADDRESS] = SingletonConfiguration::GetInstance().IPAddress;
    configObj[JSON_ATTRIBUTE_TCP_OFFSET_X] = SingletonConfiguration::GetInstance().TCPOffsetX;
    configObj[JSON_ATTRIBUTE_TCP_OFFSET_Y] = SingletonConfiguration::GetInstance().TCPOffsetY;
    configObj[JSON_ATTRIBUTE_TCP_OFFSET_Z] = SingletonConfiguration::GetInstance().TCPOffsetZ;
    configObj[JSON_ATTRIBUTE_TCP_COG_X] = SingletonConfiguration::GetInstance().TCPCOGX;
    configObj[JSON_ATTRIBUTE_TCP_COG_Y] = SingletonConfiguration::GetInstance().TCPCOGY;
    configObj[JSON_ATTRIBUTE_TCP_COG_Z] = SingletonConfiguration::GetInstance().TCPCOGZ;
    configObj[JSON_ATTRIBUTE_TCP_OFFSET_WEIGHT] = SingletonConfiguration::GetInstance().TCPWeight;

    QJsonArray arrayMinAngle;
    QJsonArray arrayMaxAngle;
    for (int i = 0 ; i < 6; i++) {
        arrayMinAngle.append(SingletonConfiguration::GetInstance().vecMinAngle.at(i));
        arrayMaxAngle.append(SingletonConfiguration::GetInstance().vecMaxAngle.at(i));
    }
    configObj[JSON_ATTRIBUTE_JOINT_ANGLE_MIN] = arrayMinAngle;
    configObj[JSON_ATTRIBUTE_JOINT_ANGLE_MAX] = arrayMaxAngle;

    configObj[JSON_ATTRIBUTE_USER_PROJECT_PATH] = SingletonConfiguration::GetInstance().userProjectsFolderPath;

    //____MAIN_END____
    QJsonDocument doc;
    doc.setObject(configObj);

    writeFile.write(doc.toJson());
    writeFile.close();
}

void SingletonConfiguration::loadFromJson() {

    QString path = CONFIG_FILE_NAME;
    QFile readFile(QDir::currentPath() + "/" + path);

    if (!readFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Read configuration failed";
        return ;
    }

    QByteArray readByteArray = readFile.readAll();
    QJsonDocument readDoc(QJsonDocument::fromJson(readByteArray));
    QJsonObject configObj = readDoc.object();

    SingletonConfiguration::GetInstance().IPAddress = configObj[JSON_ATTRIBUTE_NETWORK_IPADDRESS].toString();
    SingletonConfiguration::GetInstance().TCPOffsetX = configObj[JSON_ATTRIBUTE_TCP_OFFSET_X].toDouble();
    SingletonConfiguration::GetInstance().TCPOffsetY = configObj[JSON_ATTRIBUTE_TCP_OFFSET_Y].toDouble();
    SingletonConfiguration::GetInstance().TCPOffsetZ = configObj[JSON_ATTRIBUTE_TCP_OFFSET_Z].toDouble();
    SingletonConfiguration::GetInstance().TCPCOGX = configObj[JSON_ATTRIBUTE_TCP_COG_X].toDouble();
    SingletonConfiguration::GetInstance().TCPCOGY = configObj[JSON_ATTRIBUTE_TCP_COG_Y].toDouble();
    SingletonConfiguration::GetInstance().TCPCOGZ = configObj[JSON_ATTRIBUTE_TCP_COG_Z].toDouble();
    SingletonConfiguration::GetInstance().TCPWeight = configObj[JSON_ATTRIBUTE_TCP_OFFSET_WEIGHT].toDouble();

    QJsonArray arrayMinAngle = configObj[JSON_ATTRIBUTE_JOINT_ANGLE_MIN].toArray();
    QJsonArray arrayMaxAngle = configObj[JSON_ATTRIBUTE_JOINT_ANGLE_MAX].toArray();
    for (int i = 0 ; i <6; i++) {
        SingletonConfiguration::GetInstance().vecMinAngle[i] = arrayMinAngle.at(i).toDouble();
        SingletonConfiguration::GetInstance().vecMaxAngle[i] = arrayMaxAngle.at(i).toDouble();
    }

    SingletonConfiguration::GetInstance().userProjectsFolderPath = configObj[JSON_ATTRIBUTE_USER_PROJECT_PATH].toString();
}

