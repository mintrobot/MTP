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

#ifndef ROBOTSETTINGDIALOG_H
#define ROBOTSETTINGDIALOG_H

#include "app/controller/SingletonConfiguration.h"
#include "app/view/util/DialogKeypad.h"

#define ROBOT_CONFIG_IP_ADDRESS         1
#define ROBOT_CONFIG_TCP_OFFSET_X       2
#define ROBOT_CONFIG_TCP_OFFSET_Y       3
#define ROBOT_CONFIG_TCP_OFFSET_Z       4
#define ROBOT_CONFIG_TCP_COG_X          5
#define ROBOT_CONFIG_TCP_COG_Y          6
#define ROBOT_CONFIG_TCP_COG_Z          7
#define ROBOT_CONFIG_TCP_WEIGHT         8

class DialogRobotConfiguration : public Dialog
{
    Q_OBJECT
    typedef enum element {
        IP_ADDRESS,
        TCP_OFFSET_X,
        TCP_OFFSET_Y,
        TCP_OFFSET_Z,
        TCP_COG_X,
        TCP_COG_Y,
        TCP_COG_Z,
        TCP_WEIGHT
    } ELEMENT;
//______________________________________________________
public:
    explicit DialogRobotConfiguration(QWidget *parent = nullptr);
    virtual ~DialogRobotConfiguration() override;

    QString getIPAddress();
    QString getTCPOffsetX();
    QString getTCPOffsetY();
    QString getTCPOffsetZ();
    QString getTCPCOGX();
    QString getTCPCOGY();
    QString getTCPCOGZ();
    QString getTCPOffsetWeight();

//______________________________________________________
protected:
    virtual void resizeEvent(QResizeEvent * event) override;

//______________________________________________________
private:
    double __ratioMargin = 3;
    double __ratioWidthLabel = 15;
    double __ratioWidthButton = 36.5;
    double __ratioHeightItem = 10;

    int __widthMargin;
    int __heightMargin;
    int __widthLabel;
    int __widthButton;
    int __heightItem;

    WidgetLabel* __pLabelNetwork;
    WidgetLabel* __pLabelIPAddress;
    WidgetButton* __pButtonIPAddress;

    WidgetLabel* __pLabelTCPOffset;
    WidgetLabel* __pLabelTCPCenterGravity;

    WidgetLabel* __pLabelTCPOffsetX;
    WidgetLabel* __pLabelTCPOffsetY;
    WidgetLabel* __pLabelTCPOffsetZ;
    WidgetButton* __pButtonTCPOffsetX;
    WidgetButton* __pButtonTCPOffsetY;
    WidgetButton* __pButtonTCPOffsetZ;

    WidgetLabel* __pLabelTCPCenterGravityX;
    WidgetLabel* __pLabelTCPCenterGravityY;
    WidgetLabel* __pLabelTCPCenterGravityZ;
    WidgetButton* __pButtonTCPCenterGravityX;
    WidgetButton* __pButtonTCPCenterGravityY;
    WidgetButton* __pButtonTCPCenterGravityZ;

    WidgetLabel* __pLabelTCPWeight;
    WidgetButton* __pButtonTCPWeight;

    DialogKeypad* __pDialogKeypad;

    ELEMENT __currentEditElement;

//______________________________________________________
signals:
    void onClickApply(int index);
    void onClickCancel();

//______________________________________________________
private slots:
    void slotOpenKeypad(int ID);
    void slotOnChangeConfigurationValue();
};
//__________________________________________________________



#endif // ROBOTSETTINGDIALOG_H
