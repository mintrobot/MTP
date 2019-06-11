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

#ifndef MODELNODESETDIGITALOUT_H
#define MODELNODESETDIGITALOUT_H

#include <QThread>

#include "app/controller/SingletonComm.h"
#include "ModelNode.h"

class ModelNodeDigitalIO : public ModelNode
{
public:
    typedef enum {
        SET,
        WAIT,
    } IOTYPE;

    ModelNodeDigitalIO(QUuid uuid = nullptr) ;
    virtual ~ModelNodeDigitalIO() override;
    void cloneData(const ModelNodeDigitalIO& modelNodeSetDigitalOut);

    virtual ModelNode::NODETYPE getNodeType() override{
        return ModelNode::DIGITAL_INOUT;
    }

    virtual QString getCommandString() override{
        if (ioType == SET) {
            return "SETDO";
        }
        else if (ioType == WAIT) {
            return "WAITDI";
        }
        return "";
    }

    virtual QString getArgumentsString() override;
    virtual QUuid execute() override;

    IOTYPE ioType = SET;
    QVector<bool> listStatus;
    unsigned int timeout = 1000;
};

#endif // MODELNODESETDIGITALOUT_H
