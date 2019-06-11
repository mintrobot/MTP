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

#include "ModelNodeConditional.h"

ModelNodeConditional::ModelNodeConditional(QUuid uuid) : ModelNodeContainer(uuid) {

}

ModelNodeConditional::~ModelNodeConditional() {

}

void ModelNodeConditional::cloneData(const ModelNodeConditional& modelNodeConditional) {
    conditionalType = modelNodeConditional.conditionalType;
    conditionalEquationType = modelNodeConditional.conditionalEquationType;
    value1.isRreference = modelNodeConditional.value1.isRreference;
    value1.value = modelNodeConditional.value1.value;
    value1.referenceName = modelNodeConditional.value1.referenceName;
    value2.isRreference = modelNodeConditional.value2.isRreference;
    value2.value = modelNodeConditional.value2.value;
    value2.referenceName = modelNodeConditional.value2.referenceName;
}


QString ModelNodeConditional::getArgumentsString() {
    QString res;
    res += "[";
    res += value1.getValueInStringFormat();
    res += "]";

    if (EQUAL == conditionalEquationType) {
        res += "[==]";
    }
    else if (GREATER == conditionalEquationType) {
        res += "[>]";
    }
    else if (GREATER_EQUAL == conditionalEquationType) {
        res += "[>=]";
    }
    else if (LESS == conditionalEquationType) {
        res += "[<]";
    }
    else if (LESS_EQUAL == conditionalEquationType) {
        res += "[<=]";
    }
    else if (DIFFERENT == conditionalEquationType) {
        res += "[!=]";
    }

    res += "[" + value2.getValueInStringFormat() + "]";
    return res;
}

QUuid ModelNodeConditional::execute() {
    ModelProject* pProject = SingletonRuntimeProject::GetInstance().getProjectModel();
    double target1 = 0;
    double target2 = 0;
    bool condition = false;

    if (ELSE == conditionalType) {
        return nextNodeID;
    }

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

    if (EQUAL == conditionalEquationType) {
        if (fabs(target1 - target2) < EPS) {
            condition = true;
        }
    }
    else if (GREATER == conditionalEquationType) {
        if (target1 > target2) {
            condition = true;
        }
    }
    else if (GREATER_EQUAL == conditionalEquationType) {
        if (target1 > target2 || fabs(target1-target2) < EPS) {
            condition = true;
        }
    }
    else if (LESS == conditionalEquationType) {
        if (target1 < target2) {
            condition = true;
        }
    }
    else if (LESS_EQUAL == conditionalEquationType) {
        if (target1 < target2 || fabs(target1 - target2) < EPS) {
            condition = true;
        }
    }
    else if (DIFFERENT == conditionalEquationType) {
        if (fabs(target1 - target2) > EPS) {
            condition = true;
        }
    }

    if (condition) {
        return nextNodeID;
    }
    else {
        return nextNodeID_conditionFalse;
    }
}
