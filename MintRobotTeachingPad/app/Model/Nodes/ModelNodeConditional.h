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

#ifndef MODELNODECONDITIONAL_H
#define MODELNODECONDITIONAL_H

#include <QString>
#include "ModelNodeContainer.h"
#include "app/Controller/SingletonRuntimeProject.h"

#include "app/Model/Project/ModelValue.h"

#define EPS 1e-12

class ModelNodeConditional : public ModelNodeContainer
{
public:
    typedef enum contionalType {
        IF = 0,
        ELSEIF = 1,
        ELSE = 2,
        LOOP = 3,
    } CONDITIONALTYPE;

    typedef enum conditionalEquationType {
        EQUAL = 0,
        GREATER = 1,
        GREATER_EQUAL = 2,
        LESS = 3,
        LESS_EQUAL = 4,
        DIFFERENT = 5,
    } CONDITIONALEQUATIONTYPE;

    ModelNodeConditional(QUuid uuid = nullptr);
    virtual ~ModelNodeConditional() override;
    void cloneData(const ModelNodeConditional& modelNodeConditional);

    virtual NODETYPE getNodeType() override{
        return ModelNode::CONDITIONAL;
    }

    virtual QString getCommandString() override {
        switch (conditionalType) {
        case IF:
            return "IF";
        case ELSEIF:
            return "ELSEIF";
        case ELSE:
            return "ELSE";
        case LOOP:
            return "LOOP";
        }
        return "";
    }

    virtual QString getArgumentsString() override;
    virtual QUuid execute() override;


    ModelValue value1;
    ModelValue value2;

    CONDITIONALTYPE conditionalType = IF;
    CONDITIONALEQUATIONTYPE conditionalEquationType = EQUAL;

    QUuid nextNodeID_conditionFalse = nullptr;


protected:

private:


};

#endif // MODELNODECONDITIONAL_H
