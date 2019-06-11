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

#include "ProjectSaveLoadManager.h"

// --- Constructor ---
ProjectSaveLoadManager::ProjectSaveLoadManager() {

}

ProjectSaveLoadManager::~ProjectSaveLoadManager() {

}

void ProjectSaveLoadManager::saveToJson(QString fileName, ModelProject* pModelProject) {

    QString path = fileName;
    QFile writeFile(QDir::currentPath() + "/"  + SingletonConfiguration::GetInstance().userProjectsFolderPath + "/" + path);

    if (!writeFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Project save failed";
        return ;
    }
    QJsonObject rootObj;
    rootObj[JSON_ATTRIBUTE_START_NODE_ID] = pModelProject->IDStartNode.toString();

    //____Node_______
    QHash<QUuid, ModelNode*>::const_iterator iterator;
    QJsonArray jsonNodeObjectArray;
    QUuid uuid = nullptr;
    ModelNode* pNode = nullptr;
    ModelNode::NODETYPE type = ModelNode::DUMMY;

    for (iterator = pModelProject->getHashNode()->constBegin(); iterator != pModelProject->getHashNode()->constEnd(); ++iterator) {
        uuid = iterator.key();
        pNode = iterator.value();
        type = pNode->getNodeType();

        QJsonObject jsonNodeObject;
        jsonNodeObject[JSON_ATTRIBUTE_UUID] = uuid.toString();
        jsonNodeObject[JSON_ATTRIBUTE_NODE_TYPE] = __nodeTypeToString(type);
        jsonNodeObject[JSON_ATTRIBUTE_NEXT_NODE_ID] = pNode->nextNodeID.toString();

        if (ModelNode::ASSIGN_VARIABLE == type) {
            ModelNodeAssignVariable* pNodeAssignVariable = static_cast<ModelNodeAssignVariable*>(pNode);
            jsonNodeObject[JSON_ATTRIBUTE_ASSIGN_VARIABLE_VARIABLE_NAME] = pNodeAssignVariable->variableName;
            jsonNodeObject[JSON_ATTRIBUTE_ASSIGN_VARIABLE_ASSIGN_TYPE] = pNodeAssignVariable->assignType;
            jsonNodeObject[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET1_FLAG_REF] = pNodeAssignVariable->value1.isRreference;
            jsonNodeObject[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET1_VALUE] = pNodeAssignVariable->value1.getValueInStringFormat();
            jsonNodeObject[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET2_FLAG_REF] = pNodeAssignVariable->value2.isRreference;
            jsonNodeObject[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET2_VALUE] = pNodeAssignVariable->value2.getValueInStringFormat();
        }
        else if (ModelNode::MOVE_ROBOT == type) {
            ModelNodeMoveRobot* pNodeMoveRobot = static_cast<ModelNodeMoveRobot*>(pNode);
            jsonNodeObject[JSON_ATTRIBUTE_MOVE_ROBOT_MOVETYPE] = pNodeMoveRobot->moveType;
            jsonNodeObject[JSON_ATTRIBUTE_MOVE_ROBOT_ISRELATIVE] = pNodeMoveRobot->flagRelative;
            QJsonArray arrayReferenceFlag;
            QJsonArray arratTarget;
            for (int i = 0 ; i < 6; i++) {
                arrayReferenceFlag.append(pNodeMoveRobot->vectorTarget[i].isRreference);
                if (pNodeMoveRobot->vectorTarget[i].isRreference) {
                    arratTarget.append(pNodeMoveRobot->vectorTarget[i].referenceName);
                }
                else {
                    arratTarget.append(pNodeMoveRobot->vectorTarget[i].value);
                }
            }
            jsonNodeObject[JSON_ATTRIBUTE_MOVE_ROBOT_VEC_ISRELATIVE] = arrayReferenceFlag;
            jsonNodeObject[JSON_ATTRIBUTE_MOVE_ROBOT_VEC_TARGET] = arratTarget;
            jsonNodeObject[JSON_ATTRIBUTE_MOVE_ROBOT_VEL] = pNodeMoveRobot->vel;
            jsonNodeObject[JSON_ATTRIBUTE_MOVE_ROBOT_ACCEL] = pNodeMoveRobot->accel;
        }
        else if (ModelNode::CONDITIONAL == type) {
            ModelNodeConditional* pNodeConditional = static_cast<ModelNodeConditional*>(pNode);
            jsonNodeObject[JSON_ATTRIBUTE_CONDITIONAL_TYPE] = pNodeConditional->conditionalType;
            jsonNodeObject[JSON_ATTRIBUTE_CONDITIONAL_EQUATION_TYPE] = pNodeConditional->conditionalEquationType;
            jsonNodeObject[JSON_ATTRIBUTE_CONDITIONAL_TARGET1_IS_REF] = pNodeConditional->value1.isRreference;
            jsonNodeObject[JSON_ATTRIBUTE_CONDITIONAL_TARGET1_VALUE] = pNodeConditional->value1.getValueInStringFormat();
            jsonNodeObject[JSON_ATTRIBUTE_CONDITIONAL_TARGET2_IS_REF] = pNodeConditional->value2.isRreference;
            jsonNodeObject[JSON_ATTRIBUTE_CONDITIONAL_TARGET2_VALUE] = pNodeConditional->value2.getValueInStringFormat();
            jsonNodeObject[JSON_ATTRIBUTE_CONDITIONAL_FALSE_NEXT_NODE_ID] = pNodeConditional->nextNodeID_conditionFalse.toString();
        }
        else if (ModelNode::DELAY == type) {
            ModelNodeDelay* pNodeModelDelay = static_cast<ModelNodeDelay*>(pNode);
            jsonNodeObject[JSON_ATTRIBUTE_DELAY_DELAYMS] = static_cast<int>(pNodeModelDelay->delayms);
        }        
        else if (ModelNode::DIGITAL_INOUT == type) {
            ModelNodeDigitalIO* pNodeModelDigitalInOut = static_cast<ModelNodeDigitalIO*>(pNode);
             jsonNodeObject[JSON_ATTRIBUTE_DIGITAL_INOUT_IOTYPE] = pNodeModelDigitalInOut->ioType;
            QJsonArray array;
            for (int i = 0 ; i < 8; i++) {
                array.append(pNodeModelDigitalInOut->listStatus.at(i));
            }
            jsonNodeObject[JSON_ATTRIBUTE_DIGITAL_INOUT_VALUE] = array;
            jsonNodeObject[JSON_ATTRIBUTE_DIGITAL_INOUT_TIMEOUT] = static_cast<int>(pNodeModelDigitalInOut->timeout);
        }
        else if (ModelNode::DUMMY == type) {

        }
        jsonNodeObjectArray.append(jsonNodeObject);
    }

    rootObj[JSON_ATTRIBUTE_NODE_SET] = jsonNodeObjectArray;

    //____MAIN_END____
    QJsonDocument doc;
    doc.setObject(rootObj);

    writeFile.write(doc.toJson());
    writeFile.close();
}

void ProjectSaveLoadManager::loadFromJson(QString file, ModelProject* pModelProject) {
    QString path = file;
    QString asd = SingletonConfiguration::GetInstance().userProjectsFolderPath + "/" + path;
    QFile readFile(QDir::currentPath() + "/"  + SingletonConfiguration::GetInstance().userProjectsFolderPath + "/" + path);

    if (!readFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Project read failed";
        return ;
    }

    QByteArray readByteArray = readFile.readAll();
    QJsonDocument readDoc(QJsonDocument::fromJson(readByteArray));
    QJsonObject rootObj = readDoc.object();

    QJsonArray nodes = rootObj[JSON_ATTRIBUTE_NODE_SET].toArray();

    QString strUUID = "";
    QString strNodeType = "";
    QString strNextNodeID = "";

    pModelProject->IDStartNode = QUuid(rootObj[JSON_ATTRIBUTE_START_NODE_ID].toString());

    for (int i = 0; i < nodes.size(); i++) {
        QJsonObject nodeObj = nodes[i].toObject();
        strUUID = nodeObj[JSON_ATTRIBUTE_UUID].toString();
        strNodeType = nodeObj[JSON_ATTRIBUTE_NODE_TYPE].toString();
        strNextNodeID = nodeObj[JSON_ATTRIBUTE_NEXT_NODE_ID].toString();

        QUuid uuid = QUuid(strUUID);
        QUuid nextNodeID = QUuid(strNextNodeID);
        ModelNode* pNode = nullptr;

        if (JSON_ATTRIBUTE_ASSIGN_VARIABLE == strNodeType) {
            pNode = new ModelNodeAssignVariable(uuid);
            ModelNodeAssignVariable* pNodeAssignVariable = static_cast<ModelNodeAssignVariable*>(pNode);
            pNodeAssignVariable->variableName = nodeObj[JSON_ATTRIBUTE_ASSIGN_VARIABLE_VARIABLE_NAME].toString();
            pNodeAssignVariable->assignType = static_cast<ModelNodeAssignVariable::ASSIGNTYPE>(nodeObj[JSON_ATTRIBUTE_ASSIGN_VARIABLE_ASSIGN_TYPE].toInt());
            pNodeAssignVariable->value1.isRreference = nodeObj[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET1_FLAG_REF].toBool();
            if (pNodeAssignVariable->value1.isRreference) {
                pNodeAssignVariable->value1.referenceName = nodeObj[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET1_VALUE].toString();
            }
            else {
                pNodeAssignVariable->value1.value = nodeObj[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET1_VALUE].toString().toDouble();
            }
            pNodeAssignVariable->value2.isRreference = nodeObj[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET2_FLAG_REF].toBool();
            if (pNodeAssignVariable->value2.isRreference) {
                pNodeAssignVariable->value2.referenceName = nodeObj[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET2_VALUE].toString();
            }
            else {
                pNodeAssignVariable->value2.value = nodeObj[JSON_ATTRIBUTE_ASSIGN_VARIABLE_TARGET2_VALUE].toString().toDouble();
            }
        }
        else if (JSON_ATTRIBUTE_MOVE_ROBOT == strNodeType) {
            pNode = new ModelNodeMoveRobot(uuid);
            ModelNodeMoveRobot* pNodeMoveRobot = static_cast<ModelNodeMoveRobot*>(pNode);
            pNodeMoveRobot->moveType = static_cast<ModelNodeMoveRobot::MOVETYPE>(nodeObj[JSON_ATTRIBUTE_MOVE_ROBOT_MOVETYPE].toInt());
            pNodeMoveRobot->flagRelative = nodeObj[JSON_ATTRIBUTE_MOVE_ROBOT_ISRELATIVE].toBool();
            QJsonArray arrayIsRelativeFlag = nodeObj[JSON_ATTRIBUTE_MOVE_ROBOT_VEC_ISRELATIVE].toArray();
            QJsonArray arrayTarget = nodeObj[JSON_ATTRIBUTE_MOVE_ROBOT_VEC_TARGET].toArray();
            for (int i = 0 ; i <6; i++) {
                pNodeMoveRobot->vectorTarget[i].isRreference = arrayIsRelativeFlag.at(i).toBool();
                if (pNodeMoveRobot->vectorTarget[i].isRreference) {
                    pNodeMoveRobot->vectorTarget[i].referenceName = arrayTarget.at(i).toString();
                }
                else {
                    pNodeMoveRobot->vectorTarget[i].value = arrayTarget.at(i).toDouble();
                }
            }
            pNodeMoveRobot->vel = nodeObj[JSON_ATTRIBUTE_MOVE_ROBOT_VEL].toDouble();
            pNodeMoveRobot->accel = nodeObj[JSON_ATTRIBUTE_MOVE_ROBOT_ACCEL].toDouble();
        }
        else if (JSON_ATTRIBUTE_CONDITIONAL == strNodeType) {
            pNode = new ModelNodeConditional(uuid);
            ModelNodeConditional* pNodeConditional = static_cast<ModelNodeConditional*>(pNode);
            pNodeConditional->conditionalType = static_cast<ModelNodeConditional::CONDITIONALTYPE>(nodeObj[JSON_ATTRIBUTE_CONDITIONAL_TYPE].toInt());
            pNodeConditional->conditionalEquationType = static_cast<ModelNodeConditional::CONDITIONALEQUATIONTYPE>(nodeObj[JSON_ATTRIBUTE_CONDITIONAL_EQUATION_TYPE].toInt());
            pNodeConditional->value1.isRreference = nodeObj[JSON_ATTRIBUTE_CONDITIONAL_TARGET1_IS_REF].toBool();
            if (pNodeConditional->value1.isRreference) {
                pNodeConditional->value1.referenceName = nodeObj[JSON_ATTRIBUTE_CONDITIONAL_TARGET1_VALUE].toString();
            }
            else {
                pNodeConditional->value1.value = nodeObj[JSON_ATTRIBUTE_CONDITIONAL_TARGET1_VALUE].toString().toDouble();
            }
            pNodeConditional->value2.isRreference = nodeObj[JSON_ATTRIBUTE_CONDITIONAL_TARGET2_IS_REF].toBool();
            if (pNodeConditional->value2.isRreference) {
                pNodeConditional->value2.referenceName = nodeObj[JSON_ATTRIBUTE_CONDITIONAL_TARGET2_VALUE].toString();
            }
            else {
                pNodeConditional->value2.value = nodeObj[JSON_ATTRIBUTE_CONDITIONAL_TARGET2_VALUE].toString().toDouble();
            }
            pNodeConditional->nextNodeID_conditionFalse = QUuid(nodeObj[JSON_ATTRIBUTE_CONDITIONAL_FALSE_NEXT_NODE_ID].toString());
        }
        else if (JSON_ATTRIBUTE_DELAY == strNodeType) {
            pNode = new ModelNodeDelay(uuid);
            ModelNodeDelay* pNodeDelay = static_cast<ModelNodeDelay*>(pNode);
            pNodeDelay->delayms = static_cast<unsigned int>(nodeObj[JSON_ATTRIBUTE_DELAY_DELAYMS].toInt());
        }
        else if (JSON_ATTRIBUTE_DIGITAL_INOUT == strNodeType) {
            pNode = new ModelNodeDigitalIO(uuid);
            ModelNodeDigitalIO* pNodeDigitalInOut = static_cast<ModelNodeDigitalIO*>(pNode);
            pNodeDigitalInOut->ioType = static_cast<ModelNodeDigitalIO::IOTYPE>(nodeObj[JSON_ATTRIBUTE_DIGITAL_INOUT_IOTYPE].toInt());
            QJsonArray array = nodeObj[JSON_ATTRIBUTE_DIGITAL_INOUT_VALUE].toArray();
            for (int i = 0 ; i < 8; i++) {
                pNodeDigitalInOut->listStatus[i] = array.at(i).toBool();
            }
            pNodeDigitalInOut->timeout = static_cast<unsigned int>(nodeObj[JSON_ATTRIBUTE_DIGITAL_INOUT_TIMEOUT].toInt());
        }
        else if (JSON_ATTRIBUTE_DUMMY == strNodeType) {
            pNode = new ModelNodeDummy(uuid);
        }
        pNode->nextNodeID = nextNodeID;
        pModelProject->getHashNode()->insert(pNode->getNodeID(), pNode);
    }
}

QString ProjectSaveLoadManager::__nodeTypeToString(ModelNode::NODETYPE type) {
    if (ModelNode::ASSIGN_VARIABLE == type) {
        return JSON_ATTRIBUTE_ASSIGN_VARIABLE;
    }
    else if (ModelNode::MOVE_ROBOT == type) {
        return JSON_ATTRIBUTE_MOVE_ROBOT;
    }
    else if (ModelNode::CONDITIONAL == type) {
        return JSON_ATTRIBUTE_CONDITIONAL;
    }
    else if (ModelNode::DELAY == type) {
        return JSON_ATTRIBUTE_DELAY;
    }
    else if (ModelNode::DIGITAL_INOUT == type) {
        return JSON_ATTRIBUTE_DIGITAL_INOUT;
    }
    else if (ModelNode::DUMMY == type) {
        return JSON_ATTRIBUTE_DUMMY;
    }
    return "ERROR";
}


