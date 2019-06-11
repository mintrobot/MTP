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

#include "DialogNodeDelay.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogNodeDelay::DialogNodeDelay(QWidget *parent) : DialogNode(parent, PROJECT_EDITOR_DIALOG_DELAY) {
    setSize(25, 60);
    setTitle("Delay");

    __pLabel = new WidgetLabel(getContentsWidget());
    __pLabel->setText("Delay (ms)");
    __pLabel->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pLabelValue = new WidgetLabel(getContentsWidget());
    __pLabelValue->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelValue->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);
    __pLabelValue->setText("");

    // init keypad
    __pKeypadNumber = new WidgetKeypad(getContentsWidget());
    __pKeypadNumber->setSignButtonVisiableMode(false);

    // init connections
    connect(__pKeypadNumber, SIGNAL(onUpdateValue(QString)), this, SLOT(updateValue(QString)));
}

DialogNodeDelay::~DialogNodeDelay() {

}


//_______________________________________PUBLIC_______________________________________//
void DialogNodeDelay::initValue() {
    updateValue("0");
    __pKeypadNumber->setStringValue("");
}

void DialogNodeDelay::setValue(const ModelNodeDelay& modelNodeDelay) {
    __modelNodeDelay.cloneData(modelNodeDelay);
    __pLabelValue->setText(QString::number(__modelNodeDelay.delayms));
}

const ModelNodeDelay& DialogNodeDelay::getValue() {
    return __modelNodeDelay;
}


//_______________________________________PROTECTED____________________________________//
void DialogNodeDelay::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);
    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);

    __widthLabel = static_cast<int>(_widthContentsBox * __ratioWidthLabel / 100);
    __heightLabel = static_cast<int>(_heightContentsBox * __ratioHeightLabel / 100);
    __widthLabelValue = static_cast<int>(_widthContentsBox * __ratioWidthLabelValue / 100);    __widthKeypad = static_cast<int>(_widthContentsBox * __ratioWidthKeypad / 100);
    __heightKeypad = static_cast<int>(_heightContentsBox * __ratioHeightKeypad / 100);

    __pLabel->setGeometry(__widthMargin, __heightMargin, __widthLabel, __heightLabel);
    __pLabelValue->setGeometry(__widthLabel + __widthMargin*2,
                               __heightMargin,
                               __widthLabelValue,
                               __heightLabel);
    __pKeypadNumber->setGeometry(__widthMargin, __heightLabel + __heightMargin*2, __widthKeypad, __heightKeypad);

}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void DialogNodeDelay::updateValue(QString value) {
    __pLabelValue->setText(value);
    __modelNodeDelay.delayms = value.toUInt();
}

