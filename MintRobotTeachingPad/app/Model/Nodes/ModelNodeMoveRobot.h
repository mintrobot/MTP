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

#ifndef MODELNODEMOVEROBOTJOINT_H
#define MODELNODEMOVEROBOTJOINT_H

#include <QVector>
#include "app/controller/SingletonRuntimeProject.h"
#include "app/model/project/ModelValue.h"
#include "ModelNode.h"

class ModelNodeMoveRobot : public ModelNode
{
public:
    typedef enum {
        JOINT_INTERPOLATION,
        TCP_LINEAR_INTERPOLATION,
    } MOVETYPE;

    ModelNodeMoveRobot(QUuid uuid = nullptr);
    virtual ~ModelNodeMoveRobot() override;
    void cloneData(const ModelNodeMoveRobot& modelModeRobotJoint);

    virtual ModelNode::NODETYPE getNodeType() override {
        return ModelNode::MOVE_ROBOT;
    }

    virtual QString getCommandString() override{
        if (moveType == JOINT_INTERPOLATION) {
            if (flagRelative) {
                return "MOVEJREL";
            }
            else {
                return "MOVEJABS";
            }
        }
        else if (moveType == TCP_LINEAR_INTERPOLATION){
            if (flagRelative) {
                return "MOVELREL";
            }
            else {
                return "MOVELABS";
            }
        }
        else {
            return "";
        }
    }

    virtual QString getArgumentsString() override;
    virtual QUuid execute() override;

    MOVETYPE moveType = JOINT_INTERPOLATION;
    bool flagRelative = false;

    QVector<ModelValue> vectorTarget;
    double vel = 0;
    double accel = 0;

};

#endif // MODELNODEMOVEROBOTJOINT_H
