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

#include "DialogKeyboard.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogKeyboard::DialogKeyboard(QWidget *parent) : Dialog(parent) {
    // Width/Height ratio should be 10:9 when normal keyboard
    setSize(50, 45);
    setTitle("Keyboard");
    __pLabelText = new WidgetLabel(getContentsWidget());
    __pLabelText->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize3);
    __pLabelText->setText(__strText);

    __pWidgetKeyboard = new WidgetKeyboard(getContentsWidget());
    __pWidgetKeyboard->setOperatorVisible(false);

    connect(__pWidgetKeyboard, SIGNAL(changeValue(QString)), this, SLOT(changeValue(QString)));
}

DialogKeyboard::~DialogKeyboard() {
    delete __pLabelText;
    delete __pWidgetKeyboard;
}

//_______________________________________PUBLIC_______________________________________//
void DialogKeyboard::initValue() {
    __strText = "";
    __pLabelText->setText(__strText);
}

void DialogKeyboard::setText(QString text) {
    __strText = text;
    __pLabelText->setText(text);
    __pWidgetKeyboard->setValue(text);
}

QString DialogKeyboard::getValue() {
    return __strText;
}

//_______________________________________PROTECTED____________________________________//
void DialogKeyboard::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);
    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);
    __heightText = static_cast<int>(_widthContentsBox * __ratioHeightText / 100);

    __pLabelText->setGeometry(__widthMargin * 10, 0, _widthContentsBox - __widthMargin * 5, __heightText);
    __pLabelText->setTextHeightRatio(0.6);

    __pWidgetKeyboard->setGeometry(0, __heightText, _widthContentsBox, _heightContentsBox - __heightText);
}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void DialogKeyboard::onClickOkBtn(int id) {
    Q_UNUSED(id)
    emit onClick(__strText);
}

void DialogKeyboard::onClickCancelBtn(int id) {
    Q_UNUSED(id)
    emit onClickCancel();
}

void DialogKeyboard::changeValue(QString value) {
    __strText = value;
    __pLabelText->setText(__strText);
}
