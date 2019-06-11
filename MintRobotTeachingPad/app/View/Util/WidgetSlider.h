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

#ifndef SLIDER_H
#define SLIDER_H

//__________________________________________________________
#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QSlider>
//__________________________________________________________
class WidgetSlider : public QWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit WidgetSlider(QWidget *parent = nullptr, bool flagVertical = false, int widgetId = 0);
        virtual ~WidgetSlider() override;

        void setValue(int value);
        void setRange(int min, int max);
        int getMaxValue();
        int getMinValue();
        int getValue();

    //______________________________________________________
    protected:
        void resizeEvent(QResizeEvent * event) override;
    //______________________________________________________
    private:
        int __widgetID = 0;
        int __limitMin = -100;
        int __limitMax = 100;
        bool __flagVertical = false;

        QSlider *__pSlider;

    //______________________________________________________
    signals:
        void valueChanged(int id, int value);
    //______________________________________________________
    private slots:
        void valueChanged(int value);

};
//__________________________________________________________


#endif // SLIDER_H
