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

#include "DialogNodeMoveRobot.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogNodeMoveRobot::DialogNodeMoveRobot(QWidget *parent) : DialogNode(parent, PROJECT_EDITOR_DIALOG_MOVE_ROBOT) {

    setSize(60, 60);

    WidgetLabel *pLabel;
    WidgetButton *pButton;

    for (int i = 0; i < 6; i++) {
        pLabel = new WidgetLabel(getContentsWidget());
        pLabel->setAlign(WidgetLabel::ALIGN_CENTER);
        pLabel->setTextColor(colorJointLabelText);
        __listLabelTarget.append(pLabel);

        pButton = new WidgetButton(getContentsWidget(), i);
        pButton->setTextColor(colorJointButtonText);
        pButton->setRoundRatio(0.1);
        connect(pButton, SIGNAL(onClick(int)), this, SLOT(slotOpenAssignValue(int)));
        __listButtonTarget.append(pButton);
    }

    __pLabelMaxVelocity = new WidgetLabel(getContentsWidget());
    __pLabelMaxVelocity->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelMaxVelocity->setTextColor(colorVelAccLabelText);

    __pButtonMaxVelocityValue = new WidgetButton(getContentsWidget(), 6);
    __pButtonMaxVelocityValue->setTextAlign(WidgetLabel::ALIGN_CENTER);
    __pButtonMaxVelocityValue->setTextColor(colorJointButtonText);
    __pButtonMaxVelocityValue->setRoundRatio(0.1);


    __pSliderMaxVelocity = new WidgetSlider(getContentsWidget(), true, 0);
    __pSliderMaxVelocity->setRange(0, 30);

    __pLabelMaxAcceleration = new WidgetLabel(getContentsWidget());
    __pLabelMaxAcceleration->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelMaxAcceleration->setTextColor(colorVelAccLabelText);

    __pButtonMaxAccelerationValue = new WidgetButton(getContentsWidget(), 7);
    __pButtonMaxAccelerationValue->setTextAlign(WidgetLabel::ALIGN_CENTER);
    __pButtonMaxAccelerationValue->setTextColor(colorJointButtonText);
    __pButtonMaxAccelerationValue->setRoundRatio(0.1);

    __pSliderMaxAcceleration = new WidgetSlider(getContentsWidget(), true, 1);
    __pSliderMaxAcceleration->setRange(0, 300);

    __pLabelRelative = new WidgetLabel(getContentsWidget());
    __pLabelRelative->setText("Relative Mode");
    __pLabelRelative->setAlign(WidgetLabel::ALIGN_RIGHT);
    __pLabelRelative->setTextColor(colorJointLabelText);

    __pButtonRelative = new WidgetCheckBox(getContentsWidget());

    __pButtonGetCurrentPos = new WidgetButton(getContentsWidget());
    __pButtonGetCurrentPos->setText("Get Current Pos");
    __pButtonGetCurrentPos->setColor(colorButtonForeground);
    __pButtonGetCurrentPos->setColorClicked(colorButtonClicked);

    __pDialogKeypad = new DialogKeypad(this);
    __pDialogKeypad->setVisible(false);

    __pDialogAssignValue = new DialogAssignValue(this);
    __pDialogAssignValue->setVisible(false);

    connect(__pButtonMaxVelocityValue, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));
    connect(__pButtonMaxAccelerationValue, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));
    connect(__pSliderMaxVelocity, SIGNAL(valueChanged(int, int)), this, SLOT(slotUpdateSliderValue(int, int)));
    connect(__pSliderMaxAcceleration, SIGNAL(valueChanged(int, int)), this, SLOT(slotUpdateSliderValue(int, int)));
    connect(__pButtonGetCurrentPos, SIGNAL(onClick(int)), this, SLOT(getCurrentPos()));
    connect(__pDialogKeypad, SIGNAL(onDialogClickOK(int)), this, SLOT(slotUpdateAssignedValue()));
    connect(__pDialogAssignValue, SIGNAL(onDialogClickOK(int)), this, SLOT(slotUpdateAssignedValue()));
    connect(__pButtonRelative, SIGNAL(onChangeCheckStatus(int, bool)), this, SLOT(slotUpdateFlagRelative(int, bool)));
}

DialogNodeMoveRobot::~DialogNodeMoveRobot() {

    for(int i = 0; i < 6; i++) {
        delete __listLabelTarget.at(i);
        delete __listButtonTarget.at(i);
    }

    delete __pLabelMaxVelocity;
    delete __pButtonMaxVelocityValue;
    delete __pSliderMaxVelocity;
    delete __pLabelMaxAcceleration;
    delete __pButtonMaxAccelerationValue;
    delete __pSliderMaxAcceleration;

}

//_______________________________________PUBLIC_______________________________________//
void DialogNodeMoveRobot::initValue(ModelNodeMoveRobot::MOVETYPE type) {

    __modelNodeMoveRobot.moveType = type;

    double vMax = 0;
    double aMax = 0;
    if (__modelNodeMoveRobot.moveType == ModelNodeMoveRobot::JOINT_INTERPOLATION) {
       vMax = SingletonConfiguration::GetInstance().vMaxJoint;
       aMax = SingletonConfiguration::GetInstance().aMaxJoint;
    }
    else if (__modelNodeMoveRobot.moveType == ModelNodeMoveRobot::TCP_LINEAR_INTERPOLATION) {
       vMax = SingletonConfiguration::GetInstance().vMaxTCP;
       aMax = SingletonConfiguration::GetInstance().aMaxTCP;
    }

    for (int i = 0 ; i < 6; i++) {
        __modelNodeMoveRobot.vectorTarget[i].isRreference = false;
        __modelNodeMoveRobot.vectorTarget[i].value = 0.0;
    }
    __modelNodeMoveRobot.vel = vMax * 0.1;
    __modelNodeMoveRobot.accel = aMax * 0.1;
    __modelNodeMoveRobot.flagRelative = false;
    __updateTextes();
}

void DialogNodeMoveRobot::setValue(const ModelNodeMoveRobot& modelNodeMoveRobot) {
    __modelNodeMoveRobot.cloneData(modelNodeMoveRobot);
    __updateTextes();
}

const ModelNodeMoveRobot& DialogNodeMoveRobot::getValue() {
    return __modelNodeMoveRobot;
}

void DialogNodeMoveRobot::setVariableIDList(const QList<QString>& listVariableName) {
    __pDialogAssignValue->setVariableIDList(listVariableName);
}

//_______________________________________PROTECTED____________________________________//
void DialogNodeMoveRobot::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);

    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);

    __heightItem = static_cast<int>(_heightContentsBox * __ratioHeightItem / 100);
    __widthLabelJoint = static_cast<int>(_widthContentsBox * __ratioWidthLabelJoint / 100);
    __widthButtonJoint = static_cast<int>(_widthContentsBox * __ratioWidthButtonJoint / 100);

    __widthVelAcc = static_cast<int>(_widthContentsBox * __ratioWidthtVelAcc / 100);
    __heightVelAcc = __heightItem;
    __heightSliderVelAcc = __heightItem * 4;

    __widthLabelRelative = static_cast<int>(_widthContentsBox * __ratioWidthLableRelative / 100);
    __widthButtonGetCurrentJoint = static_cast<int>(_widthContentsBox * __ratioWidthButtonGetCurrentJoint / 100);

    WidgetLabel* pLabel;
    WidgetButton* pButton;

    for (int i = 0; i < 6; i++) {

        pLabel = __listLabelTarget.at(i);
        pLabel->setGeometry(__widthMargin,
                           __heightMargin + (__heightMargin + __heightItem) * i,
                            __widthLabelJoint,
                            __heightItem);

        pButton = __listButtonTarget.at(i);
        pButton->setGeometry(__widthLabelJoint + __widthMargin*2,
                             __heightMargin + (__heightMargin + __heightItem) * i,
                             __widthButtonJoint,
                             __heightItem);
    }

    __pLabelMaxVelocity->setGeometry(__widthLabelJoint + __widthButtonJoint + __widthMargin*3,
                                     __heightMargin,
                                     __widthVelAcc,
                                     __heightVelAcc);

    __pButtonMaxVelocityValue->setGeometry(__widthLabelJoint + __widthButtonJoint + __widthMargin*3,
                                          __heightVelAcc + __heightMargin*2,
                                          __widthVelAcc,
                                          __heightVelAcc);

    __pSliderMaxVelocity->setGeometry(__widthLabelJoint + __widthButtonJoint + __widthMargin*3,
                                      __heightVelAcc*2 + __heightMargin*3,
                                      __widthVelAcc,
                                      __heightSliderVelAcc);


    __pLabelMaxAcceleration->setGeometry(__widthLabelJoint + __widthButtonJoint + __widthVelAcc + __widthMargin * 4,
                                         __heightMargin,
                                         __widthVelAcc,
                                         __heightVelAcc);

    __pButtonMaxAccelerationValue->setGeometry(__widthLabelJoint + __widthButtonJoint + __widthVelAcc + __widthMargin * 4,
                                          __heightVelAcc + __heightMargin*2,
                                          __widthVelAcc,
                                          __heightVelAcc);

    __pSliderMaxAcceleration->setGeometry(__widthLabelJoint + __widthButtonJoint + __widthVelAcc + __widthMargin * 4,
                                      __heightVelAcc*2 + __heightMargin*3,
                                      __widthVelAcc,
                                      __heightSliderVelAcc);

    __pLabelRelative->setGeometry(__widthMargin,
                                  __listLabelTarget.at(5)->geometry().bottomRight().y() + __heightItem + __heightMargin*2,
                                  __widthLabelRelative,
                                  __heightItem);

    __pButtonRelative->setButtonSize(__heightItem);
    __pButtonRelative->setGeometry(__pLabelRelative->geometry().bottomRight().x() + __widthMargin,
                                   __listLabelTarget.at(5)->geometry().bottomRight().y() + __heightItem + __heightMargin*2,
                                  __heightItem,
                                  __heightItem);

    __pButtonGetCurrentPos->setGeometry(__pLabelMaxVelocity->geometry().bottomLeft().x(),
                                        __listLabelTarget.at(5)->geometry().bottomRight().y() + __heightItem + __heightMargin*2,
                                        __widthVelAcc * 2 + __widthMargin,
                                        __heightItem);

    __pDialogKeypad->setGeometry(0, 0, width(), height());
    __pDialogAssignValue->setGeometry(0, 0, width(), height());


}

//_____________________________________PRIVATE______________________________________//
void DialogNodeMoveRobot::__updateTextes() {
    WidgetLabel* pLabel;
    if (__modelNodeMoveRobot.moveType == ModelNodeMoveRobot::JOINT_INTERPOLATION) {
        setTitle("Move Joint");
        for (int i = 0; i < 6; i++) {
            pLabel = __listLabelTarget.at(i);
            pLabel->setText("Joint " + QString::number(i+1) + " (°)");
        }
        __pLabelMaxVelocity->setText("Max. Vel. (°/s)");
       __pLabelMaxAcceleration->setText("Max. Acc.(°/s^2)");

       __pSliderMaxVelocity->setRange(0, static_cast<int>(SingletonConfiguration::GetInstance().vMaxJoint * 100));
       __pSliderMaxAcceleration->setRange(0, static_cast<int>(SingletonConfiguration::GetInstance().aMaxJoint * 100));
    }
    else if (__modelNodeMoveRobot.moveType == ModelNodeMoveRobot::TCP_LINEAR_INTERPOLATION) {
        setTitle("Move TCP");
        __listLabelTarget.at(0)->setText("X (m)");
        __listLabelTarget.at(1)->setText("Y (m)");
        __listLabelTarget.at(2)->setText("Z (m)");
        __listLabelTarget.at(3)->setText("RX (°)");
        __listLabelTarget.at(4)->setText("RY (°)");
        __listLabelTarget.at(5)->setText("RZ (°)");
        __pLabelMaxVelocity->setText("Max. Vel. (m/s)");
       __pLabelMaxAcceleration->setText("Max. Acc.(m/s^2)");

       __pSliderMaxVelocity->setRange(0, static_cast<int>(SingletonConfiguration::GetInstance().vMaxTCP * 100));
       __pSliderMaxAcceleration->setRange(0, static_cast<int>(SingletonConfiguration::GetInstance().aMaxTCP * 100));
    }

    for (int i = 0 ; i < 6; i++) {
         if (__modelNodeMoveRobot.vectorTarget.at(i).isRreference) {
             __listButtonTarget.at(i)->setText(__modelNodeMoveRobot.vectorTarget.at(i).referenceName);
         }
         else {
             __listButtonTarget.at(i)->setText(QString::number(__modelNodeMoveRobot.vectorTarget.at(i).value, 'f', 2));
         }
    }

    __pSliderMaxVelocity->setValue(static_cast<int>(__modelNodeMoveRobot.vel * 100));
    __pSliderMaxAcceleration->setValue(static_cast<int>(__modelNodeMoveRobot.accel * 100));
    __pButtonMaxVelocityValue->setText(QString::number(__modelNodeMoveRobot.vel, 'f', 2));
    __pButtonMaxAccelerationValue->setText(QString::number(__modelNodeMoveRobot.accel, 'f', 2));

    __pButtonRelative->setCheckStatus(__modelNodeMoveRobot.flagRelative);
}

//_______________________________________SLOTS________________________________________//
void DialogNodeMoveRobot::slotOpenKeypad(int index) {
    if (index == 6) {
        __pDialogKeypad->setText(__pButtonMaxVelocityValue->getText());
    }
    else if (index == 7) {
        __pDialogKeypad->setText(__pButtonMaxAccelerationValue->getText());
    }
    __pDialogKeypad->setVisible(true);
    __indexEdit = index;
}

void DialogNodeMoveRobot::slotOpenAssignValue(int index) {
//    __pDialogAssignValue->(__listButtonTarget.at(index)->getText());
    __pDialogAssignValue->setVisible(true);
    __indexEdit = index;
}

void DialogNodeMoveRobot::slotUpdateAssignedValue() {
    double value = 0;
    if (__indexEdit < 6) {
        if (!__pDialogAssignValue->flagVariable) {
            value = __pDialogAssignValue->getValue().toDouble();
            if (value > SingletonConfiguration::GetInstance().vecMaxAngle[__indexEdit]) {
                value = SingletonConfiguration::GetInstance().vecMaxAngle[__indexEdit];
            }
            else if (value < SingletonConfiguration::GetInstance().vecMinAngle[__indexEdit]) {
                value = SingletonConfiguration::GetInstance().vecMinAngle[__indexEdit];
            }
            __listButtonTarget.at(__indexEdit)->setText(QString::number(value, 'f', 2));
            __modelNodeMoveRobot.vectorTarget[__indexEdit].isRreference = false;
            __modelNodeMoveRobot.vectorTarget[__indexEdit].value = __pDialogAssignValue->getValue().toDouble();
        }
        else {
            __listButtonTarget.at(__indexEdit)->setText(__pDialogAssignValue->getValue());
            __modelNodeMoveRobot.vectorTarget[__indexEdit].isRreference = true;
            __modelNodeMoveRobot.vectorTarget[__indexEdit].referenceName = __pDialogAssignValue->getValue();
        }
    }
    else if (__indexEdit == 6) {
        value = __pDialogKeypad->getText().toDouble();
        if (value > SingletonConfiguration::GetInstance().vMaxJoint) {
            value = SingletonConfiguration::GetInstance().vMaxJoint;
        }
        __pButtonMaxVelocityValue->setText(QString::number(value, 'f', 2));
        __pSliderMaxVelocity->setValue(static_cast<int>(value));
    }
    else if (__indexEdit == 7) {
        value = __pDialogKeypad->getText().toDouble();
        if (value > SingletonConfiguration::GetInstance().aMaxJoint) {
            value = SingletonConfiguration::GetInstance().aMaxJoint;
        }
        __pButtonMaxAccelerationValue->setText(QString::number(value, 'f', 2));
        __pSliderMaxAcceleration->setValue(static_cast<int>(value));
    }
}

void DialogNodeMoveRobot::slotUpdateSliderValue(int id, int value) {
    double actualValue = static_cast<double>(value) / 100.0;
    if (id == 0 ){
        __pButtonMaxVelocityValue->setText(QString::number(actualValue, 'f', 2));
        __modelNodeMoveRobot.vel = actualValue;
    }
    else {
        __pButtonMaxAccelerationValue->setText(QString::number(actualValue, 'f', 2));
        __modelNodeMoveRobot.accel = actualValue;
    }
}

void DialogNodeMoveRobot::slotUpdateFlagRelative(int index, bool flagRelative) {
    Q_UNUSED(index);
    __modelNodeMoveRobot.flagRelative = flagRelative;
}

void DialogNodeMoveRobot::getCurrentPos() {
    QVector<double> vecTarget = QVector<double>(6);
    if (__modelNodeMoveRobot.moveType == ModelNodeMoveRobot::JOINT_INTERPOLATION) {
        SingletonInterfaceManager::GetInstance().getInterfaceRobot()->getRobotJoint(&vecTarget);
    }
    else {
        SingletonInterfaceManager::GetInstance().getInterfaceRobot()->getRobotTCP(&vecTarget);
    }
    for (int i = 0; i < 6; i++) {
        __listButtonTarget.at(i)->setText(QString::number(vecTarget.at(i)));
        __modelNodeMoveRobot.vectorTarget[i].isRreference = false;
        __modelNodeMoveRobot.vectorTarget[i].value = vecTarget.at(i);
    }
}

