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

#include "DialogRobotConfiguration.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogRobotConfiguration::DialogRobotConfiguration(QWidget *parent) : Dialog(parent) {

    setSize(60, 60);
    setTitle("Robot Configuration");

    // IP ADdress
    __pLabelNetwork = new WidgetLabel(getContentsWidget());
    __pLabelNetwork->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);
    __pLabelNetwork->setAlign(WidgetLabel::ALIGN_LEFT);
    __pLabelNetwork->setText("Network");

    __pLabelIPAddress = new WidgetLabel(getContentsWidget());
    __pLabelIPAddress->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pLabelIPAddress->setAlign(WidgetLabel::ALIGN_LEFT);
    __pLabelIPAddress->setText("IP Address");

    __pButtonIPAddress = new WidgetButton(getContentsWidget(), ROBOT_CONFIG_IP_ADDRESS);
    __pButtonIPAddress->setRoundRatio(0.3);
    __pButtonIPAddress->setText(SingletonConfiguration::GetInstance().IPAddress);
    __pButtonIPAddress->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);


    // TCP Cofiguration
    __pLabelTCPOffset = new WidgetLabel(getContentsWidget());
    __pLabelTCPOffset->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);
    __pLabelTCPOffset->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelTCPOffset->setText("TCP Offset");

    __pLabelTCPCenterGravity = new WidgetLabel(getContentsWidget());
    __pLabelTCPCenterGravity->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);
    __pLabelTCPCenterGravity->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelTCPCenterGravity->setText("TCP Center of Gravity");

    __pLabelTCPOffsetX = new WidgetLabel(getContentsWidget());
    __pLabelTCPOffsetX->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pLabelTCPOffsetX->setAlign(WidgetLabel::ALIGN_LEFT);
    __pLabelTCPOffsetX->setText("X(m)");

    __pLabelTCPOffsetY = new WidgetLabel(getContentsWidget());
    __pLabelTCPOffsetY->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pLabelTCPOffsetY->setAlign(WidgetLabel::ALIGN_LEFT);
    __pLabelTCPOffsetY->setText("Y(m)");

    __pLabelTCPOffsetZ = new WidgetLabel(getContentsWidget());
    __pLabelTCPOffsetZ->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pLabelTCPOffsetZ->setAlign(WidgetLabel::ALIGN_LEFT);
    __pLabelTCPOffsetZ->setText("Z(m)");


    // Offset
    __pButtonTCPOffsetX = new WidgetButton(getContentsWidget(), ROBOT_CONFIG_TCP_OFFSET_X);
    __pButtonTCPOffsetX->setRoundRatio(0.3);
    __pButtonTCPOffsetX->setText(QString::number(SingletonConfiguration::GetInstance().TCPOffsetX, 'f', 2));
    __pButtonTCPOffsetX->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);

    __pButtonTCPOffsetY = new WidgetButton(getContentsWidget(), ROBOT_CONFIG_TCP_OFFSET_Y);
    __pButtonTCPOffsetY->setRoundRatio(0.3);
    __pButtonTCPOffsetY->setText(QString::number(SingletonConfiguration::GetInstance().TCPOffsetY, 'f', 2));
    __pButtonTCPOffsetY->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);

    __pButtonTCPOffsetZ = new WidgetButton(getContentsWidget(), ROBOT_CONFIG_TCP_OFFSET_Z);
    __pButtonTCPOffsetZ->setRoundRatio(0.3);
    __pButtonTCPOffsetZ->setText(QString::number(SingletonConfiguration::GetInstance().TCPOffsetZ, 'f', 2));
    __pButtonTCPOffsetZ->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);


    // Center of Gravity
    __pButtonTCPCenterGravityX = new WidgetButton(getContentsWidget(), ROBOT_CONFIG_TCP_COG_X);
    __pButtonTCPCenterGravityX->setRoundRatio(0.3);
    __pButtonTCPCenterGravityX->setText(QString::number(SingletonConfiguration::GetInstance().TCPCOGX, 'f', 2));
    __pButtonTCPCenterGravityX->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);

    __pButtonTCPCenterGravityY = new WidgetButton(getContentsWidget(), ROBOT_CONFIG_TCP_COG_Y);
    __pButtonTCPCenterGravityY->setRoundRatio(0.3);
    __pButtonTCPCenterGravityY->setText(QString::number(SingletonConfiguration::GetInstance().TCPCOGY, 'f', 2));
    __pButtonTCPCenterGravityY->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);

    __pButtonTCPCenterGravityZ = new WidgetButton(getContentsWidget(), ROBOT_CONFIG_TCP_COG_Z);
    __pButtonTCPCenterGravityZ->setRoundRatio(0.3);
    __pButtonTCPCenterGravityZ->setText(QString::number(SingletonConfiguration::GetInstance().TCPCOGZ, 'f', 2));
    __pButtonTCPCenterGravityZ->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);


    // Weight
    __pLabelTCPWeight = new WidgetLabel(getContentsWidget());
    __pLabelTCPWeight->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pLabelTCPWeight->setAlign(WidgetLabel::ALIGN_LEFT);
    __pLabelTCPWeight->setText("Weight(kg)");

    __pButtonTCPWeight = new WidgetButton(getContentsWidget(), ROBOT_CONFIG_TCP_WEIGHT);
    __pButtonTCPWeight->setRoundRatio(0.3);
    __pButtonTCPWeight->setText(QString::number(SingletonConfiguration::GetInstance().TCPWeight));
    __pButtonTCPWeight->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);

    __pDialogKeypad = new DialogKeypad(this);
    __pDialogKeypad->setVisible(false);

    connect(__pButtonIPAddress, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));
    connect(__pButtonTCPOffsetX, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));
    connect(__pButtonTCPOffsetY, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));
    connect(__pButtonTCPOffsetZ, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));
    connect(__pButtonTCPCenterGravityX, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));
    connect(__pButtonTCPCenterGravityY, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));
    connect(__pButtonTCPCenterGravityZ, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));
    connect(__pButtonTCPWeight, SIGNAL(onClick(int)), this, SLOT(slotOpenKeypad(int)));

    connect(__pDialogKeypad, SIGNAL(onDialogClickOK(int)), this, SLOT(slotOnChangeConfigurationValue()));

}

DialogRobotConfiguration::~DialogRobotConfiguration() {

}

//_______________________________________PUBLIC_______________________________________//
QString DialogRobotConfiguration::getIPAddress() {
    return __pButtonIPAddress->getText();
}

QString DialogRobotConfiguration::getTCPOffsetX() {
    return __pButtonTCPOffsetX->getText();
}

QString DialogRobotConfiguration::getTCPOffsetY() {
    return __pButtonTCPOffsetY->getText();
}

QString DialogRobotConfiguration::getTCPOffsetZ() {
    return __pButtonTCPOffsetZ->getText();
}

QString DialogRobotConfiguration::getTCPCOGX() {
    return __pButtonTCPCenterGravityX->getText();
}

QString DialogRobotConfiguration::getTCPCOGY() {
    return __pButtonTCPCenterGravityY->getText();
}

QString DialogRobotConfiguration::getTCPCOGZ() {
    return __pButtonTCPCenterGravityZ->getText();
}

QString DialogRobotConfiguration::getTCPOffsetWeight() {
    return __pButtonTCPWeight->getText();
}

//_______________________________________PROTECTED____________________________________//
void DialogRobotConfiguration::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);

    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);

    __widthLabel = static_cast<int>(_widthContentsBox * __ratioWidthLabel / 100);
    __widthButton = static_cast<int>(_widthContentsBox * __ratioWidthButton / 100);
    __heightItem = static_cast<int>(_heightContentsBox * __ratioHeightItem / 100);

    __pLabelNetwork->setGeometry(__widthMargin, __heightMargin, __widthLabel, __heightItem);

    __pLabelIPAddress->setGeometry(__widthMargin,
                                   __pLabelNetwork->geometry().bottomLeft().y() + __heightMargin,
                                   __widthLabel,
                                   __heightItem);

    __pButtonIPAddress->setGeometry(__pLabelIPAddress->geometry().bottomRight().x() + __widthMargin,
                                    __pLabelIPAddress->geometry().topLeft().y(),
                                    __widthButton,
                                    __heightItem);

    __pLabelTCPOffset->setGeometry(__widthLabel + __widthMargin*2,
                             __pLabelIPAddress->geometry().bottomLeft().y() + __heightMargin,
                             __widthButton,
                             __heightItem);

    __pLabelTCPCenterGravity->setGeometry(__pLabelTCPOffset->geometry().bottomRight().x() + __widthMargin,
                             __pLabelIPAddress->geometry().bottomLeft().y() + __heightMargin,
                             __widthButton,
                             __heightItem);

    __pLabelTCPOffsetX->setGeometry(__widthMargin,
                             __pLabelTCPOffset->geometry().bottomLeft().y() + __heightMargin,
                             __widthLabel,
                             __heightItem);

    __pLabelTCPOffsetY->setGeometry(__widthMargin,
                             __pLabelTCPOffsetX->geometry().bottomLeft().y() + __heightMargin,
                             __widthLabel,
                             __heightItem);

    __pLabelTCPOffsetZ->setGeometry(__widthMargin,
                             __pLabelTCPOffsetY->geometry().bottomLeft().y() + __heightMargin,
                             __widthLabel,
                             __heightItem);

    __pButtonTCPOffsetX->setGeometry(__pLabelTCPOffsetX->geometry().bottomRight().x() + __widthMargin,
                               __pLabelTCPOffsetX->geometry().topLeft().y(),
                               __widthButton,
                               __heightItem);

    __pButtonTCPOffsetY->setGeometry(__pLabelTCPOffsetY->geometry().bottomRight().x() + __widthMargin,
                               __pLabelTCPOffsetY->geometry().topLeft().y(),
                               __widthButton,
                               __heightItem);

    __pButtonTCPOffsetZ->setGeometry(__pLabelTCPOffsetZ->geometry().bottomRight().x() + __widthMargin,
                               __pLabelTCPOffsetZ->geometry().topLeft().y(),
                               __widthButton,
                               __heightItem);


    __pButtonTCPCenterGravityX->setGeometry(__pButtonTCPOffsetX->geometry().bottomRight().x() + __widthMargin,
                               __pLabelTCPOffsetX->geometry().topLeft().y(),
                               __widthButton,
                               __heightItem);

    __pButtonTCPCenterGravityY->setGeometry(__pButtonTCPOffsetY->geometry().bottomRight().x() + __widthMargin,
                               __pLabelTCPOffsetY->geometry().topLeft().y(),
                               __widthButton,
                               __heightItem);

    __pButtonTCPCenterGravityZ->setGeometry(__pButtonTCPOffsetZ->geometry().bottomRight().x() + __widthMargin,
                               __pLabelTCPOffsetZ->geometry().topLeft().y(),
                               __widthButton,
                               __heightItem);

    __pLabelTCPWeight->setGeometry(__widthMargin,
                             __pLabelTCPOffsetZ->geometry().bottomLeft().y() + __heightMargin,
                             __widthLabel,
                             __heightItem);

    __pButtonTCPWeight->setGeometry(__pLabelTCPWeight->geometry().bottomRight().x() + __widthMargin,
                               __pLabelTCPWeight->geometry().topLeft().y(),
                               __widthButton,
                               __heightItem);


    __pDialogKeypad->setGeometry(0, 0, width(), height());

}

//_______________________________________PRIVATE______________________________________//


//_______________________________________SLOTS________________________________________//
void DialogRobotConfiguration::slotOpenKeypad(int ID) {
    if (ID == ROBOT_CONFIG_IP_ADDRESS) {
        __currentEditElement = IP_ADDRESS;
        __pDialogKeypad->setSignButtonVisiable(false);
        __pDialogKeypad->setText(__pButtonIPAddress->getText());
    }
    else if (ID == ROBOT_CONFIG_TCP_OFFSET_X) {
        __currentEditElement = TCP_OFFSET_X;
        __pDialogKeypad->setSignButtonVisiable(true);
        __pDialogKeypad->setText(__pButtonTCPOffsetX->getText());
    }
    else if (ID == ROBOT_CONFIG_TCP_OFFSET_Y) {
        __currentEditElement = TCP_OFFSET_Y;
        __pDialogKeypad->setSignButtonVisiable(true);
        __pDialogKeypad->setText(__pButtonTCPOffsetY->getText());
    }
    else if (ID == ROBOT_CONFIG_TCP_OFFSET_Z) {
        __currentEditElement = TCP_OFFSET_Z;
        __pDialogKeypad->setSignButtonVisiable(true);
        __pDialogKeypad->setText(__pButtonTCPOffsetZ->getText());
    }
    else if (ID == ROBOT_CONFIG_TCP_COG_X) {
        __currentEditElement = TCP_COG_X;
        __pDialogKeypad->setSignButtonVisiable(true);
        __pDialogKeypad->setText(__pButtonTCPCenterGravityX->getText());
    }
    else if (ID == ROBOT_CONFIG_TCP_COG_Y) {
        __currentEditElement = TCP_COG_Y;
        __pDialogKeypad->setSignButtonVisiable(true);
        __pDialogKeypad->setText(__pButtonTCPCenterGravityY->getText());
    }
    else if (ID == ROBOT_CONFIG_TCP_COG_Z) {
        __currentEditElement = TCP_COG_Z;
        __pDialogKeypad->setSignButtonVisiable(true);
        __pDialogKeypad->setText(__pButtonTCPCenterGravityZ->getText());
    }
    else if (ID == ROBOT_CONFIG_TCP_WEIGHT) {
        __currentEditElement = TCP_WEIGHT;
        __pDialogKeypad->setSignButtonVisiable(false);
        __pDialogKeypad->setText(__pButtonTCPWeight->getText());
    }
    __pDialogKeypad->setVisible(true);
}

void DialogRobotConfiguration::slotOnChangeConfigurationValue() {

    double val = __pDialogKeypad->getText().toDouble();
    if (__currentEditElement == IP_ADDRESS) {
        __pButtonIPAddress->setText(QString::number(val, 'f', 2));
    }
    else if (__currentEditElement == TCP_OFFSET_X) {
        __pButtonTCPOffsetX->setText(QString::number(val, 'f', 2));
    }
    else if (__currentEditElement == TCP_OFFSET_Y) {
        __pButtonTCPOffsetY->setText(QString::number(val, 'f', 2));
    }
    else if (__currentEditElement == TCP_OFFSET_Z) {
        __pButtonTCPOffsetZ->setText(QString::number(val, 'f', 2));
    }
    else if (__currentEditElement == TCP_COG_X) {
        __pButtonTCPCenterGravityX->setText(QString::number(val, 'f', 2));
    }
    else if (__currentEditElement == TCP_COG_Y) {
        __pButtonTCPCenterGravityY->setText(QString::number(val, 'f', 2));
    }
    else if (__currentEditElement == TCP_COG_Z) {
        __pButtonTCPCenterGravityZ->setText(QString::number(val, 'f', 2));
    }
    else if (__currentEditElement == TCP_WEIGHT) {
        __pButtonTCPWeight->setText(QString::number(val, 'f', 2));
    }
}
