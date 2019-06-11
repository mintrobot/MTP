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

#include "WidgetProjectEditorPlayer.h"

WidgetProjectEditorPlayer::WidgetProjectEditorPlayer(QWidget *parent) : QWidget(parent) {

    __pRectBackground = new WidgetRect(this);
    __pRectBackground->setColor(SingletonColor::GetInstance().ColorProjectEditorWidgetMenuBackground);

    __pButtonPlayPause = new WidgetButton(this, 0);
    __pButtonPlayPause->setText("Play");
    __pButtonPlayPause->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonPlayPause->setColor(SingletonColor::GetInstance().ColorButtonDefaultClicked);
    __pButtonPlayPause->setColorClicked(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    __pButtonStopExit = new WidgetButton(this, 1);
    __pButtonStopExit->setText("Exit");
    __pButtonStopExit->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonStopExit->setColor(SingletonColor::GetInstance().ColorButtonDefaultClicked);
    __pButtonStopExit->setColorClicked(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    __pLabelJoint = new WidgetLabel(this);
    __pLabelJoint->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelJoint->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pLabelJoint->setText("Joint Value");

    __pLabelTCP = new WidgetLabel(this);
    __pLabelTCP->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelTCP->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pLabelTCP->setText("TCP Value");

    WidgetLabel* pLabel;
    for (int i = 0; i < 6; i++) {
        pLabel = new WidgetLabel(this);
        pLabel->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
        pLabel->setText("J" + QString::number(i));
        __listJointIndex.append(pLabel);

        pLabel = new WidgetLabel(this);
        pLabel->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
        __listTCPIndex.append(pLabel);

        pLabel = new WidgetLabel(this);
        pLabel->setAlign(WidgetLabel::ALIGN_CENTER);
        pLabel->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);
        pLabel->setText("0");
        __listJointValue.append(pLabel);

        pLabel = new WidgetLabel(this);
        pLabel->setAlign(WidgetLabel::ALIGN_CENTER);
        pLabel->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);
        pLabel->setText("0");
        __listTCPValue.append(pLabel);
    }

    __listTCPIndex.at(0)->setText("X");
    __listTCPIndex.at(1)->setText("Y");
    __listTCPIndex.at(2)->setText("Z");
    __listTCPIndex.at(3)->setText("RX");
    __listTCPIndex.at(4)->setText("RY");
    __listTCPIndex.at(5)->setText("RZ");

    connect(__pButtonPlayPause, SIGNAL(onClick(int)), this, SLOT(slotOnPlayPauseButton()));
    connect(__pButtonStopExit, SIGNAL(onClick(int)), this, SLOT(slotOnStopExitButton()));
}


WidgetProjectEditorPlayer::~WidgetProjectEditorPlayer() {

}

//_______________________________________PUBLIC_______________________________________//
WidgetProjectEditorPlayer::PLAYER_STATE WidgetProjectEditorPlayer::getState() {
    return __state;
}

void WidgetProjectEditorPlayer::setState(WidgetProjectEditorPlayer::PLAYER_STATE state) {
    __state = state;
    if (__state == STOP) {
        __pButtonPlayPause->setText("Play");
        __pButtonStopExit->setText("Exit");
    }
    else if (__state == PLAYING) {
        __pButtonPlayPause->setText("Pause");
        __pButtonStopExit->setText("Stop");
    }
    else if (__state == PAUSE) {
        __pButtonPlayPause->setText("Play");
    }
}

//_______________________________________PROTECTED____________________________________//
void WidgetProjectEditorPlayer::resizeEvent(QResizeEvent * event) {

    Q_UNUSED(event);

    __marginWidth = static_cast<int>(width() * __ratioMarginWidth / 100);
    __marginHeight = static_cast<int>(width() * __ratioMarginHeight / 100);
    __sizeButton = static_cast<int>(width() * __ratioSizeButton / 100);
    __widthLabelIndex = static_cast<int>(width() * __ratioWidthLabelIndex / 100);
    __widthLabelValue = static_cast<int>(width() * __ratioWidthLabelValue / 100);
    __heightLabel = static_cast<int>(height() * __ratioHeightLabel / 100);
    __widthSlider = static_cast<int>(width() * __ratioWidthSlider / 100);
    __heightSlider = static_cast<int>(height() * __ratioHeightSlider / 100);
    __widthSliderMinMax = static_cast<int>(width() * __ratioWidthLabelSliderMinMax / 100);

    // set geometry of elements
    __pRectBackground->setGeometry(0, 0, width(), height());
    __pButtonPlayPause->setGeometry(__marginWidth, __marginHeight, __sizeButton, __sizeButton);
    __pButtonStopExit->setGeometry(__pButtonPlayPause->geometry().bottomRight().x() + __marginWidth, __marginHeight, __sizeButton, __sizeButton);

    __pLabelJoint->setGeometry(0, __pButtonPlayPause->geometry().bottomRight().y() +  __marginHeight + __heightLabel, width()/2, __heightLabel);
    __pLabelTCP->setGeometry(__pLabelJoint->geometry().right(), __pLabelJoint->geometry().top(), width()/2, __heightLabel);

    __listJointIndex.at(0)->setGeometry(__marginWidth, __pLabelJoint->geometry().bottomRight().y() + __marginHeight, __widthLabelIndex, __heightLabel);
    __listJointValue.at(0)->setGeometry(__listJointIndex.at(0)->geometry().topRight().x() + __marginWidth, __listJointIndex.at(0)->geometry().top(), __widthLabelValue, __heightLabel);
    __listTCPIndex.at(0)->setGeometry(__listJointValue.at(0)->geometry().topRight().x(), __listJointIndex.at(0)->geometry().top(), __widthLabelIndex, __heightLabel);
    __listTCPValue.at(0)->setGeometry(__listTCPIndex.at(0)->geometry().topRight().x() + __marginWidth, __listJointIndex.at(0)->geometry().top(), __widthLabelValue, __heightLabel);

    for (int i = 1; i < 6; i++) {
        __listJointIndex.at(i)->setGeometry(__marginWidth, __listJointValue.at(i-1)->geometry().bottomRight().y() + __marginHeight, __widthLabelIndex, __heightLabel);
        __listJointValue.at(i)->setGeometry(__listJointIndex.at(i-1)->geometry().topRight().x() + __marginWidth, __listJointValue.at(i-1)->geometry().bottomRight().y() + __marginHeight, __widthLabelValue, __heightLabel);
        __listTCPIndex.at(i)->setGeometry(__listJointValue.at(i-1)->geometry().topRight().x(), __listTCPIndex.at(i-1)->geometry().bottomRight().y() + __marginHeight, __widthLabelIndex, __heightLabel);
        __listTCPValue.at(i)->setGeometry(__listTCPIndex.at(i-1)->geometry().topRight().x() + __marginWidth, __listTCPIndex.at(i-1)->geometry().bottomLeft().y() + __marginHeight, __widthLabelValue, __heightLabel);
    }
}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void WidgetProjectEditorPlayer::slotOnPlayPauseButton() {
    if (__state == STOP) {
        emit signalPlayProject();
    }
    else if (__state == PLAYING) {
        emit signalPauseProject();
    }
    else if (__state == PAUSE) {
        emit signalResumeProject();
    }
}

void WidgetProjectEditorPlayer::slotOnStopExitButton() {
    if (__state == STOP) {
        this->setVisible(false);
    }
    else if (__state == PLAYING) {
        emit signalStopProject();
    }
    else if (__state == PAUSE) {
        emit signalStopProject();
    }
}

void WidgetProjectEditorPlayer::slotUpdateCurrentPosition(QVector<double> vecJoint, QVector<double> vecTCP) {
    for (int i = 0; i < __listJointValue.size(); i++) {
        __listJointValue.at(i)->setText(QString::number(vecJoint.at(i)));
        __listTCPValue.at(i)->setText(QString::number(vecTCP.at(i)));
    }
}
