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

#include "WidgetUINode.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetUINode::WidgetUINode(QWidget *parent, int id) : MTPWidget(parent, id) {    
    __pLabelCommand = new WidgetLabel(this);
    __pLabelCommand->setText(__strCommandText);
    __pLabelCommand->setTextColor(__colorTextLabelCommand);
    __pLabelCommand->setAlign(__alignText);
    __pLabelCommand->setBold();

    __plabelArguments = new WidgetLabel(this);
    __plabelArguments->setText(__strArgumentText);
    __plabelArguments->setTextColor(__colorTextLabelArgument);
    __plabelArguments->setAlign(__alignText);
}

WidgetUINode::~WidgetUINode() {
    delete __plabelArguments;
}

//_______________________________________PUBLIC_______________________________________//
void WidgetUINode::updateText() {
    __pLabelCommand->setText(pModelNode->getCommandString());
    __plabelArguments->setText(pModelNode->getArgumentsString());
}

void WidgetUINode::setColor(QColor color) {
    __colorBase = color;
    __colorNormal = SingletonColor::GetInstance().getColorWithAlpha(__colorBase, 0x50);
    __colorSelected = SingletonColor::GetInstance().getColorWithAlpha(__colorBase, 0xff);
    __colorError = SingletonColor::GetInstance().ColorLabelError;
    __colorCurrent = __colorNormal;
}

void WidgetUINode::setOnRunning(bool flagStatus) {
    if (flagStatus) {
        __colorCurrent = __colorSelected;
        repaint();
    }
    else {
        __colorCurrent = __colorNormal;
        repaint();
    }
}
//_______________________________________PROTECTED____________________________________//
void WidgetUINode::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);

    int offset = height() * cal;

    __widthMargin = static_cast<int>(width() * __ratioMargin / 100);
    __heightMargin = static_cast<int>(height() * __ratioMargin / 100);
    __widthCommand = static_cast<int>(width() * __ratioWidthCommand / 100);
    __widthArgument = static_cast<int>(width() * __ratioWidthArgument / 100);

    __pLabelCommand->setTextHeightRatio(__ratioTextHeight);
    __pLabelCommand->setGeometry(offset + __widthMargin, __heightMargin, __widthCommand, height() - __heightMargin * 2);

    __plabelArguments->setTextHeightRatio(__ratioTextHeight);
    __plabelArguments->setGeometry(__pLabelCommand->geometry().bottomRight().x() + __widthMargin, __heightMargin, __widthArgument, height() - __heightMargin * 2);
}

void WidgetUINode::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    int offset = height() * cal;

    QRect rect;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    int __margin = __heightMargin;

    for (int i = 0; i < cal; i++) {
        rect.setRect(__margin + height() * i, 0, height()-__margin*2, height());
        painter.setBrush(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorNodeConditional, 0x50));
        painter.drawRect(rect);
    }

    painter.setBrush(QBrush(__colorCurrent));
    rect.setRect(offset + __margin, __margin, width()-__margin*2, height()-__margin*2);
    painter.drawRect(rect);

    painter.setBrush(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorNodeConditional, 0x50));
    if (flagContainerTop == true) {
        rect.setRect(offset + __margin, height()-__margin, height()-__margin*2, __margin);
        painter.drawRect(rect);
    }
    else if (flagContainerBetween) {
        rect.setRect(offset + __margin, height()-__margin, height()-__margin*2, __margin);
        painter.drawRect(rect);
        rect.setRect(offset + __margin, 0, height()-__margin*2, __margin);
        painter.drawRect(rect);
    }
    else if (flagContainerBottom == true) {
        rect.setRect(offset + __margin, 0, height()-__margin*2, __margin);
        painter.drawRect(rect);
    }
}

void WidgetUINode::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    if (!__flagPressed) {
        __flagPressed = true;
        update();
    }
}

void WidgetUINode::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    if (__flagPressed) {
        __flagPressed = false;
        update();
        emit onClickUINode(row, cal);
    }
}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
