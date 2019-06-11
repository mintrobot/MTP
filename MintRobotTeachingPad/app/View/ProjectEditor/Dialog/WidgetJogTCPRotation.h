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

#ifndef MOVEROTATION3D_H
#define MOVEROTATION3D_H

#include "app/model/SingletonInterfaceManager.h"

#include "app/view/util/MTPWidget.h"
#include "app/view/util/WidgetLabel.h"
#include "app/view/util/WidgetRect.h"
#include "app/view/util/WidgetButton.h"
#include "app/view/util/WidgetSliderBar.h"

#include "app/view/viewid.h"

class WidgetJogTCPRotation : public MTPWidget
{
    Q_OBJECT
//______________________________________________________
public:
    explicit WidgetJogTCPRotation(QWidget *parent = nullptr);
    virtual ~WidgetJogTCPRotation() override;

//______________________________________________________
protected:
    virtual void resizeEvent(QResizeEvent * event) override;
    virtual void paintEvent(QPaintEvent *event) override;

//______________________________________________________
private:
    double __ratioMargin = 3;
    double __ratioWidthButton = 29.33;
    double __ratioHeightButton = 21.25;

    int __widthMargin;
    int __heightMargin;
    int __widthButton;
    int __heightButton;

    WidgetButton *__pButtonXPlus;
    WidgetButton *__pButtonXMinus;

    WidgetButton *__pButtonYPlus;
    WidgetButton *__pButtonYMinus;

    WidgetButton *__pButtonZPlus;
    WidgetButton *__pButtonZMinus;
//______________________________________________________
signals:

//______________________________________________________
private slots:
    void slotJogTCPRotationIncrease(int index);
    void slotJogTCPRotationDecrease(int index);
    void slotStop();
};
//__________________________________________________________


#endif // MOVEROTATION3D_H
