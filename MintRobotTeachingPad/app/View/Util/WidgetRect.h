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

#ifndef RECTANGLE_H
#define RECTANGLE_H

//__________________________________________________________
#include <QObject>
#include <QWidget>
#include <QtGui>

//__________________________________________________________
class WidgetRect : public QWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit WidgetRect(QWidget *parent = nullptr);
        virtual ~WidgetRect() override;

        void setColor(QColor color);
        void setRoundRatio(double roundRatio);
        void setRoundEnable(bool r1, bool r2, bool r3, bool r4);
    //______________________________________________________
    protected:
        void paintEvent(QPaintEvent *event) override;
    //______________________________________________________
    private:
        bool __flagOutlinePathComplete = false;
        QPainterPath __painterOutlinePath;
        double __roundRatio = 0;
        int __margin = 0;
        bool __roundCorner1 = true;
        bool __roundCorner2 = true;
        bool __roundCorner3 = true;
        bool __roundCorner4 = true;

        QColor mColor = QColor(0x55, 0x55, 0x55, 0x55);

        int mWidth = 0;
        int mHeight = 0;

    //______________________________________________________
    signals:
    //______________________________________________________
    private slots:

};
//__________________________________________________________

#endif // RECTANGLE_H
