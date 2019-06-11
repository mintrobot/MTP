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

#include "WidgetKeyboard.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetKeyboard::WidgetKeyboard(QWidget *parent) : QWidget(parent) {

    __keySize = width() / 10;

    // init background
    __pRectBackground = new WidgetRect(this);
    __pRectBackground->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);

    // init capslock and backspace button
    __pButtonCapsLock = createButton(VIEW_ID_KEYBOARD_CAPSLOCK, "Caps Lock");
    __pButtonCapsLock->setColor(__colorSpecialKey);
    __pButtonCapsLock->setColor(__colorSpecialKeyClicked);
    __pButtonCapsLock->setTextColor(__colorText);
    __pButtonCapsLock->setTextFontHeightRatio(0.8);
    __pButtonBackspace = createButton(VIEW_ID_KEYBOARD_BACKSPACE, "Backspace");
    __pButtonBackspace->setColor(__colorSpecialKey);
    __pButtonBackspace->setColor(__colorSpecialKeyClicked);
    __pButtonBackspace->setTextColor(__colorText);
    __pButtonBackspace->setTextFontHeightRatio(0.8);


    // init signkey button
    __pListButtonSignKey = new QList<WidgetButton*>();   
    __pListButtonSignKey->append(createButton(VIEW_ID_KEYBOARD_SIGN_1, ">"));
    __pListButtonSignKey->append(createButton(VIEW_ID_KEYBOARD_SIGN_2, ">="));
    __pListButtonSignKey->append(createButton(VIEW_ID_KEYBOARD_SIGN_3, "!="));
    __pListButtonSignKey->append(createButton(VIEW_ID_KEYBOARD_SIGN_4, "=="));
    __pListButtonSignKey->append(createButton(VIEW_ID_KEYBOARD_SIGN_5, "<="));
    __pListButtonSignKey->append(createButton(VIEW_ID_KEYBOARD_SIGN_6, "<"));

    // init operator button
    __pListButtonOpereator = new QList<WidgetButton*>();
    __pListButtonOpereator->append(createButton(VIEW_ID_KEYBOARD_OPERATOR_1, QString("+")));
    __pListButtonOpereator->append(createButton(VIEW_ID_KEYBOARD_OPERATOR_2, QString("-")));
    __pListButtonOpereator->append(createButton(VIEW_ID_KEYBOARD_OPERATOR_3, QString("*")));
    __pListButtonOpereator->append(createButton(VIEW_ID_KEYBOARD_OPERATOR_4, QString("/")));
    __pListButtonOpereator->append(createButton(VIEW_ID_KEYBOARD_OPERATOR_5, QString("%")));

    // init dot, braket, underbar, and equal buttons
    __pButtonDot = createButton(VIEW_ID_KEYBOARD_DOT, QString("."));
    __pButtonBracketOpen = createButton(VIEW_ID_KEYBOARD_BRACET_OPEN, QString("("));
    __pButtonBracketClose = createButton(VIEW_ID_KEYBOARD_BRACET_CLOSE, QString(")"));
    __pButtonUnderbar = createButton(VIEW_ID_KEYBOARD_UNDERBAR, QString("_"));
    __pButtonEqual = createButton(VIEW_ID_KEYBOARD_BAR, QString("="));

    // init number buttons
    __pListButtonNumberKey = new QList<WidgetButton*>();
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_1, QString(VIEW_ID_KEYPAD_NUM_1+16)));
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_2, QString(VIEW_ID_KEYPAD_NUM_2+16)));
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_3, QString(VIEW_ID_KEYPAD_NUM_3+16)));
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_4, QString(VIEW_ID_KEYPAD_NUM_4+16)));
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_5, QString(VIEW_ID_KEYPAD_NUM_5+16)));
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_6, QString(VIEW_ID_KEYPAD_NUM_6+16)));
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_7, QString(VIEW_ID_KEYPAD_NUM_7+16)));
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_8, QString(VIEW_ID_KEYPAD_NUM_8+16)));
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_9, QString(VIEW_ID_KEYPAD_NUM_9+16)));
    __pListButtonNumberKey->append(createButton(VIEW_ID_KEYPAD_NUM_0, QString("0")));

    // init alphabet buttons
    __pListButtonAlphabetKey = new QList<WidgetButton*>();
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_Q, QString(VIEW_ID_KEYBOARD_KEY_Q+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_W, QString(VIEW_ID_KEYBOARD_KEY_W+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_E, QString(VIEW_ID_KEYBOARD_KEY_E+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_R, QString(VIEW_ID_KEYBOARD_KEY_R+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_T, QString(VIEW_ID_KEYBOARD_KEY_T+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_Y, QString(VIEW_ID_KEYBOARD_KEY_Y+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_U, QString(VIEW_ID_KEYBOARD_KEY_U+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_I, QString(VIEW_ID_KEYBOARD_KEY_I+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_O, QString(VIEW_ID_KEYBOARD_KEY_O+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_P, QString(VIEW_ID_KEYBOARD_KEY_P+55)));

    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_A, QString(VIEW_ID_KEYBOARD_KEY_A+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_S, QString(VIEW_ID_KEYBOARD_KEY_S+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_D, QString(VIEW_ID_KEYBOARD_KEY_D+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_F, QString(VIEW_ID_KEYBOARD_KEY_F+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_G, QString(VIEW_ID_KEYBOARD_KEY_G+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_H, QString(VIEW_ID_KEYBOARD_KEY_H+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_K, QString(VIEW_ID_KEYBOARD_KEY_K+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_L, QString(VIEW_ID_KEYBOARD_KEY_L+55)));

    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_Z, QString(VIEW_ID_KEYBOARD_KEY_Z+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_X, QString(VIEW_ID_KEYBOARD_KEY_X+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_C, QString(VIEW_ID_KEYBOARD_KEY_C+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_V, QString(VIEW_ID_KEYBOARD_KEY_V+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_B, QString(VIEW_ID_KEYBOARD_KEY_B+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_N, QString(VIEW_ID_KEYBOARD_KEY_N+55)));
    __pListButtonAlphabetKey->append(createButton(VIEW_ID_KEYBOARD_KEY_M, QString(VIEW_ID_KEYBOARD_KEY_M+55)));

    // init space
    __pButtonSpace = createButton(VIEW_ID_KEYBOARD_SPACE, "SPACE");

}

WidgetKeyboard::~WidgetKeyboard() {

}

//_______________________________________PUBLIC_______________________________________//
void WidgetKeyboard::setValue(QString text) {
    __text = text;
}

void WidgetKeyboard::setOperatorVisible(bool visible) {
    __flagOperatorVisiable = visible;
}


//_______________________________________PROTECTED____________________________________//
void WidgetKeyboard::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event)
    __keySize = width() / 10;

    __pRectBackground->setGeometry(0, 0, width(), height());

    __redrawSignKeys();
    __redrawOperatorKeys();
    __redrawEtcKeys();
    __redrawNumberKeys();
    __redrawAlphabetKeys();
}

//_______________________________________PRIVATE______________________________________//
void WidgetKeyboard::__redrawEtcKeys() {

    // Capslock
    int widthKeys = __flagOperatorVisiable ? __keySize*2 : __keySize;
    __pButtonCapsLock->setGeometry(0, 0, widthKeys, __keySize);
    if (!__flagOperatorVisiable) {
        __pButtonCapsLock->setText("CAPS");
    }

    // Backspace
    widthKeys = __flagOperatorVisiable ? __keySize*2 : __keySize;
    __pButtonBackspace->setGeometry(width() - widthKeys, 0, widthKeys, __keySize);
    if (!__flagOperatorVisiable) {
        __pButtonBackspace->setText("DEL");
    }

    // ETCs
    __pButtonDot->setGeometry(__keySize*5, __keySize, __keySize, __keySize);
    __pButtonBracketOpen->setGeometry(__keySize*6, __keySize, __keySize, __keySize);
    __pButtonBracketClose->setGeometry(__keySize*7, __keySize, __keySize, __keySize);
    __pButtonUnderbar->setGeometry(__keySize*8, __keySize, __keySize, __keySize);
    __pButtonEqual->setGeometry(__keySize*9, __keySize, __keySize, __keySize);

    __pButtonDot->setVisible(__flagOperatorVisiable);
    __pButtonBracketOpen->setVisible(__flagOperatorVisiable);
    __pButtonBracketClose->setVisible(__flagOperatorVisiable);
    __pButtonUnderbar->setVisible(__flagOperatorVisiable);
    __pButtonEqual->setVisible(__flagOperatorVisiable);

    // Space
    int startY = __flagOperatorVisiable ? __keySize*5 : __keySize*3;
    __pButtonSpace->setGeometry(__keySize*7, startY, __keySize*3, __keySize);
}


void WidgetKeyboard::__redrawSignKeys() {
    for (int i=0; i<__pListButtonSignKey->size(); i++) {
        int x = __keySize*(i+2);
        __pListButtonSignKey->at(i)->setGeometry(x, 0, __keySize, __keySize);
        __pListButtonSignKey->at(i)->setVisible(__flagOperatorVisiable);
    }
}

void WidgetKeyboard::__redrawOperatorKeys() {
    for (int i=0; i<__pListButtonOpereator->size(); i++) {
        int x = __keySize*i;
        __pListButtonOpereator->at(i)->setGeometry(x, __keySize, __keySize, __keySize);
        __pListButtonOpereator->at(i)->setVisible(__flagOperatorVisiable);
    }
}


void WidgetKeyboard::__redrawNumberKeys() {
    int x = __flagOperatorVisiable ? 0 : __keySize;
    int w = __flagOperatorVisiable ? __keySize : (__keySize*8)/10;
    int startY = __flagOperatorVisiable ? __keySize*2 : 0;
    for (int i=0; i<__pListButtonNumberKey->size(); i++) {
        __pListButtonNumberKey->at(i)->setGeometry(x+w*i, startY, w, __keySize);
    }
}

void WidgetKeyboard::__redrawAlphabetKeys() {
    int startY = __flagOperatorVisiable ? __keySize*3 : __keySize;
    for (int i=0; i<__pListButtonAlphabetKey->size(); i++) {
        if (i < 10) {
            __pListButtonAlphabetKey->at(i)->setGeometry(__keySize*i, startY, __keySize, __keySize);
        }
        else if (i < 19) {
            __pListButtonAlphabetKey->at(i)->setGeometry(__keySize*(i-10)+__keySize/2, startY+__keySize, __keySize, __keySize);
        }
        else {
            __pListButtonAlphabetKey->at(i)->setGeometry(__keySize*(i-19)+__keySize, startY+__keySize*2, __keySize, __keySize);
        }
    }
}

WidgetButton* WidgetKeyboard::createButton(int id, QString text) {
    WidgetButton *btn = new WidgetButton(this, id);
    btn->setRoundRatio(0.1);
    btn->setColor(__colorNormalKey);
    btn->setColorClicked(__colorNormalKeyClicked);
    btn->setTextColor(__colorText);
    btn->setText(text);
    btn->setTextFontHeightRatio(0.8);
    connect(btn, SIGNAL(onClick(int)), this, SLOT(onClick(int)));
    return btn;
}

void WidgetKeyboard::upDateKeyText() {
    int dif = __flagCapslockEnable ? 23 : 55;
    for (int i=0; i<__pListButtonAlphabetKey->size(); i++) {
        __pListButtonAlphabetKey->at(i)->setText(QString(__pListButtonAlphabetKey->at(i)->getWidgetID()+dif));
    }
    __redrawAlphabetKeys();
}

//_______________________________________SLOTS________________________________________//
void WidgetKeyboard::onClick(int id) {
    if (id == VIEW_ID_KEYBOARD_CAPSLOCK) {
        __flagCapslockEnable = !__flagCapslockEnable;
        upDateKeyText();
    }
    if ((VIEW_ID_KEYBOARD_KEY_A <= id) & (id <= VIEW_ID_KEYBOARD_KEY_Z)) {
        if (__flagCapslockEnable) {
            __text = __text+QString(id+23);
        }
        else {
            __text = __text+QString(id+55);
        }
    }
    else if ((VIEW_ID_KEYPAD_NUM_0 <= id) & (id <= VIEW_ID_KEYPAD_NUM_9)) {
        if (__text == "0") {
            __text = QString(id-VIEW_ID_KEYPAD_NUM_0+48);
        }
        else {
            __text = __text+QString(id-VIEW_ID_KEYPAD_NUM_0+48);
        }
    } else if (id == VIEW_ID_KEYBOARD_UNDERBAR) {     __text = __text+QString("_");
    } else if (id == VIEW_ID_KEYBOARD_BAR) {          __text = __text+QString("=");
    } else if (id == VIEW_ID_KEYBOARD_OPERATOR_1) {   __text = __text+QString("+");
    } else if (id == VIEW_ID_KEYBOARD_OPERATOR_2) {   __text = __text+QString("-");
    } else if (id == VIEW_ID_KEYBOARD_OPERATOR_3) {   __text = __text+QString("*");
    } else if (id == VIEW_ID_KEYBOARD_OPERATOR_4) {   __text = __text+QString("/");
    } else if (id == VIEW_ID_KEYBOARD_OPERATOR_5) {   __text = __text+QString("%");
    } else if (id == VIEW_ID_KEYBOARD_BRACET_OPEN) {  __text = __text+QString("(");
    } else if (id == VIEW_ID_KEYBOARD_BRACET_CLOSE) { __text = __text+QString(")");
    } else if (id == VIEW_ID_KEYBOARD_SIGN_1) { __text = __text+QString(" > ");
    } else if (id == VIEW_ID_KEYBOARD_SIGN_2) { __text = __text+QString(" >= ");
    } else if (id == VIEW_ID_KEYBOARD_SIGN_3) { __text = __text+QString(" != ");
    } else if (id == VIEW_ID_KEYBOARD_SIGN_4) { __text = __text+QString(" == ");
    } else if (id == VIEW_ID_KEYBOARD_SIGN_5) { __text = __text+QString(" <= ");
    } else if (id == VIEW_ID_KEYBOARD_SIGN_6) { __text = __text+QString(" < ");
    } else if (id == VIEW_ID_KEYBOARD_SPACE) { __text = __text+QString(" ");
    } else if (id == VIEW_ID_KEYBOARD_BACKSPACE) { __text.remove(__text.length()-1, 1);
    }
    emit changeValue(__text);
}
