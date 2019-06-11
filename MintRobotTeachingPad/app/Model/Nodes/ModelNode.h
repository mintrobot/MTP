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

#ifndef MODELNODE_H
#define MODELNODE_H

#include <QUuid>
#include <QThread>
#include "app/Model/Interface/InterfaceRobot.h"

class ModelNode
{
public:
    typedef enum nodeType {
        DUMMY,
        CONTAINER,
        ASSIGN_VARIABLE,
        ASSIGN_POSITION,
        MOVE_ROBOT,
        CONDITIONAL,
        DELAY,
        DIGITAL_INOUT,
    } NODETYPE;

    ModelNode(QUuid uuid = nullptr);
    virtual ~ModelNode();

    QUuid nextNodeID = nullptr;
    QUuid getNodeID() {
        return __ID;
    }

    void setRobotCommandInterface(InterfaceRobot* pRobotCommand);

    // Since this method is a pure virtual method, user cannot instanciate ModelNode class
    virtual NODETYPE getNodeType() = 0;
    virtual QString getCommandString() = 0;
    virtual QString getArgumentsString() = 0;
    virtual QUuid execute() = 0;


protected:
    QUuid __ID = nullptr;
    InterfaceRobot* __pRobotCommand = nullptr;


private:

};

#endif // MODELNODE_H
