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

#include "WidgetSlideSwitch.h"

//--- Constructor
WidgetSlideSwitch::WidgetSlideSwitch(QWidget *parent, int widgetId) : MTPWidget (parent, widgetId) {

    __pWidgetRectBackground = new WidgetRect(this);
    __pWidgetRectBackground->setRoundRatio(0.1);
    __pWidgetRectButton = new WidgetRect(this);
    __pWidgetRectButton->setRoundRatio(0.1);
}

WidgetSlideSwitch::~WidgetSlideSwitch() {

}

//--- Public
void WidgetSlideSwitch::setStatus(bool status) {
    __status = status;
    __pWidgetRectBackground->setGeometry(0, 0, width(), height());
    if (__status) {
        __pWidgetRectButton->setColor(__colorActiavte);
        __pWidgetRectButton->setGeometry(width()/2, 0, width()/2, height());
    }
    else {
        __pWidgetRectButton->setColor(__colorDeactivate);
        __pWidgetRectButton->setGeometry(0, 0, width()/2, height());
    }
}

bool WidgetSlideSwitch::getStatus() {
    return __status;
}

void WidgetSlideSwitch::setRoundRatio(double ratio) {
    __pWidgetRectBackground->setRoundRatio(ratio);
    __pWidgetRectButton->setRoundRatio(ratio);
    update();
}

void WidgetSlideSwitch::setClickable(bool clickable) {
    __clickable = clickable;
}

//--- Protected
void WidgetSlideSwitch::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);
    setStatus(__status);
}


void WidgetSlideSwitch::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    if (__clickable) {
        __status = !__status;
        setStatus(__status);
        emit onClick(getWidgetID());
    }
}
