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

#include "ModelNodeDigitalIO.h"

ModelNodeDigitalIO::ModelNodeDigitalIO(QUuid uuid) : ModelNode(uuid) {
    for (int i = 0; i < 8; i++) {
        listStatus.append(false);
    }
}

ModelNodeDigitalIO::~ModelNodeDigitalIO() {

}

void ModelNodeDigitalIO::cloneData(const ModelNodeDigitalIO& modelNodeSetDigitalOut) {
    ioType = modelNodeSetDigitalOut.ioType;
    for (int i = 0 ; i < listStatus.size(); i++) {
        listStatus[i] = modelNodeSetDigitalOut.listStatus.at(i);
    }
    timeout = modelNodeSetDigitalOut.timeout;
}

QString ModelNodeDigitalIO::getArgumentsString() {
    QString res = "[";
    for (int i = 0; i < listStatus.size(); i++) {
        if (listStatus.at(i)) {
            res += "H";
        }
        else {
            res += "L";
        }
        if (i < listStatus.size() - 1) {
            res += " ";
        }
    }
    res += "]";
    if (ioType == ModelNodeDigitalIO::WAIT) {
        res += "[" + QString::number(timeout) + "]";
    }
    return res;
}

QUuid ModelNodeDigitalIO::execute() {

    if (ioType == SET) {
        for (int i = 0 ; i < listStatus.size(); i++) {
            __pRobotCommand->setIOStatus(i, listStatus.at(i));
            while(__pRobotCommand->isCommandRunning()) {
                QThread::msleep(10);
            }
        }
    }
    else if (ioType == WAIT) {
        QVector<bool> currentDigitalIn;
        for (int i = 0 ; i < 8; i++) {
            currentDigitalIn.append(false);
        }

        double elaspedTime = 0;
        while(elaspedTime < timeout) {
            __pRobotCommand->getIOStatus(&currentDigitalIn);
            if (currentDigitalIn == listStatus) {
                break;
            }
            else {
                QThread::msleep(10);
                elaspedTime += 10;
            }
        }
    }
    return nextNodeID;
}
