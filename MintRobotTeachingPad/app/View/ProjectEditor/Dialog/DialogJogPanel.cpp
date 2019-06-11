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

#include "DialogJogPanel.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogJogPanel::DialogJogPanel(QWidget *parent) : Dialog(parent) {
    setTitle("Jog");
    setSize(80,80);
    _flagOkButton = false;

    __pWidgetJogJoint = new WidgetJogJoint(getContentsWidget());
    __pWidgetJogTCPTranslation = new WidgetJogTCPTranslation(getContentsWidget());
    __pWidgetJogTCPRotation = new WidgetJogTCPRotation(getContentsWidget());
    __pWidgetJogTCPTranslation->setVisible(false);
    __pWidgetJogTCPRotation->setVisible(false);


    __pWidgetPosMonitor = new WidgetJogPosMonitor(getContentsWidget());

    __pButtonJointJog = new WidgetButton(getContentsWidget(), 1);
    __pButtonJointJog->setText("Joint Control");

    __pButtonTCPTranslationJog = new WidgetButton(getContentsWidget(), 2);
    __pButtonTCPTranslationJog->setText("TCP Translation");

    __pButtonTCPRotationJog = new WidgetButton(getContentsWidget(), 3);
    __pButtonTCPRotationJog->setText("TCP Rotation");

    __pButtonDirectTeaching = new WidgetButton(getContentsWidget(), 3);
    __pButtonDirectTeaching->setText("Direct Teaching");


    connect(__pButtonJointJog, SIGNAL(onClick(int)), this, SLOT(slotChangeJogJoint()));
    connect(__pButtonTCPTranslationJog, SIGNAL(onClick(int)), this, SLOT(slotChangeJogTCPTranslation()));
    connect(__pButtonTCPRotationJog, SIGNAL(onClick(int)), this, SLOT(slotChangeJogTCPRotation()));
    connect(__pButtonDirectTeaching, SIGNAL(onClick(int)), this, SLOT(slotToggleDirectTeaching()));

    connect(this, SIGNAL(signalUpdatedPos(const QVector<double>&, const QVector<double>&)),
            __pWidgetPosMonitor, SLOT(slotUpdatePos(const QVector<double>&, const QVector<double>&)));

    connect(this, SIGNAL(signalUpdatedPos(const QVector<double>&, const QVector<double>&)),
            __pWidgetJogJoint, SLOT(slotUpdatePos(const QVector<double>&, const QVector<double>&)));

}

DialogJogPanel::~DialogJogPanel() {
    delete __pWidgetJogJoint;
    delete __pWidgetPosMonitor;

    delete __pButtonJointJog;
    delete __pButtonTCPTranslationJog;
    delete __pButtonTCPRotationJog;
    delete __pButtonDirectTeaching;
}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//
void DialogJogPanel::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);

    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);

    __widthControl = static_cast<int>(_widthContentsBox * __ratioWidthControl / 100);
    __heightControl = static_cast<int>(_heightContentsBox * __ratioHeightControl / 100);
    __widthButton = static_cast<int>(_widthContentsBox * __ratioWidthButton / 100);
    __heightButton = static_cast<int>(_heightContentsBox * __ratioHeightButton / 100);

    __pWidgetJogJoint->setGeometry(__widthMargin,
                                   __heightMargin,
                                   __widthControl,
                                   __heightControl);

    __pWidgetJogTCPTranslation->setGeometry(__widthMargin,
                                            __heightMargin,
                                            __widthControl,
                                            __heightControl);

    __pWidgetJogTCPRotation->setGeometry(__widthMargin,
                                            __heightMargin,
                                            __widthControl,
                                            __heightControl);


    __pWidgetPosMonitor->setGeometry(__widthControl + __widthMargin*2,
                                         __heightMargin,
                                         __widthControl,
                                         __heightControl);

    __pButtonJointJog->setGeometry(__widthMargin,
                                   __heightControl + __heightMargin*2,
                                   __widthButton,
                                   __heightButton);

    __pButtonTCPTranslationJog->setGeometry(__widthButton + __widthMargin*2,
                                   __heightControl + __heightMargin*2,
                                   __widthButton,
                                   __heightButton);

    __pButtonTCPRotationJog->setGeometry(__widthButton*2 + __widthMargin*3,
                                   __heightControl + __heightMargin*2,
                                   __widthButton,
                                   __heightButton);

    __pButtonDirectTeaching->setGeometry(__widthButton*3 + __widthMargin*4,
                                   __heightControl + __heightMargin*2,
                                   __widthButton,
                                   __heightButton);
}

//_______________________________________PRIVATE______________________________________//


//_______________________________________SLOTS________________________________________//
void DialogJogPanel::slotChangeJogJoint() {
    __pWidgetJogTCPTranslation->setVisible(false);
    __pWidgetJogTCPRotation->setVisible(false);
    __pWidgetJogJoint->setVisible(true);
}

void DialogJogPanel::slotChangeJogTCPTranslation() {
    __pWidgetJogJoint->setVisible(false);
    __pWidgetJogTCPRotation->setVisible(false);
    __pWidgetJogTCPTranslation->setVisible(true);
}

void DialogJogPanel::slotChangeJogTCPRotation() {
    __pWidgetJogJoint->setVisible(false);
    __pWidgetJogTCPTranslation->setVisible(false);
    __pWidgetJogTCPRotation->setVisible(true);
}

void DialogJogPanel::slotToggleDirectTeaching() {
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->startDirectTeaching();
}



