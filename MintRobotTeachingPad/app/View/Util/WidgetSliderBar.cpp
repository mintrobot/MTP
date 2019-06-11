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

#include "WidgetSliderBar.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetSliderBar::WidgetSliderBar(QWidget *parent, bool flagVertiral) : MTPWidget(parent) {

    __flagVertical = flagVertiral;

    __pBarBackground = new WidgetRect(this);
    __pBarBackground->setColor(__colorBackground);

    __pBarValue = new WidgetRect(this);
    __pBarValue->setColor(__colorValue);

}

WidgetSliderBar::~WidgetSliderBar() {

}

//_______________________________________PUBLIC_______________________________________//
void WidgetSliderBar::setValue(int value) {
    __value = value;
    update();
}

void WidgetSliderBar::setRange(int min, int max) {
    __valueMin = min;
    __valueMax = max;
    update();
}

int WidgetSliderBar::getValue() {
    return __value;
}

void WidgetSliderBar::setVerticalMode(bool flagVertical) {
    __flagVertical = flagVertical;
}
//_______________________________________PROTECTED____________________________________//
void WidgetSliderBar::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);
    if (!__flagVertical) {
        __pBarBackground->setGeometry(0, 0, width(), height());
        int w = ((__value-__valueMin)*width())/(__valueMax-__valueMin);
        __pBarValue->setGeometry(0, 0, w, height());
    }
    else {
        __pBarBackground->setGeometry(0, 0, width(), height());
        int h = ((__value-__valueMin)*height())/(__valueMax-__valueMin);
        __pBarValue->setGeometry(0, 0, width(), h);
    }

}


//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
