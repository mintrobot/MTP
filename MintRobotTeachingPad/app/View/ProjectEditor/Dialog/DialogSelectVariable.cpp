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

#include "DialogSelectVariable.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogSelectVariable::DialogSelectVariable(QWidget *parent) : Dialog(parent) {

    setSize(20, 50);
    setTitle("Select Variable");

    __pListWidgetScrollArea = new QListWidget(getContentsWidget());
    __pListWidgetScrollArea->setStyleSheet("background-color:transparent;");
     connect(__pListWidgetScrollArea, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(updateVariableAssign(QListWidgetItem*)));

}

DialogSelectVariable::~DialogSelectVariable() {

}

//_______________________________________PUBLIC_______________________________________//
void DialogSelectVariable::initValues() {
    __strValue = "0";
}

QString DialogSelectVariable::getValue() {
    return __strValue;
}

void DialogSelectVariable::setVariableIDList(const QList<QString>& listVariableName) {
    __pListWidgetScrollArea->clear();
    QString strVariableName;
    for (int i = 0 ; i < listVariableName.size(); i++) {
        strVariableName = listVariableName.at(i);
        __pListWidgetScrollArea->addItem(strVariableName);
        __pListWidgetScrollArea->item(i)->setForeground(SingletonColor::GetInstance().ColorLabelEmphasize3);
    }
}



//_______________________________________PROTECTED____________________________________//
void DialogSelectVariable::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);

    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);
    __widthContentsSection = static_cast<int>(_widthContentsBox * __ratioWidthLabelValue / 100);
    __heightContentsSection = static_cast<int>(_heightContentsBox * __ratioHeightContentsSection / 100);
    __heightItemInVariableList = static_cast<int>(__heightContentsSection * __ratioHeightItemInVariableList / 100);

    __pListWidgetScrollArea->setGeometry(__widthMargin, __heightMargin, __widthContentsSection, __heightContentsSection);
    __pListWidgetScrollArea->setFont(SingletonFont::GetInstance().getFontLight(__heightItemInVariableList));
}


//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void DialogSelectVariable::updateVariableAssign(QListWidgetItem* pItem) {
    __strValue = pItem->text();
}
