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

#include "WidgetRect.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetRect::WidgetRect(QWidget *parent) : QWidget(parent) {

}

WidgetRect::~WidgetRect() { }

//_______________________________________PUBLIC_______________________________________//
void WidgetRect::setColor(QColor color) {
    mColor = color;
}

void WidgetRect::setRoundRatio(double roundRatio) {
    __roundRatio = roundRatio;
    __roundCorner1 = true;
    __roundCorner2 = true;
    __roundCorner3 = true;
    __roundCorner4 = true;
}

void WidgetRect::setRoundEnable(bool r1, bool r2, bool r3, bool r4) {
    __roundCorner1 = r1;
    __roundCorner2 = r2;
    __roundCorner3 = r3;
    __roundCorner4 = r4;
}

//_______________________________________PROTECTED____________________________________//
void WidgetRect::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    __painterOutlinePath = QPainterPath();

    int m = __margin;
    double r = 0;
    int w = 0;
    int h = 0;

    w = width();
    h = height();

    if (width() < height()) {
        r = (width()-m*2)*__roundRatio*2;
    } else {
        r = (height()-m*2)*__roundRatio*2;
    }

    __painterOutlinePath.moveTo((m+r/2), m);
    if (__roundCorner2) {
        __painterOutlinePath.arcTo(m, m, r, r, 90.0, 90.0);
    } else {
        __painterOutlinePath.lineTo(m, m);
    }
    __painterOutlinePath.lineTo(m, m+r/2);
    __painterOutlinePath.lineTo(m, h-m-r/2);

    if (__roundCorner3) {
        __painterOutlinePath.arcTo(m, h-m-r, r, r, 180, 90);
    } else {
        __painterOutlinePath.lineTo(m, h-m);
    }

    __painterOutlinePath.lineTo(m+r/2, h-m);
    __painterOutlinePath.lineTo(w-m-r/2, h-m);

    if (__roundCorner4) {
        __painterOutlinePath.arcTo(w-m-r, h-m-r, r, r, 270, 90);
    } else {
        __painterOutlinePath.lineTo(w-m, h-m);
    }

    __painterOutlinePath.lineTo(w-m, h-r/2-m);
    __painterOutlinePath.lineTo(w-m, m+r/2);

    if (__roundCorner1) {
        __painterOutlinePath.arcTo(w-m-r, m, r, r, 0, 90);
    } else {
        __painterOutlinePath.lineTo(w-m, m);
    }
    __painterOutlinePath.lineTo(w-m-r/2, m);
    __painterOutlinePath.closeSubpath();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(mColor));
    painter.setPen(Qt::NoPen);
    painter.drawPath(__painterOutlinePath);
}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
