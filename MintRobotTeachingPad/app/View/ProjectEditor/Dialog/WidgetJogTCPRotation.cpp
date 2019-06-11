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

#include "WidgetJogTCPRotation.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetJogTCPRotation::WidgetJogTCPRotation(QWidget *parent) : MTPWidget(parent) {

    __pButtonXPlus = new WidgetButton(this, 0);
    __pButtonXPlus->setRoundEnable(false, false, false, false);
    __pButtonXPlus->setButtonImage(SingletonImage::GetInstance().ID_ROT_X_PLUS);
    __pButtonXPlus->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);
    __pButtonXPlus->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);

    __pButtonXMinus = new WidgetButton(this, 0);
    __pButtonXMinus->setRoundEnable(false, false, false, false);
    __pButtonXMinus->setButtonImage(SingletonImage::GetInstance().ID_ROT_X_MINUS);
    __pButtonXMinus->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);
    __pButtonXMinus->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);


    __pButtonYPlus = new WidgetButton(this, 1);
    __pButtonYPlus->setRoundEnable(false, false, false, false);
    __pButtonYPlus->setButtonImage(SingletonImage::GetInstance().ID_ROT_Y_PLUS);
    __pButtonYPlus->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);
    __pButtonYPlus->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);

    __pButtonYMinus = new WidgetButton(this, 1);
    __pButtonYMinus->setRoundEnable(false, false, false, false);
    __pButtonYMinus->setButtonImage(SingletonImage::GetInstance().ID_ROT_Y_MINUS);
    __pButtonYMinus->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);
    __pButtonYMinus->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);

    __pButtonZPlus = new WidgetButton(this, 2);
    __pButtonZPlus->setRoundEnable(false, false, false, false);
    __pButtonZPlus->setButtonImage(SingletonImage::GetInstance().ID_ROT_Z_PLUS);
    __pButtonZPlus->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);
    __pButtonZPlus->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);

    __pButtonZMinus = new WidgetButton(this, 2);
    __pButtonZMinus->setRoundEnable(false, false, false, false);
    __pButtonZMinus->setButtonImage(SingletonImage::GetInstance().ID_ROT_Z_MINUS);
    __pButtonZMinus->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);
    __pButtonZMinus->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);

    connect(__pButtonXPlus, SIGNAL(onPress(int)), this, SLOT(slotJogTCPRotationIncrease(int)));
    connect(__pButtonXPlus, SIGNAL(onRelease(int)), this, SLOT(slotStop()));
    connect(__pButtonXMinus, SIGNAL(onPress(int)), this, SLOT(slotJogTCPRotationDecrease(int)));
    connect(__pButtonXMinus, SIGNAL(onRelease(int)), this, SLOT(slotStop()));

    connect(__pButtonYPlus, SIGNAL(onPress(int)), this, SLOT(slotJogTCPRotationIncrease(int)));
    connect(__pButtonYPlus, SIGNAL(onRelease(int)), this, SLOT(slotStop()));
    connect(__pButtonYMinus, SIGNAL(onPress(int)), this, SLOT(slotJogTCPRotationDecrease(int)));
    connect(__pButtonYMinus, SIGNAL(onRelease(int)), this, SLOT(slotStop()));

    connect(__pButtonZPlus, SIGNAL(onPress(int)), this, SLOT(slotJogTCPRotationIncrease(int)));
    connect(__pButtonZPlus, SIGNAL(onRelease(int)), this, SLOT(slotStop()));
    connect(__pButtonZMinus, SIGNAL(onPress(int)), this, SLOT(slotJogTCPRotationDecrease(int)));
    connect(__pButtonZMinus, SIGNAL(onRelease(int)), this, SLOT(slotStop()));
}

WidgetJogTCPRotation::~WidgetJogTCPRotation() {



}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//
void WidgetJogTCPRotation::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);

    __widthMargin = static_cast<int>(width() * __ratioMargin / 100);
    __heightMargin = static_cast<int>(height() * __ratioMargin / 100);
    __widthButton = static_cast<int>(width() * __ratioWidthButton / 100);
    __heightButton = static_cast<int>(height() * __ratioHeightButton / 100);

    __pButtonXPlus->setGeometry(__widthButton + __widthMargin*2,
                                __heightButton*3 + __heightMargin*4,
                                __widthButton,
                                __heightButton);

    __pButtonXMinus->setGeometry(__widthButton + __widthMargin*2,
                                 __heightButton + __heightMargin*2,
                                 __widthButton,
                                 __heightButton);


    __pButtonYMinus->setGeometry(__widthMargin,
                                __heightButton*2 + __heightMargin*3,
                                __widthButton,
                                __heightButton);

    __pButtonYPlus->setGeometry(__widthButton*2 + __widthMargin*3,
                                 __heightButton*2 + __heightMargin*3,
                                 __widthButton,
                                 __heightButton);


    __pButtonZPlus->setGeometry(__widthMargin,
                                __heightMargin,
                                __widthButton,
                                __heightButton);

    __pButtonZMinus->setGeometry(__widthButton*2 + __widthMargin*3,
                                 __heightMargin,
                                 __widthButton,
                                 __heightButton);
}

void WidgetJogTCPRotation::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
}


//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void WidgetJogTCPRotation::slotJogTCPRotationIncrease(int index) {
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->jotTCP(0x02, index, 0x01, 0.1, 10);
}

void WidgetJogTCPRotation::slotJogTCPRotationDecrease(int index) {
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->jotTCP(0x02, index, 0x00, 0.1, 10);
}

void WidgetJogTCPRotation::slotStop() {
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->stopRobot();
}
