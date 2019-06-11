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

#ifndef KEYBOARD_H
#define KEYBOARD_H

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

#include "WidgetRect.h"
#include "WidgetButton.h"
//__________________________________________________________
class WidgetKeyboard : public QWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit WidgetKeyboard(QWidget *parent = nullptr);
        virtual ~WidgetKeyboard() override;

        void setValue(QString text);
        void setOperatorVisible(bool visible);

    //______________________________________________________
    protected:
        void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:
        int __keySize;

        QString __text = "";
        bool __flagOperatorVisiable = true;
        bool __flagCapslockEnable = false;

        WidgetRect *__pRectBackground;
        WidgetButton *__pButtonCapsLock;
        WidgetButton *__pButtonBackspace;
        QList<WidgetButton*>* __pListButtonSignKey;
        QList<WidgetButton*>* __pListButtonOpereator;
        WidgetButton *__pButtonDot;
        WidgetButton *__pButtonBracketOpen;
        WidgetButton *__pButtonBracketClose;
        WidgetButton *__pButtonUnderbar;
        WidgetButton *__pButtonEqual;
        WidgetButton *__pButtonSpace;
        QList<WidgetButton*>* __pListButtonNumberKey;
        QList<WidgetButton*>* __pListButtonAlphabetKey;

        void __redrawNumberKeys();
        void __redrawAlphabetKeys();
        void __redrawOperatorKeys();
        void __redrawSignKeys();
        void __redrawEtcKeys();

        WidgetButton* createButton(int id, QString text);
        WidgetButton* createButton(int id, QString text, float ratio);
        void upDateKeyText();

        QColor __colorText = SingletonColor::GetInstance().ColorLabelTextDefault;
        QColor __colorSpecialKey =  SingletonColor::GetInstance().ColorButtonEmpashize2Normal;
        QColor __colorSpecialKeyClicked = SingletonColor::GetInstance().ColorButtonEmpashize2Clicked;
        QColor __colorNormalKey = SingletonColor::GetInstance().ColorButtonDefaultNormal;
        QColor __colorNormalKeyClicked = SingletonColor::GetInstance().ColorButtonDefaultClicked;

    //______________________________________________________
    signals:
        void changeValue(QString value);
    //______________________________________________________
    private slots:
        void onClick(int id);

};
//__________________________________________________________

#endif // KEYBOARD_H
