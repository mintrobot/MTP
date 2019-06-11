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

#include "WidgetSlider.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetSlider::WidgetSlider(QWidget *parent, bool flagVertical, int widgetId) : QWidget(parent) {
    __widgetID = widgetId;
    __flagVertical = flagVertical;

    __pSlider = new QSlider(this);
    __pSlider->setTickInterval(500);
    __pSlider->setSingleStep(500);
    if (!__flagVertical) {
        __pSlider->setOrientation(Qt::Horizontal);
        __pSlider->setRange(__limitMin, __limitMax);
        __pSlider->setStyleSheet("QSlider::groove:horizontal {"
                                "background: #ff666666;"
                                "height: 10px;"
                                "margin: 0 0 0 0;}"
                                "QSlider::handle:horizontal {"
                                "background: #ffaaaaaa;"
                                "width: 30px;"
                                "height: 20px;"
                                "border-radius: 0px;"
                                "margin: -10px 0px -10px 0px;}");
        __pSlider->setTracking(true);
    }
    else {
        __pSlider->setOrientation(Qt::Vertical);
        __pSlider->setRange(__limitMin, __limitMax);
        __pSlider->setStyleSheet("QSlider::groove:vertical {"
                                "background: #ff666666;"
                                "width: 15px;"
                                "margin: 0 0 0 0;}"
                                "QSlider::handle:vertical {"
                                "background: #ffaaaaaa;"
                                "height: 40px;"
                                "width: 30px;"
                                "border-radius: 0px;"
                                "margin: 0px -15px 0px -15px;}");
        __pSlider->setTracking(true);
    }
    connect(__pSlider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
}

WidgetSlider::~WidgetSlider() {
    delete __pSlider;
}

//_______________________________________PUBLIC_______________________________________//
void WidgetSlider::setValue(int value) {
    __pSlider->setValue(value);
}

int WidgetSlider::getValue() {
    return __pSlider->value();
}

void WidgetSlider::setRange(int min, int max) {
    __limitMin = min;
    __limitMax = max;
    __pSlider->setRange(min, max);
}

int WidgetSlider::getMaxValue() {
    return __limitMax;
}

int WidgetSlider:: getMinValue() {
    return __limitMin;
}


//_______________________________________PROTECTED____________________________________//
void WidgetSlider::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event)
    __pSlider->setGeometry(0, 0, width(), height());
}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void WidgetSlider::valueChanged(int value) {
    emit valueChanged(__widgetID, value);
}
