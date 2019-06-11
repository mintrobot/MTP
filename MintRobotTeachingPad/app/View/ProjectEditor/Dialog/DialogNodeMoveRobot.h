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

#ifndef DIALOGNODEMOVEJOINT_H
#define DIALOGNODEMOVEJOINT_H

#include "app/controller/SingletonConfiguration.h"

#include "app/model/SingletonInterfaceManager.h"
#include "app/model/project/ModelValue.h"

#include "app/view/util/Dialog.h"
#include "app/view/util/WidgetSlider.h"
#include "app/view/util/WidgetCheckBox.h"
#include "app/view/util/DialogKeypad.h"

#include "DialogAssignValue.h"

#include "app/model/nodes/ModelNodeMoveRobot.h"
#include "DialogNode.h"

class DialogNodeMoveRobot : public DialogNode
{
    Q_OBJECT
public:
    explicit DialogNodeMoveRobot(QWidget *parent = nullptr);
    virtual ~DialogNodeMoveRobot() override;

    void initValue(ModelNodeMoveRobot::MOVETYPE type);
    void setValue(const ModelNodeMoveRobot& modelMoveRobot);
    const ModelNodeMoveRobot& getValue();

    void setVariableIDList(const QList<QString>& listVariableName);


protected:
    virtual void resizeEvent(QResizeEvent * event) override;

private:
    ModelNodeMoveRobot __modelNodeMoveRobot;

    // Variables for coordinates
    double __ratioMargin = 3;

    double __ratioHeightItem = 9.125;
    double __ratioWidthLabelJoint = 15;
    double __ratioWidthButtonJoint = 37;

    double __ratioWidthtVelAcc = 17;

    double __ratioWidthLableRelative = 31.75;
    double __ratioWidthButtonGetCurrentJoint = 30;


    int __widthMargin;
    int __heightMargin;

    int __heightItem;
    int __widthLabelJoint;
    int __widthButtonJoint;

    int __widthVelAcc;
    int __heightVelAcc;
    int __heightSliderVelAcc;

    int __widthLabelRelative;
    int __sizeCheckRelative;
    int __widthButtonGetCurrentJoint;

    int __indexEdit = 0;

    // Widgets
    QList<WidgetLabel*> __listLabelTarget;
    QList<WidgetButton*> __listButtonTarget;

    WidgetLabel* __pLabelMaxVelocity;
    WidgetButton* __pButtonMaxVelocityValue;
    WidgetSlider* __pSliderMaxVelocity;

    WidgetLabel* __pLabelMaxAcceleration;
    WidgetButton* __pButtonMaxAccelerationValue;
    WidgetSlider* __pSliderMaxAcceleration;

    WidgetLabel* __pLabelRelative;
    WidgetCheckBox* __pButtonRelative;
    WidgetButton* __pButtonGetCurrentPos;

    DialogKeypad* __pDialogKeypad;
    DialogAssignValue* __pDialogAssignValue;

    // Colors
    QColor colorJointLabelText = SingletonColor::GetInstance().ColorLabelEmphasize2;
    QColor colorJointButtonText = SingletonColor::GetInstance().ColorLabelTextDefault;
    QColor colorJointButtonForeground = SingletonColor::GetInstance().ColorButtonDefaultNormal;
    QColor colorJointButtonClicked = SingletonColor::GetInstance().ColorButtonDefaultClicked;
    QColor colorVelAccLabelText = SingletonColor::GetInstance().ColorLabelEmphasize2;
    QColor colorButtonForeground = SingletonColor::GetInstance().ColorButtonEmpashize1Normal;
    QColor colorButtonClicked = SingletonColor::GetInstance().ColorButtonEmpashize1Clicked;

    // Private Methods
    void __updateTextes();

signals:


private slots:
    void slotOpenKeypad(int index);
    void slotOpenAssignValue(int index);
    void slotUpdateAssignedValue();
    void slotUpdateSliderValue(int id, int value);
    void slotUpdateFlagRelative(int index, bool flagRelative);
    void getCurrentPos();
};

#endif // DIALOGNODEMOVEJOINT_H
