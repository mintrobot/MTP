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

#include "DialogKeypad.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogKeypad::DialogKeypad(QWidget *parent) : Dialog(parent) {
    // Width/Height ratio should be 10:9 when normal keyboard
    setSize(25, 45);
    setTitle("Keypad");
    __pLabelText = new WidgetLabel(getContentsWidget());
    __pLabelText->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);
    __pLabelText->setText(__strText);

    __pWidgetKeypad = new WidgetKeypad(getContentsWidget());
    __pWidgetKeypad->setSignButtonVisiableMode(false);

    connect(__pWidgetKeypad, SIGNAL(onUpdateValue(QString)), this, SLOT(changeValue(QString)));
}

DialogKeypad::~DialogKeypad() {
    delete __pLabelText;
}

//_______________________________________PUBLIC_______________________________________//
void DialogKeypad::setText(QString projectName) {
    __strText = projectName;
    __pLabelText->setText(__strText);
    __pWidgetKeypad->setStringValue(__strText);
}

QString DialogKeypad::getText() {
    return __strText;
}

void DialogKeypad::setSignButtonVisiable(bool visiable) {
    __pWidgetKeypad->setSignButtonVisiableMode(visiable);
    __pWidgetKeypad->update();
}

//_______________________________________PROTECTED____________________________________//
void DialogKeypad::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);

    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);
    __heightText = static_cast<int>(_widthContentsBox * __ratioHeightText / 100);

    __pLabelText->setGeometry(__widthMargin, __heightMargin, _widthContentsBox - __widthMargin * 5, __heightText);
    __pLabelText->setTextHeightRatio(0.6);

    __pWidgetKeypad->setGeometry(__widthMargin, __heightText + __heightMargin * 2, _widthContentsBox - __widthMargin*2, _heightContentsBox - __heightText - __heightMargin * 3);
}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void DialogKeypad::onClickOkBtn(int id) {
    Q_UNUSED(id)
    emit onClick(__strText);
}

void DialogKeypad::onClickCancelBtn(int id) {
    Q_UNUSED(id)
    emit onClickCancel();
}

void DialogKeypad::changeValue(QString value) {
    __strText = value;
    __pLabelText->setText(value);
}
