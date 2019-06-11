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

#include "ViewMainMenu.h"
#include <QList>
//_______________________________________CONSTRUCTOR__________________________________//
ViewMainMenu::ViewMainMenu(QWidget *parent) : QWidget(parent) {
    __backGround = new WidgetLabel(this);
    __initMenuButton();

    pDialogRobotConfiguration = new DialogRobotConfiguration(this);
    pDialogRobotConfiguration->setVisible(false);

    pViewProjectEditor = new ViewProjectEditor(this);
    pViewProjectEditor->setVisible(false);

    connect(pDialogRobotConfiguration, SIGNAL(onDialogClickOK(int)), this, SLOT(slotSaveConfiguration()));
}

ViewMainMenu::~ViewMainMenu() {

}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//
void ViewMainMenu::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event)
    __redrawBackGround();
    __redrawMenuButton();

    pViewProjectEditor->setGeometry(0, 0, width(), height());
    pDialogRobotConfiguration->setGeometry(0, 0, width(),height());
}

//_______________________________________PRIVATE______________________________________//
void ViewMainMenu::__initMenuButton() {
    int margin = 10;
    WidgetButton* pButton;

    pButton = new WidgetButton(this, VIEW_ID_MAIN_ITEM_NEW_PROJECT);
    pButton->setMargin(margin);
    pButton->setRoundEnable(false, false, false, false);
    pButton->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    pButton->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);
    pButton->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    pButton->setTextFontHeightRatio(0.8);
    pButton->setText(STRING_ID_MAIN_ITEM_NEW_PROJECT);
    pButton->setTextFontHeightRatio(0.8);
    pButton->setTextBold(true);
    __listButton.append(pButton);

    pButton = new WidgetButton(this, VIEW_ID_MAIN_ITEM_ROBOT_SETTING);
    pButton->setMargin(margin);
    pButton->setRoundEnable(false, false, false, false);
    pButton->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    pButton->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);
    pButton->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    pButton->setText(STRING_ID_MAIN_ITEM_ROBOT_SETTING);
    pButton->setTextFontHeightRatio(0.8);
    pButton->setTextBold(true);
    __listButton.append(pButton);

    pButton = new WidgetButton(this, VIEW_ID_MAIN_ITEM_EXIT);
    pButton->setMargin(margin);
    pButton->setRoundEnable(false, false, false, false);
    pButton->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    pButton->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);
    pButton->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    pButton->setText(STRING_ID_MAIN_ITEM_EXIT);
    __listButton.append(pButton);

    for (int i = 0; i < __listButton.size(); i++) {
        connect(__listButton.at(i), SIGNAL(onClick(int)), this, SLOT(onClickMenu(int)));
    }
}

void ViewMainMenu::__redrawBackGround() {
    QPixmap pixmap = SingletonImage::GetInstance().getPixmap(SingletonImage::GetInstance().ID_Background, width(), height());
    __backGround->setPixmap(pixmap);
    __backGround->setGeometry(0, 0, width(), height());
}

void ViewMainMenu::__redrawMenuButton() {
    int margin = 10;
    int itemW = ViewSize::GetInstance().KEY_SIZE*5;
    int itemH = ViewSize::GetInstance().KEY_SIZE+margin*2;
    int startX = (width()-itemW)/2;
    int startY = height()/2 - itemH*3;

    for (int i = 0; i < __listButton.size(); i++) {
        WidgetButton* pButton = __listButton.at(i);
        pButton->setGeometry(startX, startY + (itemH * i), itemW, itemH);
    }
}


//_______________________________________SLOTS________________________________________//
void ViewMainMenu::onClickMenu(int id) {
    switch (id) {
    case VIEW_ID_MAIN_ITEM_NEW_PROJECT:
        pViewProjectEditor->setVisible(true);
        break;

    case VIEW_ID_MAIN_ITEM_ROBOT_SETTING:
        pDialogRobotConfiguration->setVisible(true);
        break;

    case VIEW_ID_MAIN_ITEM_EXIT:
        exit(0);
    }
}

void ViewMainMenu::slotSaveConfiguration() {
    SingletonConfiguration::GetInstance().IPAddress = pDialogRobotConfiguration->getIPAddress();
    SingletonConfiguration::GetInstance().TCPOffsetX = pDialogRobotConfiguration->getTCPOffsetX().toDouble();
    SingletonConfiguration::GetInstance().TCPOffsetY = pDialogRobotConfiguration->getTCPOffsetY().toDouble();
    SingletonConfiguration::GetInstance().TCPOffsetZ = pDialogRobotConfiguration->getTCPOffsetZ().toDouble();
    SingletonConfiguration::GetInstance().TCPCOGX = pDialogRobotConfiguration->getTCPCOGX().toDouble();
    SingletonConfiguration::GetInstance().TCPCOGY = pDialogRobotConfiguration->getTCPCOGY().toDouble();
    SingletonConfiguration::GetInstance().TCPCOGZ = pDialogRobotConfiguration->getTCPCOGZ().toDouble();
    SingletonConfiguration::GetInstance().TCPWeight = pDialogRobotConfiguration->getTCPOffsetWeight().toDouble();
    SingletonConfiguration::GetInstance().saveToJson();

    QVector<double> TCPOffset;
    QVector<double> TCPCOG;
    double TCPweight;
    TCPOffset.append(SingletonConfiguration::GetInstance().TCPOffsetX);
    TCPOffset.append(SingletonConfiguration::GetInstance().TCPOffsetY);
    TCPOffset.append(SingletonConfiguration::GetInstance().TCPOffsetZ);
    TCPCOG.append(SingletonConfiguration::GetInstance().TCPCOGX);
    TCPCOG.append(SingletonConfiguration::GetInstance().TCPCOGY);
    TCPCOG.append(SingletonConfiguration::GetInstance().TCPCOGZ);
    TCPweight = SingletonConfiguration::GetInstance().TCPWeight;
    SingletonComm::GetInstance().configureTCPOffset(TCPOffset, TCPCOG, TCPweight);
}
