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

#include "DialogNodeAssignVariable.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogNodeAssignVariable::DialogNodeAssignVariable(QWidget *parent) : DialogNode(parent, PROJECT_EDITOR_DIALOG_ASSIGN_VARIABLE) {

    setTitle("Variable Assignment");
    setSize(30, 16);

    __pLabelName = new WidgetLabel(getContentsWidget());
    __pLabelName->setText("Name");

    __pLabelValue = new WidgetLabel(getContentsWidget());
    __pLabelValue->setText("Value");

    __pButtonName = new WidgetButton(getContentsWidget(), 0);
    __pButtonName->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonName->setRoundRatio(0.1);
    __pButtonName->setTextAlign(WidgetLabel::ALIGN_CENTER);
    __pButtonName->setText("");

    __pButtonSelectVariable = new WidgetButton(getContentsWidget(), 1);
    __pButtonSelectVariable->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonSelectVariable->setRoundRatio(0.1);
    __pButtonSelectVariable->setTextAlign(WidgetLabel::ALIGN_CENTER);
    __pButtonSelectVariable->setText("Select");


    __pButtonTarget1 = new WidgetButton(getContentsWidget(), 1);
    __pButtonTarget1->setRoundRatio(0.1);
    __pButtonTarget1->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonTarget1->setText("0");

    __pButtonTarget2 = new WidgetButton(getContentsWidget(), 2);
    __pButtonTarget2->setRoundRatio(0.1);
    __pButtonTarget2->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonTarget2->setText("0");
    __pButtonTarget2->setVisible(false);

    __pButtonAssignOperator = new WidgetButton(getContentsWidget());
    __pButtonAssignOperator->setRoundRatio(0.1);
    __pButtonAssignOperator->setTextAlign(WidgetLabel::ALIGN_CENTER);
    __pButtonAssignOperator->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonAssignOperator->setText(" ");


    __pDialogKeyboard = new DialogKeyboard(this);
    __pDialogKeyboard->setVisible(false);

    __pDialogSelectAssignOperator = new DialogSelectAssignOperator(this);
    __pDialogSelectAssignOperator->setVisible(false);

    __pDialogAssignValue = new DialogAssignValue(this);
    __pDialogAssignValue->setVisible(false);

    __pDialogSelectVariable = new DialogSelectVariable(this);
    __pDialogSelectVariable->setVisible(false);

    connect(__pButtonName, SIGNAL(onClick(int)), this, SLOT(slotOpenDialogKeyboard()));
    connect(__pButtonSelectVariable, SIGNAL(onClick(int)), this, SLOT(slotOpenDialogSelectVariable()));
    connect(__pButtonTarget1, SIGNAL(onClick(int)), this, SLOT(slotOpenDialogAssignVariable(int)));
    connect(__pButtonTarget2, SIGNAL(onClick(int)), this, SLOT(slotOpenDialogAssignVariable(int)));
    connect(__pButtonAssignOperator, SIGNAL(onClick(int)), this, SLOT(slotOpenDialogSelectAssignOperator()));

    connect(__pDialogKeyboard, SIGNAL(onDialogClickOK(int)), this, SLOT(slotAssignVariableName()));
    connect(__pDialogSelectVariable, SIGNAL(onDialogClickOK(int)), this, SLOT(slotAssignSelectedVariable()));
    connect(__pDialogAssignValue, SIGNAL(onDialogClickOK(int)), this, SLOT(slotAssignVariableValue()));
    connect(__pDialogSelectAssignOperator, SIGNAL(onDialogClickOK(int)), this, SLOT(slotAssignOperator()));

}

DialogNodeAssignVariable::~DialogNodeAssignVariable() {

    delete __pLabelName;
    delete __pLabelValue;
    delete __pButtonName;
}

//_______________________________________PUBLIC_______________________________________//
void DialogNodeAssignVariable::initValue() {

    __modelNodeAssignVariable.variableName = "var";
    __modelNodeAssignVariable.assignType = ModelNodeAssignVariable::EQUAL;
    __modelNodeAssignVariable.value1.isRreference = false;
    __modelNodeAssignVariable.value1.value = 0;
    __modelNodeAssignVariable.value1.referenceName = "";
    __modelNodeAssignVariable.value2.isRreference = false;
    __modelNodeAssignVariable.value2.value = 0;
    __modelNodeAssignVariable.value2.referenceName = "";
    __updateTexts();
}

void DialogNodeAssignVariable::setValue(const ModelNodeAssignVariable& modelAssignVariable) {
    __modelNodeAssignVariable.cloneData(modelAssignVariable);
    __updateTexts();
}

const ModelNodeAssignVariable& DialogNodeAssignVariable::getValue() {
    return __modelNodeAssignVariable;
}


void DialogNodeAssignVariable::setVariableIDList(const QList<QString>& listVariableName) {
    __pDialogAssignValue->setVariableIDList(listVariableName);
    __pDialogSelectVariable->setVariableIDList(listVariableName);
}

//_______________________________________PROTECTED____________________________________//
void DialogNodeAssignVariable::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);
    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);

    __heightItem = static_cast<int>(_heightContentsBox * __ratioHeightItem / 100);
    __widthLabel = static_cast<int>(_widthContentsBox * __ratioWidthLabel / 100);
    __widthButtonName = static_cast<int>(_widthContentsBox * __ratioWidthButtonName / 100);
    __widthButtonSelectVariable = static_cast<int>(_widthContentsBox * __ratioWidthButtonSelectVariable / 100);
    __widthAssignButtons = static_cast<int>(_widthContentsBox * __ratioWidthAssignButtons / 100);

    __pLabelName->setGeometry(__widthMargin,
                              __heightMargin,
                              __widthLabel,
                              __heightItem);

    __pButtonName->setGeometry(__widthLabel + __widthMargin*2,
                               __heightMargin,
                               __widthButtonName,
                               __heightItem);

    __pButtonSelectVariable->setGeometry(__widthLabel + __widthButtonName + __widthMargin*3,
                                         __heightMargin,
                                         __widthButtonSelectVariable,
                                         __heightItem);

    __pLabelValue->setGeometry(__widthMargin,
                               __heightItem + __heightMargin*2,
                               __widthLabel,
                               __heightItem);

    __pButtonTarget1->setGeometry(__widthLabel + __widthMargin*2,
                                   __heightMargin*2 + __heightItem,
                                   __widthAssignButtons,
                                   __heightItem);

    __pButtonAssignOperator->setGeometry(__widthLabel + __widthAssignButtons + __widthMargin*3,
                                          __heightMargin*2 + __heightItem,
                                          __widthAssignButtons,
                                          __heightItem);

    __pButtonTarget2->setGeometry(__widthLabel + __widthAssignButtons*2 + __widthMargin*4,
                                          __heightMargin*2 + __heightItem,
                                          __widthAssignButtons,
                                          __heightItem);


    __pDialogKeyboard->setGeometry(0, 0, width(), height());
    __pDialogSelectVariable->setGeometry(0, 0, width(), height());
    __pDialogAssignValue->setGeometry(0, 0, width(), height());
    __pDialogSelectAssignOperator->setGeometry(0, 0, width(), height());
}

//_______________________________________PRIVATE______________________________________//
void DialogNodeAssignVariable::__updateTexts() {
    __pButtonName->setText(__modelNodeAssignVariable.variableName);

    if (__modelNodeAssignVariable.value1.isRreference) {
        __pButtonTarget1->setText(__modelNodeAssignVariable.value1.referenceName);
    }
    else {
        __pButtonTarget1->setText(QString::number(__modelNodeAssignVariable.value1.value));
    }

    if (__modelNodeAssignVariable.value2.isRreference) {
        __pButtonTarget2->setText(__modelNodeAssignVariable.value2.referenceName);
    }
    else {
        __pButtonTarget2->setText(QString::number(__modelNodeAssignVariable.value2.value));
    }

    switch(__modelNodeAssignVariable.assignType) {
    case ModelNodeAssignVariable::EQUAL:
        __pButtonAssignOperator->setText(" ");
        __pButtonTarget2->hide();
        break;
    case ModelNodeAssignVariable::PLUS:
        __pButtonAssignOperator->setText("+");
        __pButtonTarget2->show();
        break;
    case ModelNodeAssignVariable::MINUS:
        __pButtonAssignOperator->setText("-");
        __pButtonTarget2->show();
        break;
    case ModelNodeAssignVariable::MULTIPLY:
        __pButtonAssignOperator->setText("*");
        __pButtonTarget2->show();
        break;
    case ModelNodeAssignVariable::DIVIDE:
        __pButtonAssignOperator->setText("/");
        __pButtonTarget2->show();
        break;
    }
}

//_______________________________________SLOTS________________________________________//
void DialogNodeAssignVariable::slotOpenDialogKeyboard() {
    __pDialogKeyboard->setText(__pButtonName->getText());
    __pDialogKeyboard->setVisible(true);
}

void DialogNodeAssignVariable::slotOpenDialogSelectVariable() {
    __pDialogSelectVariable->setVisible(true);
}

void DialogNodeAssignVariable::slotOpenDialogAssignVariable(int index) {
    __pDialogAssignValue->initValues();
    __pDialogAssignValue->setVisible(true);
    __indexCurrentEditTarget = index;
}

void DialogNodeAssignVariable::slotOpenDialogSelectAssignOperator() {
    __pDialogSelectAssignOperator->setVisible(true);
}

void DialogNodeAssignVariable::slotAssignVariableName() {
    __modelNodeAssignVariable.variableName = __pDialogKeyboard->getValue();
    __updateTexts();
}

void DialogNodeAssignVariable::slotAssignSelectedVariable() {
    __modelNodeAssignVariable.variableName = __pDialogSelectVariable->getValue();
    __updateTexts();
}

void DialogNodeAssignVariable::slotAssignVariableValue() {
    QString value = __pDialogAssignValue->getValue();
    bool flagVariable = __pDialogAssignValue->flagVariable;
    if (flagVariable) {
        if (__indexCurrentEditTarget == 1) {
            __modelNodeAssignVariable.value1.isRreference = true;
            __modelNodeAssignVariable.value1.referenceName = __pDialogAssignValue->getValue();
        }
        else if (__indexCurrentEditTarget == 2) {
            __modelNodeAssignVariable.value2.isRreference = false;
            __modelNodeAssignVariable.value2.value = __pDialogAssignValue->getValue().toDouble();
        }
    }
    else {
        if (__indexCurrentEditTarget == 1) {
            __modelNodeAssignVariable.value1.isRreference = true;
            __modelNodeAssignVariable.value1.referenceName = __pDialogAssignValue->getValue();
        }
        else if (__indexCurrentEditTarget == 2) {
            __modelNodeAssignVariable.value2.isRreference = false;
            __modelNodeAssignVariable.value2.value = __pDialogAssignValue->getValue().toDouble();
        }
    }
    __updateTexts();
}

void DialogNodeAssignVariable::slotAssignOperator() {
    int operatorIndex = __pDialogSelectAssignOperator->getAssignOperator();
    switch (operatorIndex) {
    case 0:
        __modelNodeAssignVariable.assignType = ModelNodeAssignVariable::EQUAL;
        break;
    case 1:
        __modelNodeAssignVariable.assignType = ModelNodeAssignVariable::PLUS;
        break;
    case 2:
        __modelNodeAssignVariable.assignType = ModelNodeAssignVariable::MINUS;
        break;
    case 3:
        __modelNodeAssignVariable.assignType = ModelNodeAssignVariable::MULTIPLY;
        break;
    case 4:
        __modelNodeAssignVariable.assignType = ModelNodeAssignVariable::DIVIDE;
        break;
    }
    __updateTexts();
}
