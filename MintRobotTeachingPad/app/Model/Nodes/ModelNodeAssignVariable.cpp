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

#include "ModelNodeAssignVariable.h"

ModelNodeAssignVariable::ModelNodeAssignVariable(QUuid uuid) : ModelNode(uuid) {

}

ModelNodeAssignVariable::~ModelNodeAssignVariable() {

}

void ModelNodeAssignVariable::cloneData(const ModelNodeAssignVariable& modelNodeAssignVariable) {
    variableName = modelNodeAssignVariable.variableName;
    assignType = modelNodeAssignVariable.assignType;
    value1.isRreference = modelNodeAssignVariable.value1.isRreference;
    value1.value = modelNodeAssignVariable.value1.value;
    value1.referenceName = modelNodeAssignVariable.value1.referenceName;
    value2.isRreference = modelNodeAssignVariable.value2.isRreference;
    value2.value = modelNodeAssignVariable.value2.value;
    value2.referenceName = modelNodeAssignVariable.value2.referenceName;
}

QString ModelNodeAssignVariable::getArgumentsString() {

    QString res = "[";
    res += variableName + "]";
    res += "[";
    res += value1.getValueInStringFormat();
    res += "]";
    if (assignType == PLUS) {
        res += "[";
        res += " + ";
        res += "]";
    }
    else if (assignType == MINUS) {
        res += "[";
        res += " - ";
        res += "]";
    }
    else if (assignType == MULTIPLY) {
        res += "[";
        res += " * ";
        res += "]";
    }
    else if (assignType == DIVIDE) {
        res += "[";
        res += " / ";
        res += "]";
    }
    else {
        return res;
    }
    res += "[";
    res += value2.getValueInStringFormat();
    res += "]";
    return res;
}

QUuid ModelNodeAssignVariable::execute() {
    ModelProject* pProject = SingletonRuntimeProject::GetInstance().getProjectModel();
    double target1 = 0;
    double target2 = 0;
    double assignValue = 0;
    if (!value1.isRreference) {
        target1 = value1.value;
    }
    else {
        target1 = pProject->getVariableValue(value1.referenceName);
    }
    if (!value2.isRreference) {
        target2 = value2.value;
    }
    else {
        target2 = pProject->getVariableValue(value2.referenceName);
    }

    if (assignType == EQUAL) {
        assignValue = target1;
    }
    else if (assignType == PLUS) {
        assignValue = target1 + target2;
    }
    else if (assignType == MINUS) {
        assignValue = target1 - target2;
    }
    else if (assignType == MULTIPLY) {
        assignValue = target1 * target2;
    }
    else if (assignType == DIVIDE) {
        assignValue = target1 / target2;
    }
    pProject->getHashVariable()->insert(variableName, assignValue);
    return nextNodeID;
}
