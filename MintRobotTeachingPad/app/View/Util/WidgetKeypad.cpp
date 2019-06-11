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

#include "WidgetKeypad.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetKeypad::WidgetKeypad(QWidget *parent) : QWidget(parent) {

    __pRectBackground = new WidgetRect(this);
    __pRectBackground->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);

    // Init plus, minus and clear buttons
    __pButtonPlus = new WidgetButton(this, BUTTON_ID_PLUS);
    __pButtonPlus->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultNormal, 0xff));
    __pButtonPlus->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonPlus->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonPlus->setRoundRatio(0.1);
    __pButtonPlus->setText("+");
    __pButtonPlus->setVisible(__flagSignButtonVisiable);

    __pButtonMinus = new WidgetButton(this, BUTTON_ID_MINUS);
    __pButtonMinus->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultNormal, 0xff));
    __pButtonMinus->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonMinus->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonMinus->setRoundRatio(0.1);
    __pButtonMinus->setText("-");
    __pButtonMinus->setVisible(__flagSignButtonVisiable);

    __pButtonClear = new WidgetButton(this, BUTTON_ID_CLEAR);
    __pButtonClear->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultNormal, 0xff));
    __pButtonClear->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonClear->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonClear->setRoundRatio(0.1);
    __pButtonClear->setText("C");


    // Init keypad buttons
    __pListButtonNumber = new QList<WidgetButton*>();
    WidgetButton* btn = new WidgetButton(this, BUTTON_ID_DOT);
    btn->setRoundRatio(0.1);
    btn->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultNormal, 0xff));
    btn->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    btn->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    btn->setText(".");
    __pListButtonNumber->append(btn);

    for (int i = 0; i < 10; i++) {
        btn = new WidgetButton(this, i);
        btn->setRoundRatio(0.1);
        btn->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultNormal, 0xff));
        btn->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
        btn->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
        btn->setText(QString(48+i));
        __pListButtonNumber->append(btn);
    }


    // Connect signals
    connect(__pButtonPlus, SIGNAL(onClick(int)), this, SLOT(updateClickedKey(int)));
    connect(__pButtonMinus, SIGNAL(onClick(int)), this, SLOT(updateClickedKey(int)));
    connect(__pButtonClear, SIGNAL(onClick(int)), this, SLOT(updateClickedKey(int)));
    for (int i = 0; i < 11; i++) {
        btn = __pListButtonNumber->at(i);
        connect(btn, SIGNAL(onClick(int)), this, SLOT(updateClickedKey(int)));
    }
}

WidgetKeypad::~WidgetKeypad() {

}

//_______________________________________PUBLIC_______________________________________//
void WidgetKeypad::setSignButtonVisiableMode(bool enable) {
    __flagSignButtonVisiable = enable;
    __pButtonPlus->setVisible(enable);
    __pButtonMinus->setVisible(enable);
}

void WidgetKeypad::setStringValue(QString value) {
    __strValue = value;
}


//_______________________________________PROTECTED____________________________________//
void WidgetKeypad::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event)
    __redrawBackground();
    __redrawButtonPlus();
    __redrawButtonMinus();
    __redrawButtonClear();
    __redrawButtonNumber();
}

//_______________________________________PRIVATE______________________________________//
void WidgetKeypad::__redrawBackground() {
    __pRectBackground->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);
    __pRectBackground->setGeometry(0, 0, width(), height());
}

void WidgetKeypad::__redrawButtonPlus() {
    int w = width() / 3;
    int h = height() / 5;
    int x = 0;
    int y = 0;
    __pButtonPlus->setGeometry(x, y, w, h);
}

void WidgetKeypad::__redrawButtonMinus() {
    int w = width() / 3;
    int h = height() / 5;
    int x = w;
    int y = 0;
    __pButtonMinus->setGeometry(x, y, w, h);
}

void WidgetKeypad::__redrawButtonClear() {
    int w = width() / 3;
    int h = height() / 5;
    int x = width() - w;
    int y = 0;
    __pButtonClear->setGeometry(x, y, w, h);
}

void WidgetKeypad::__redrawButtonNumber() {
    int w = width() / 3;
    int h = height() / 5;
    for (int i = 2; i < __pListButtonNumber->size(); i++) {
        int x = (i - 2) % 3 * w;
        int y = height() - (i - 2) / 3 * h - h * 2;
        __pListButtonNumber->at(i)->setGeometry(x, y, w, h);
    }
    __pListButtonNumber->at(1)->setGeometry(0, height() - h, w * 2, h);
    __pListButtonNumber->at(0)->setGeometry(width() - w, height() - h, w, h);
}

//_______________________________________SLOTS________________________________________//
void WidgetKeypad::updateClickedKey(int id) {

    if (id == BUTTON_ID_CLEAR) {
        __strValue = "";
    }
    else if (id == BUTTON_ID_DOT) {
        __strValue = __strValue + ".";
    }
    else if (id == BUTTON_ID_MINUS) {
        __strValue = __strValue + "-";
    }
    else if (id == 0) {
        __strValue = __strValue+QString::number(0);
    }
    else {
        __strValue = __strValue+QString::number(id);
    }
    emit onUpdateValue(__strValue);

}
