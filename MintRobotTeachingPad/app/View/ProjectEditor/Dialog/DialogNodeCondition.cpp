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

#include "DialogNodeCondition.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogNodeCondition::DialogNodeCondition(QWidget *parent) : DialogNode(parent, PROJECT_EDITOR_DIALOG_CONDITIONAL) {

    setSize(30, 8);

    __pLabelCondition = new WidgetLabel(getContentsWidget());
    __pLabelCondition->setText("Condition");

    __pButtonTarget1 = new WidgetButton(getContentsWidget(), 1);
    __pButtonTarget1->setRoundRatio(0.1);
    __pButtonTarget1->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonTarget1->setText("0");

    __pButtonTarget2 = new WidgetButton(getContentsWidget(), 2);
    __pButtonTarget2->setRoundRatio(0.1);
    __pButtonTarget2->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonTarget2->setText("0");

    __pButtonCompareCondition = new WidgetButton(getContentsWidget());
    __pButtonCompareCondition->setRoundRatio(0.1);
    __pButtonCompareCondition->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonCompareCondition->setText("==");

    __pDialogSelectVariable = new DialogAssignValue(this);
    __pDialogSelectVariable->setVisible(false);

    __pDialogSelectCompareCondition = new DialogSelectCompareCondition(this);
    __pDialogSelectCompareCondition->setVisible(false);

    connect(__pButtonTarget1, SIGNAL(onClick(int)), this, SLOT(openDialogSelectVariable(int)));
    connect(__pButtonTarget2, SIGNAL(onClick(int)), this, SLOT(openDialogSelectVariable(int)));
    connect(__pButtonCompareCondition, SIGNAL(onClick(int)), this, SLOT(openDialogSelectAssignCondition()));
    connect(__pDialogSelectVariable, SIGNAL(onDialogClickOK(int)), this, SLOT(slotAssignVariableValue()));
    connect(__pDialogSelectCompareCondition, SIGNAL(onDialogClickOK(int)), this, SLOT(slotAssignCondition()));

}

DialogNodeCondition::~DialogNodeCondition() {

}

//_______________________________________PUBLIC_______________________________________//
void DialogNodeCondition::initValue(ModelNodeConditional::CONDITIONALTYPE type) {
    __modelNodeConditional.conditionalType = type;
    __modelNodeConditional.conditionalEquationType = ModelNodeConditional::EQUAL;
    __modelNodeConditional.value1.isRreference = false;
    __modelNodeConditional.value1.value = 0;
    __modelNodeConditional.value1.referenceName = "";
    __modelNodeConditional.value2.isRreference = false;
    __modelNodeConditional.value2.value = 0;
    __modelNodeConditional.value2.referenceName = "";
    __updateTexts();
    __pDialogSelectVariable->initValues();
}

void DialogNodeCondition::setValue(const ModelNodeConditional& modelNodeConditional) {
    __modelNodeConditional.cloneData(modelNodeConditional);
    __updateTexts();
}

const ModelNodeConditional& DialogNodeCondition::getValue() {
    return __modelNodeConditional;
}

void DialogNodeCondition::setVariableIDList(const QList<QString>& listVariableName) {
    __pDialogSelectVariable->setVariableIDList(listVariableName);
}


//_______________________________________PROTECTED____________________________________//
void DialogNodeCondition::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);
    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);

    __heightItem = static_cast<int>(_heightContentsBox * __ratioHeightItem / 100);
    __widthLabel = static_cast<int>(_widthContentsBox * __ratioWidthLabel / 100);
    __widthButton = static_cast<int>(_widthContentsBox * __ratioWidthButton / 100);

    __pLabelCondition->setGeometry(__widthMargin,
                          __heightMargin,
                          __widthLabel,
                          __heightItem);

    __pButtonTarget1->setGeometry(__widthLabel + __widthMargin*2,
                                   __heightMargin,
                                   __widthButton,
                                   __heightItem);

    __pButtonCompareCondition->setGeometry(__widthLabel + __widthButton + __widthMargin*3,
                                          __heightMargin,
                                          __widthButton,
                                          __heightItem);

    __pButtonTarget2->setGeometry(__widthLabel + __widthButton*2 + __widthMargin*4,
                                          __heightMargin,
                                          __widthButton,
                                          __heightItem);


    __pDialogSelectVariable->setGeometry(0, 0, width(), height());
    __pDialogSelectCompareCondition->setGeometry(0, 0, width(), height());
}

//_______________________________________PRIVATE______________________________________//
void DialogNodeCondition::__updateTexts() {

    if (__modelNodeConditional.value1.isRreference) {
        __pButtonTarget1->setText(__modelNodeConditional.value1.referenceName);
    }
    else {
        __pButtonTarget1->setText(QString::number(__modelNodeConditional.value1.value));
    }

    if (__modelNodeConditional.value2.isRreference) {
        __pButtonTarget2->setText(__modelNodeConditional.value2.referenceName);
    }
    else {
        __pButtonTarget2->setText(QString::number(__modelNodeConditional.value2.value));
    }

    switch(__modelNodeConditional.conditionalType) {

    case ModelNodeConditional::IF:
        setTitle("If");
        break;
    case ModelNodeConditional::ELSEIF:
        setTitle("Else If");
        break;
    case ModelNodeConditional::ELSE:
        setTitle("Else");
        break;
    case ModelNodeConditional::LOOP:
        setTitle("Loop");
        break;
    }

    switch(__modelNodeConditional.conditionalEquationType) {
    case ModelNodeConditional::EQUAL:
        __pButtonCompareCondition->setText("==");
        break;
    case ModelNodeConditional::LESS:
        __pButtonCompareCondition->setText("<");
        break;
    case ModelNodeConditional::LESS_EQUAL:
        __pButtonCompareCondition->setText("<=");
        break;
    case ModelNodeConditional::GREATER:
        __pButtonCompareCondition->setText(">");
        break;
    case ModelNodeConditional::GREATER_EQUAL:
        __pButtonCompareCondition->setText(">=");
        break;
    case ModelNodeConditional::DIFFERENT:
        __pButtonCompareCondition->setText("!=");
        break;
    }
}

//_______________________________________SLOTS________________________________________//
void DialogNodeCondition::openDialogSelectAssignCondition() {
    __pDialogSelectCompareCondition->setVisible(true);
}

void DialogNodeCondition::openDialogSelectVariable(int index) {
    __pDialogSelectVariable->initValues();
    __pDialogSelectVariable->setVisible(true);
    __indexCurrentEditTarget = index;
}

void DialogNodeCondition::slotAssignVariableValue() {
    QString value = __pDialogSelectVariable->getValue();
    if (__indexCurrentEditTarget == 1) {
        if (__pDialogSelectVariable->flagVariable) {
            __modelNodeConditional.value1.isRreference = true;
            __modelNodeConditional.value1.referenceName = value;
        }
        else {
            __modelNodeConditional.value1.isRreference = false;
            __modelNodeConditional.value1.value = value.toDouble();
        }
    }
    else if (__indexCurrentEditTarget == 2) {
        if (__pDialogSelectVariable->flagVariable) {
            __modelNodeConditional.value2.isRreference = true;
            __modelNodeConditional.value2.referenceName = value;
        }
        else {
            __modelNodeConditional.value2.isRreference = false;
            __modelNodeConditional.value2.value = value.toDouble();
        }
    }
    __updateTexts();
}

void DialogNodeCondition::slotAssignCondition() {
    DialogSelectCompareCondition::COMPARE_CONDITION compareCondition = __pDialogSelectCompareCondition->getCompareCondition();

    if (compareCondition == DialogSelectCompareCondition::EQUAL) {
        __pButtonCompareCondition->setText("==");
        __modelNodeConditional.conditionalEquationType = ModelNodeConditional::EQUAL;
    }
    else if (compareCondition == DialogSelectCompareCondition::GREATER) {
        __pButtonCompareCondition->setText(">");
        __modelNodeConditional.conditionalEquationType = ModelNodeConditional::GREATER;
    }
    else if (compareCondition == DialogSelectCompareCondition::GREATER_EQUAL) {
        __pButtonCompareCondition->setText(">=");
        __modelNodeConditional.conditionalEquationType = ModelNodeConditional::GREATER_EQUAL;
    }
    else if (compareCondition == DialogSelectCompareCondition::LESS) {
        __pButtonCompareCondition->setText("<");
        __modelNodeConditional.conditionalEquationType = ModelNodeConditional::LESS;
    }
    else if (compareCondition == DialogSelectCompareCondition::LESS_EQUAL) {
        __pButtonCompareCondition->setText("<=");
        __modelNodeConditional.conditionalEquationType = ModelNodeConditional::LESS_EQUAL;
    }
    else if (compareCondition == DialogSelectCompareCondition::DIFFERENT) {
        __pButtonCompareCondition->setText("!=");
        __modelNodeConditional.conditionalEquationType = ModelNodeConditional::DIFFERENT;
    }
}
