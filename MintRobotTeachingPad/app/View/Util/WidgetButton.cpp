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

#include "WidgetButton.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetButton::WidgetButton(QWidget *parent, int widgetID) : MTPWidget(parent, widgetID) {
    __label = new WidgetLabel(this);
}

WidgetButton::~WidgetButton() {
    delete __label;
}

//_____________________________
void WidgetButton::setText(QString text) {    
    __strText = text;
    __label->setText(__strText);
}

QString WidgetButton::getText() {
    return __strText;
}

void WidgetButton::setTextColor(QColor color) {
    __colorTextLabel = color;
    __label->setTextColor(color);
}

void WidgetButton::setTextFontHeightRatio(double ratio) {
    __textHeightRatio = ratio;
    __label->setTextHeightRatio(__textHeightRatio);
}

void WidgetButton::setTextAlign (WidgetLabel::ALIGN align) {
    __alignText = align;
    __label->setAlign(align);
}

void WidgetButton::setTextBold(bool flagBold) {
    if (flagBold) {
        __label->setBold();
    }
    else {
        __label->setLight();
    }
}

void WidgetButton::setButtonImage(QString imageID) {
    __strImageID = imageID;
}

void WidgetButton::setColor(QColor color) {
    __colorNormal = color;
    __flagOutlinePathComplete = false;
}

void WidgetButton::setColorClicked(QColor color) {
    __colorClicked = color;
    __flagOutlinePathComplete = false;
}

void WidgetButton::setMargin(int margine) {
    __margin = margine;
}

void WidgetButton::setRoundRatio(double roundRatio) {
    __roundRatio = roundRatio;
    __roundCorner1 = true;
    __roundCorner2 = true;
    __roundCorner3 = true;
    __roundCorner4 = true;
}

void WidgetButton::setRoundEnable(bool r1, bool r2, bool r3, bool r4) {
    __roundCorner1 = r1;
    __roundCorner2 = r2;
    __roundCorner3 = r3;
    __roundCorner4 = r4;
}
//_______________________________________PROTECTED____________________________________//
void WidgetButton::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);
    if (__strImageID.size() > 0) {
        int itemW = 0;
        if (width() < height()) {
            itemW = static_cast<int>((width()-__margin*2)*__imageMarginRatio);
        }
        else {
            itemW = static_cast<int>((height()-__margin*2)*__imageMarginRatio);
        }
        QPixmap pixmap = SingletonImage::GetInstance().getPixmap(__strImageID, itemW, itemW);
        __label->setPixmap(pixmap);
        __label->setGeometry((width()-itemW)/2, (height()-itemW)/2, itemW, itemW);
    } else if (__strText.size() > 0 && __strImageID.size() == 0) {
        __label->setGeometry(0, 0, width(), height());
        __label->setText(__strText);
        __label->setTextColor(__colorTextLabel);
        __label->setAlign(__alignText);
    }
}

void WidgetButton::paintEvent(QPaintEvent *event) {
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
    if (__flagPressed) {
        painter.setBrush(QBrush(__colorClicked));
    }
    else {
        painter.setBrush(QBrush(__colorNormal));
    }
    painter.setPen(Qt::NoPen);
    painter.drawPath(__painterOutlinePath);
}


void WidgetButton::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    if (!__flagPressed) {
        __flagPressed = true;
        update();
        emit onPress(getWidgetID());
    }
}

void WidgetButton::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    if (__flagPressed) {
        __flagPressed = false;
        update();
        emit onRelease(getWidgetID());
        emit onClick(getWidgetID());
    }
}


//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
