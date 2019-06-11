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

#ifndef SINGLETONPROJECTEDITORWARNING_H
#define SINGLETONPROJECTEDITORWARNING_H

#include "app/view/util/MTPWidget.h"
#include "app/view/util/WidgetRect.h"
#include "app/view/util/WidgetLabel.h"
#include "app/view/util/WidgetButton.h"

class SingletonProjectEditorWarning : public MTPWidget
{
    Q_OBJECT
public:
    explicit SingletonProjectEditorWarning(QWidget *parent = nullptr);
    virtual ~SingletonProjectEditorWarning() override;

    static SingletonProjectEditorWarning &GetInstance() {
        static SingletonProjectEditorWarning instance;
        return instance;
    }

    void warningEmptyProject();
    void warningRobotNotReady();
    void warningNotOperable();
    void warningOnBrake();
    void warningRobotIsOperating();
    void warningSelfCollisionPredicted();
    void warningJointLimit();
    void warningTrajectoryGenerateFailed();
    void warningCollosionDetected();

protected:
    virtual void resizeEvent(QResizeEvent * event) override;


private:
    double __ratioTitleHeight = 10;
    int __heightTitleBar;

    WidgetRect* __pRectContents;
    WidgetRect* __pRectTitle;
    WidgetLabel* __pLabelTitle;

    WidgetButton *__pButtonClose;
    WidgetLabel* __pLabelContents;

signals:

private slots:
    void closeDialog();

};

#endif // SINGLETONPROJECTEDITORWARNING_H
