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

#ifndef KEYPAD_H
#define KEYPAD_H

//__________________________________________________________
#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QLabel>

#include "app/view/SingletonImage.h"
#include "app/view/SingletonFont.h"
#include "app/view/SingletonColor.h"
#include "app/view/viewsize.h"
#include "app/view/viewid.h"
#include "app/view/stringid.h"

#include "WidgetRect.h"
#include "WidgetButton.h"
#include "WidgetKeyboard.h"

#define BUTTON_ID_PLUS      0x11
#define BUTTON_ID_MINUS     0x12
#define BUTTON_ID_DOT       0x13
#define BUTTON_ID_CLEAR     0x14

//__________________________________________________________
class WidgetKeypad : public QWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit WidgetKeypad(QWidget *parent = nullptr);
        virtual ~WidgetKeypad() override;

        void setSignButtonVisiableMode(bool enable);
        void setStringValue(QString value);

    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:
        bool __flagSignButtonVisiable = true;

        QString __strValue = "";
        bool __flagDot = false;
        bool __flagPlus = true;

        WidgetRect *__pRectBackground;
        WidgetButton *__pButtonPlus;
        WidgetButton *__pButtonMinus;
        WidgetButton *__pButtonClear;
        QList<WidgetButton*> *__pListButtonNumber;

        void __redrawBackground();
        void __redrawButtonClear();
        void __redrawButtonPlus();
        void __redrawButtonMinus();
        void __redrawButtonNumber();

    //______________________________________________________
    signals:
        void onUpdateValue(QString value);
    //______________________________________________________
    private slots:
        void updateClickedKey(int id);

};
//__________________________________________________________

#endif // KEYPAD_H
