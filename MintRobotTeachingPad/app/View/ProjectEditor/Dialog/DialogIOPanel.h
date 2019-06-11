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

#ifndef IOCONTROLLERWIDGET_H
#define IOCONTROLLERWIDGET_H

#include <QPushButton>
#include <QState>

#include "app/controller/SingletonComm.h"
#include "app/view/util/Dialog.h"
#include "app/view/util/WidgetSlideSwitch.h"

#include "WidgetJogJoint.h"
#include "WidgetJogTCPTranslation.h"
#include "WidgetJogPosMonitor.h"

//__________________________________________________________
class DialogIOPanel : public Dialog
{
    Q_OBJECT
public:
    explicit DialogIOPanel(QWidget *parent = nullptr);
    virtual ~DialogIOPanel() override;

protected:
    virtual void resizeEvent(QResizeEvent * event) override;

private:
    double __ratioMargin = 3;

    double __ratioWidthItem = 21.25;
    double __ratioHeightItem = 7.78;

    int __widthMargin;
    int __heightMargin;
    int __widthItem;
    int __heightItem;


    WidgetLabel* __pLabelIn;
    WidgetLabel* __pLabelOut;

    QState* __pStateHigh;
    QState* __pStateLow;
    QList<WidgetLabel*> __listWidgetLabelInput;
    QList<WidgetLabel*> __listWidgetLabelOutput;
    QList<WidgetSlideSwitch*> __listStateButtonInput;
    QList<WidgetSlideSwitch*> __listToggleButtonOutput;
    QList<bool> __listStateInput;
    QList<bool> __listStateOutput;


//______________________________________________________
signals:

//______________________________________________________
private slots:
    void slotToggleOut(int);
    void slotUpdatedIO(const QVector<bool>& vecDigitalIn, const QVector<bool>& vecDigitalOut);
//__________________________________________________________
};

#endif // IOCONTROLLERWIDGET_H
