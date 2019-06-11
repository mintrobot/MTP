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

#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include "app/view/SingletonFont.h"
#include "app/view/SingletonColor.h"

class WidgetLabel : public QLabel
{
    Q_OBJECT
    public:
        typedef enum{
            ALIGN_LEFT = 0,
            ALIGN_CENTER = 1,
            ALIGN_RIGHT = 2,
        } ALIGN;

    //______________________________________________________
    public:
        explicit WidgetLabel(QWidget *parent = nullptr);
        virtual ~WidgetLabel() override;

        void setText(QString text);
        void setTextColor(QColor textColor);
        void setTextHeightRatio(double ratio);
        void setTextHeightPixel(int pixel);
        void setAlign(ALIGN align = ALIGN_LEFT);
        void setBold();
        void setLight();
    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:
        QString __strText = "";
        QColor __textColor = SingletonColor::GetInstance().ColorLabelTextDefault;
        QFont __textFont = SingletonFont::GetInstance().getFontLight(static_cast<int>(height() * 0.8));
        ALIGN __align = ALIGN_LEFT;
        int __sizeFont = 3;

        void __updateText();
    //______________________________________________________
    signals:
    //______________________________________________________
    private slots:

};

#endif // LABEL_H
