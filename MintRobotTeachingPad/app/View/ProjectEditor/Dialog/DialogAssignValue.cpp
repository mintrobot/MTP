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

#include "DialogAssignValue.h"

DialogAssignValue::DialogAssignValue(QWidget *parent) : Dialog (parent) {

    setSize(40, 50);
    setTitle("Assign Variable");

    __pLabelValue = new WidgetLabel(getContentsWidget());
    __pLabelValue->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelValue->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);
    __pLabelValue->setText(__strValue);

    __pLabelVariableSection = new WidgetLabel(getContentsWidget());
    __pLabelVariableSection->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelVariableSection->setText("SELECT EXISTING VARIABLE");
    __pLabelDirectSection = new WidgetLabel(getContentsWidget());
    __pLabelDirectSection->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelDirectSection->setText("DIRECT ASSIGN");

    __pListWidgetScrollArea = new QListWidget(getContentsWidget());
    __pListWidgetScrollArea->setStyleSheet("background-color:transparent;");

    __pWidgetKeypad = new WidgetKeypad(getContentsWidget());
    __pWidgetKeypad->setSignButtonVisiableMode(true);

     connect(__pWidgetKeypad, SIGNAL(onUpdateValue(QString)), this, SLOT(updateDirectAssign(QString)));
     connect(__pListWidgetScrollArea, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(updateVariableAssign(QListWidgetItem*)));

}

DialogAssignValue::~DialogAssignValue() {

}

void DialogAssignValue::setVariableIDList(const QList<QString>& listVariableName) {

    __pListWidgetScrollArea->clear();

    QString strVariableName;
    for (int i = 0 ; i < listVariableName.size(); i++) {
        strVariableName = listVariableName.at(i);
        __pListWidgetScrollArea->addItem(strVariableName);
        __pListWidgetScrollArea->item(i)->setForeground(SingletonColor::GetInstance().ColorLabelEmphasize3);
    }
}

//_______________________________________CONSTRUCTOR__________________________________//

//_______________________________________PUBLIC_______________________________________//
void DialogAssignValue::initValues() {
    __pWidgetKeypad->setStringValue("");
    __strValue = "0";
    __pLabelValue->setText(__strValue);
    flagVariable = false;
}

QString DialogAssignValue::getValue() {
    return __strValue;
}

//_______________________________________PROTECTED____________________________________//
void DialogAssignValue::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);

    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);
    __widthLabelValue = static_cast<int>(_widthContentsBox * __ratioWidthLabelValue / 100);
    __heightLabelValue = static_cast<int>(_heightContentsBox * __ratioHeightLabelValue / 100);
    __widthSection = static_cast<int>(_widthContentsBox * __ratioWidthLabelSection / 100);
    __heightLabelSection = static_cast<int>(_heightContentsBox * __ratioHeightLabelSection / 100);
    __heightContentsSection = static_cast<int>(_heightContentsBox * __ratioHeightContentsSection / 100);
    __heightVariableButton = static_cast<int>(__heightContentsSection * __ratioHeightVariableButton / 100);
    __heightItemInVariableList = static_cast<int>(__heightContentsSection * __ratioHeightItemInVariableList / 100);

    __pLabelValue->setGeometry(__widthMargin, __heightMargin, __widthLabelValue, __heightLabelValue);
    __pLabelValue->setTextHeightRatio(0.6);
    __pLabelVariableSection->setGeometry(__widthMargin, __heightMargin*2 + __heightLabelValue, __widthSection, __heightLabelSection);
    __pLabelDirectSection->setGeometry(__widthMargin*2 + __widthSection, __heightMargin*2 + __heightLabelValue, __widthSection, __heightLabelSection);

    __pListWidgetScrollArea->setGeometry(__widthMargin, __heightMargin*3 + __heightLabelValue + __heightLabelSection, __widthSection, __heightContentsSection);
    __pListWidgetScrollArea->setFont(SingletonFont::GetInstance().getFontLight(__heightItemInVariableList));

    __pWidgetKeypad->setGeometry(__widthMargin*2 + __widthSection, __heightMargin*3 + __heightLabelValue + __heightLabelSection, __widthSection, __heightContentsSection);

}


//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void DialogAssignValue::updateDirectAssign(QString value) {
    flagVariable = false;
    __strValue = value;
    __pLabelValue->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);
    __pLabelValue->setText(__strValue);
}

void DialogAssignValue::updateVariableAssign(QListWidgetItem* pItem) {
    flagVariable = true;
    __strValue = pItem->text();
    __pLabelValue->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize3);
    __pLabelValue->setText(__strValue);
}


