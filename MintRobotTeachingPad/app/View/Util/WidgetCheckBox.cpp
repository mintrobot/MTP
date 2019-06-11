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

#include "WidgetCheckBox.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetCheckBox::WidgetCheckBox(QWidget *parent, int id) : QWidget(parent) {
    this->ID = id;
    __pButtonChecked = new WidgetButton(this, 1);
    __pButtonChecked->setButtonImage(SingletonImage::GetInstance().ID_OK);
    __pButtonChecked->setColor(SingletonColor::GetInstance().ColorLabelError);

    __pButtonUnchecked = new WidgetButton(this, 2);
    __pButtonUnchecked->setText(" ");

    if (__flagChecked) {
        __pButtonChecked->setVisible(true);
        __pButtonUnchecked->setVisible(false);
    }
    else {
        __pButtonChecked->setVisible(false);
        __pButtonUnchecked->setVisible(true);
    }

    connect(__pButtonChecked, SIGNAL(onClick(int)), this, SLOT(changeCheckStatus(int)));
    connect(__pButtonUnchecked, SIGNAL(onClick(int)), this, SLOT(changeCheckStatus(int)));
}

WidgetCheckBox::~WidgetCheckBox() {

}

//_____________________________
void WidgetCheckBox::setButtonSize(int sizePixel) {
    __buttonSize = sizePixel;
}

void WidgetCheckBox::setCheckStatus(bool status) {
    __flagChecked = status;
    redraw();
}

bool WidgetCheckBox::getCheckStatus() {
    return __flagChecked;
}

//_______________________________________PROTECTED____________________________________//
void WidgetCheckBox::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event)
    redraw();
}

void WidgetCheckBox::redraw() {
    if (__flagChecked) {
        __pButtonChecked->setVisible(true);
        __pButtonUnchecked->setVisible(false);
    }
    else {
        __pButtonChecked->setVisible(false);
        __pButtonUnchecked->setVisible(true);
    }
    __pButtonChecked->setGeometry(0, 0, __buttonSize, __buttonSize);
    __pButtonUnchecked->setGeometry(0, 0, __buttonSize, __buttonSize);
}

//_______________________________________PRIVATE______________________________________//


//_______________________________________SLOTS________________________________________//
void WidgetCheckBox::changeCheckStatus(int id) {
    if (id == 1) {
        __flagChecked = false;
    }
    else {
        __flagChecked = true;
    }
    redraw();
    emit onChangeCheckStatus(ID, __flagChecked);
}
