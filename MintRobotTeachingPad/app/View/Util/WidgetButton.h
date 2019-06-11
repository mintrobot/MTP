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

#ifndef BUTTON_H
#define BUTTON_H

//__________________________________________________________
#include "app/view/util/MTPWidget.h"
#include "WidgetLabel.h"

//__________________________________________________________
class WidgetButton : public MTPWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit WidgetButton(QWidget *parent = nullptr, int widgetId = 0);
        virtual ~WidgetButton() override;

        void setText(QString text);
        QString getText();

        void setTextColor(QColor color);
        void setTextFontHeightRatio(double ratio);
        void setTextAlign (WidgetLabel::ALIGN align);
        void setTextBold(bool flagBold);

        void setButtonImage(QString imgId);

        void setBackgroindVisible(bool backgroundVisiable);
        void setColor(QColor color);
        void setColorClicked(QColor color);
        void setMargin(int margine);
        void setRoundRatio(double roundRatio);
        void setRoundEnable(bool r1, bool r2, bool r3, bool r4);

    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;
        virtual void paintEvent(QPaintEvent *event) override;
        virtual void mousePressEvent(QMouseEvent *event) override;
        virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //______________________________________________________
    private:
        WidgetLabel* __label;
        QString __strImageID = "";
        QString __strText = "";
        QColor  __colorTextLabel = SingletonColor::GetInstance().ColorLabelTextDefault;
        double __textHeightRatio = 0.8;
        WidgetLabel::ALIGN __alignText = WidgetLabel::ALIGN_CENTER;

        bool __flagOutlinePathComplete = false;
        QPainterPath __painterOutlinePath;
        int __preWidth = 0;
        int __preHeight = 0;
        QColor __colorNormal = SingletonColor::GetInstance().ColorButtonDefaultNormal;
        QColor __colorClicked = SingletonColor::GetInstance().ColorButtonDefaultClicked;
        int __margin = 5;
        double __imageMarginRatio = 0.6;
        double __roundRatio = 0.5;
        bool __roundCorner1 = true;
        bool __roundCorner2 = true;
        bool __roundCorner3 = true;
        bool __roundCorner4 = true;

        bool __flagPressed = false;

    //______________________________________________________
    signals:
        void onClick(int id);
        void onPress(int id);
        void onRelease(int id);
    //______________________________________________________
    private slots:

};
//__________________________________________________________


#endif // BUTTON_H
