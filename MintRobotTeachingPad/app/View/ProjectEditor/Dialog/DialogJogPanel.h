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

#ifndef CONTROLLER2WIDGET_H
#define CONTROLLER2WIDGET_H

#include "app/view/util/DialogKeypad.h"

#include "WidgetJogJoint.h"
#include "WidgetJogTCPTranslation.h"
#include "WidgetJogTCPRotation.h"
#include "WidgetJogPosMonitor.h"

class DialogJogPanel : public Dialog
{
    Q_OBJECT
public:
    explicit DialogJogPanel(QWidget *parent = nullptr);
    virtual ~DialogJogPanel() override;

protected:
    virtual void resizeEvent(QResizeEvent * event) override;

private:
    double __ratioMargin = 3;

    double __ratioWidthControl = 45.5;
    double __ratioHeightControl = 79;
    double __ratioHeightButton = 10;
    double __ratioWidthButton = 21.25;

    int __widthMargin;
    int __heightMargin;

    int __widthControl;
    int __heightControl;
    int __heightButton;
    int __widthButton;

    WidgetJogJoint* __pWidgetJogJoint;
    WidgetJogTCPTranslation* __pWidgetJogTCPTranslation;
    WidgetJogTCPRotation* __pWidgetJogTCPRotation;
    WidgetJogPosMonitor* __pWidgetPosMonitor;

    WidgetButton* __pButtonJointJog;
    WidgetButton* __pButtonTCPTranslationJog;
    WidgetButton* __pButtonTCPRotationJog;
    WidgetButton* __pButtonDirectTeaching;

//    DialogKeypad* __pDialogKeypad;

//______________________________________________________
signals:
    void signalUpdatedPos(const QVector<double>& vecJoint, const QVector<double>& vecTCP);

//______________________________________________________
private slots:
    void slotChangeJogJoint();
    void slotChangeJogTCPTranslation();
    void slotChangeJogTCPRotation();
    void slotToggleDirectTeaching();
};
//__________________________________________________________

#endif // CONTROLLER2WIDGET_H
