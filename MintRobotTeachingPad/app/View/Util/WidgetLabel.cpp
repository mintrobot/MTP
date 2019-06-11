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

#include "WidgetLabel.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetLabel::WidgetLabel(QWidget *parent) : QLabel (parent) {

}

WidgetLabel::~WidgetLabel() {

}

//_____________________________
void WidgetLabel::setText(QString text) {
    __strText = text;
    __updateText();
}

void WidgetLabel::setTextColor(QColor textColor){
    __textColor = textColor;
    __updateText();
}

void WidgetLabel::setTextHeightRatio(double ratio) {
    setTextHeightPixel(static_cast<int>(height() * ratio));
    __updateText();
}

void WidgetLabel::setTextHeightPixel(int pixel) {
    __sizeFont = pixel;
    __textFont = SingletonFont::GetInstance().getFontLight(__sizeFont);
    __updateText();
}

void WidgetLabel::setAlign(ALIGN align) {
    __align = align;
    __updateText();
}

void WidgetLabel::setBold() {
    __textFont = SingletonFont::GetInstance().getFontBold(__sizeFont);
    __updateText();
}

void WidgetLabel::setLight() {
    __textFont = SingletonFont::GetInstance().getFontLight(__sizeFont);
    __updateText();
}

//_______________________________________PROTECTED____________________________________//
void WidgetLabel::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);
    __sizeFont = static_cast<int>(height() * 0.6);
}

//_______________________________________PRIVATE______________________________________//
void WidgetLabel::__updateText() {
    QLabel::setText(__strText);
    QPalette p;
    p.setColor(QPalette::WindowText, __textColor);
    setPalette(p);
    setFont(__textFont);
    if (ALIGN_LEFT == __align) {
        setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }
    else if (ALIGN_CENTER == __align) {
        setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    }
    else if (ALIGN_RIGHT == __align) {
        setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    }
    update();
}
//_______________________________________SLOTS________________________________________//
