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

#ifndef SLIDERBAR_H
#define SLIDERBAR_H

//__________________________________________________________
#include "MTPWidget.h"
#include "WidgetRect.h"
//__________________________________________________________
class WidgetSliderBar : public MTPWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit WidgetSliderBar(QWidget *parent = nullptr, bool flagVertiral = false);
        virtual ~WidgetSliderBar() override;

        void setValue(int value);
        void setRange(int min, int max);
        int getMaxValue();
        int getMinValue();
        int getValue();
        void setVerticalMode(bool enable);

    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:
        bool __flagVertical = false;
        int __valueMin = -100;
        int __valueMax = 100;
        int __value = 0;

        WidgetRect *__pBarBackground;
        WidgetRect *__pBarValue;

        QColor __colorBackground = SingletonColor::GetInstance().ColorButtonDefaultNormal;
        QColor __colorValue = SingletonColor::GetInstance().ColorButtonEmpashize1Clicked;

        void initSlider();

    //______________________________________________________
    signals:
    //______________________________________________________
    private slots:

};
//__________________________________________________________


#endif // SLIDERBAR_H
