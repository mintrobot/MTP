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

#include "WidgetJogJoint.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetJogJoint::WidgetJogJoint(QWidget *parent) : MTPWidget(parent) {

    WidgetLabel* pLabel;
    WidgetButton *pButton;
    WidgetSliderBar *pSliderBar;
    double minAngle = 0;
    double maxAngle = 0;

    for (int i = 0; i < 6; i++) {
        pLabel = new WidgetLabel(this);
        pLabel->setText("Joint " + QString::number(i + 1));
        pLabel->setTextColor(__colorLabelIndexText);
        __listLabelJointIndex.append(pLabel);

        pButton = new WidgetButton(this, i);
        pButton->setButtonImage(SingletonImage::GetInstance().ID_ADD);
        connect(pButton, SIGNAL(onPress(int)), this, SLOT(slotJogIncrease(int)));
        connect(pButton, SIGNAL(onRelease(int)), this, SLOT(slotStop()));
        __listButtonJointPlus.append(pButton);

        pButton = new WidgetButton(this, i);
        pButton->setButtonImage(SingletonImage::GetInstance().ID_MINUS);
        connect(pButton, SIGNAL(onPress(int)), this, SLOT(slotJogDecrease(int)));
        connect(pButton, SIGNAL(onRelease(int)), this, SLOT(slotStop()));
        __listButtonJointMinus.append(pButton);

        minAngle = SingletonConfiguration::GetInstance().vecMinAngle.at(i);
        maxAngle = SingletonConfiguration::GetInstance().vecMaxAngle.at(i);
        pSliderBar = new WidgetSliderBar(this, i);
        pSliderBar->setRange(static_cast<int>(minAngle), static_cast<int>(maxAngle));
        pSliderBar->setValue(0);
        pSliderBar->setVerticalMode(false);
        // Add here the range of the slider by referencing confuration instance (singleton)
        __listSliderBar.append(pSliderBar);
    }
}

WidgetJogJoint::~WidgetJogJoint() {

}

//_______________________________________PUBLIC_______________________________________//
void WidgetJogJoint::setPos(const QVector<double>& vecJoint, const QVector<double>& vecTCP) {
    Q_UNUSED(vecTCP);
    for (int i = 0 ; i < vecJoint.size(); i++) {
//        __list
    }
}

//_______________________________________PROTECTED____________________________________//
void WidgetJogJoint::resizeEvent(QResizeEvent * event) {

    Q_UNUSED(event);
    __widthMargin = static_cast<int>(width() * __ratioMargin / 100);
    __heightMargin = static_cast<int>(height() * __ratioMargin / 100);

    __heightItem = static_cast<int>(height() * __ratioHeightItem / 100);
    __widthLabelIndex = static_cast<int>(width() * __ratioWidthLabelIndex / 100);
    __widthSliderBar = static_cast<int>(width() * __ratioWidthSliderBar / 100);

    WidgetLabel* pLabel;
    WidgetButton *pButton;
    WidgetSliderBar *pSliderBar;

    for (int i = 0; i < 6; i++) {
        pLabel = __listLabelJointIndex.at(i);
        pLabel->setGeometry(__widthMargin,
                            __heightMargin + (__heightItem + __heightMargin)*i,
                            __widthLabelIndex,
                            __heightItem);

        pButton = __listButtonJointMinus.at(i);
        pButton->setGeometry(__widthLabelIndex + __widthMargin*2,
                             __heightMargin + (__heightItem + __heightMargin)*i,
                             __heightItem,
                             __heightItem);

        pSliderBar = __listSliderBar.at(i);
        pSliderBar->setGeometry(__widthLabelIndex + __heightItem + __widthMargin*3,
                                __heightMargin + (__heightItem + __heightMargin)*i,
                                __widthSliderBar,
                                __heightItem);

        pButton = __listButtonJointPlus.at(i);
        pButton->setGeometry(__widthLabelIndex + __heightItem + __widthSliderBar + __widthMargin*4,
                             __heightMargin + (__heightItem + __heightMargin)*i,
                             __heightItem,
                             __heightItem);
    }
}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void WidgetJogJoint::slotUpdatePos(const QVector<double>& vecJoint, const QVector<double>& vecTCP) {
    Q_UNUSED(vecTCP);
    for (int i = 0; i < 6; i++) {
        __listSliderBar.at(i)->setValue(static_cast<int>(vecJoint.at(i)));
    }
}

void WidgetJogJoint::slotJogIncrease(int index) {
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->jogJoint(index, 1, 0.2, 10);
}

void WidgetJogJoint::slotJogDecrease(int index) {
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->jogJoint(index, 0, 0.2, 10);
}

void WidgetJogJoint::slotStop() {
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->stopRobot();
}
