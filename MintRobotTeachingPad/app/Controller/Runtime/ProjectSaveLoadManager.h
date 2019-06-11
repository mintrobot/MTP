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

#ifndef PROJECTSAVELOADHANDLER_H
#define PROJECTSAVELOADHANDLER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>

#include "app/controller/SingletonConfiguration.h"

#include "app/model/project/ModelProject.h"
#include "app/model/nodes/ModelNodeAssignVariable.h"
#include "app/model/nodes/ModelNodeConditional.h"
#include "app/model/nodes/ModelNodeContainer.h"
#include "app/model/nodes/ModelNodeDelay.h"
#include "app/model/nodes/ModelNodeDummy.h"
#include "app/model/nodes/ModelNodeMoveRobot.h"
#include "app/model/nodes/ModelNodeDigitalIO.h"

// Project Basic
#define JSON_ATTRIBUTE_START_NODE_ID    "START_NODE_ID"
#define JSON_ATTRIBUTE_NODE_SET         "NODE_SET"

// Node Basic Information
#define JSON_ATTRIBUTE_UUID             "UUID"
#define JSON_ATTRIBUTE_NODE_TYPE        "NODE_TYPE"
#define JSON_ATTRIBUTE_NEXT_NODE_ID     "NEXT_NODE_ID"

// Node Type
#define JSON_ATTRIBUTE_ASSIGN_VARIABLE  "ASSIGN_VARIABLE"
#define JSON_ATTRIBUTE_MOVE_ROBOT       "MOVE_ROBOT"
#define JSON_ATTRIBUTE_CONDITIONAL      "CONDITIONAL"
#define JSON_ATTRIBUTE_DELAY            "DELAY"
#define JSON_ATTRIBUTE_DIGITAL_INOUT    "DIGITAL_INOUT"
#define JSON_ATTRIBUTE_DUMMY            "DUMMY"

// Node Assign Variable
#define JSON_ATTRIBUTE_ASSIGN_VARIABLE_VARIABLE_NAME    "VARIABLE_NAME"
#define JSON_ATTRIBUTE_ASSIGN_VARIABLE_ASSIGN_TYPE      "ASSIGN_TYPE"
#define JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET1_FLAG_REF "TARGET1_IS_REF"
#define JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET1_VALUE    "TARGET1_VALUE"
#define JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET2_FLAG_REF "TARGET2_IS_REF"
#define JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET2_VALUE    "TARGET2_VALUE"

// Node Move Robot
#define JSON_ATTRIBUTE_MOVE_ROBOT_MOVETYPE              "MOVE TYPE"
#define JSON_ATTRIBUTE_MOVE_ROBOT_ISRELATIVE            "IS_RELATIVE"
#define JSON_ATTRIBUTE_MOVE_ROBOT_VEC_ISRELATIVE        "VEC_ISRELATIVE"
#define JSON_ATTRIBUTE_MOVE_ROBOT_VEC_TARGET            "VEC_JOINT"
#define JSON_ATTRIBUTE_MOVE_ROBOT_VEL                   "VEL"
#define JSON_ATTRIBUTE_MOVE_ROBOT_ACCEL                 "ACCEL"

// Node Conditional
#define JSON_ATTRIBUTE_CONDITIONAL_TYPE                 "CONDITIONA_TYPE"
#define JSON_ATTRIBUTE_CONDITIONAL_EQUATION_TYPE        "CONDITIONA_EQUATION_TYPE"
#define JSON_ATTRIBUTE_CONDITIONAL_TARGET1_IS_REF       "TARGET1_IS_REF"
#define JSON_ATTRIBUTE_CONDITIONAL_TARGET1_VALUE        "TARGET1_VALUE"
#define JSON_ATTRIBUTE_CONDITIONAL_TARGET2_IS_REF       "TARGET2_IS_REF"
#define JSON_ATTRIBUTE_CONDITIONAL_TARGET2_VALUE        "TARGET2_VALUE"
#define JSON_ATTRIBUTE_CONDITIONAL_FALSE_NEXT_NODE_ID   "CONDITIONA_FALSE_NEXT_NODE_ID"

// Node Delay
#define JSON_ATTRIBUTE_DELAY_DELAYMS                    "DELAYMS"

// Node Digital IO
#define JSON_ATTRIBUTE_DIGITAL_INOUT_IOTYPE             "IO TYPE"
#define JSON_ATTRIBUTE_DIGITAL_INOUT_INDEX              "INDEX"
#define JSON_ATTRIBUTE_DIGITAL_INOUT_VALUE              "VALUE"
#define JSON_ATTRIBUTE_DIGITAL_INOUT_TIMEOUT            "TIMEOUT"


class ProjectSaveLoadManager : public QObject
{
    Q_OBJECT

public:
    ProjectSaveLoadManager();
    virtual ~ProjectSaveLoadManager();

    static ProjectSaveLoadManager &GetInstance() {
        static ProjectSaveLoadManager instance;
        return instance;
    }

    void saveToJson(QString file, ModelProject* pModelProject);
    void loadFromJson(QString file, ModelProject* pModelProject);


private:
    QString __nodeTypeToString(ModelNode::NODETYPE type);
};

#endif // PROJECTSAVELOADHANDLER_H
