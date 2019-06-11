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

#include "WidgetJogPosMonitor.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetJogPosMonitor::WidgetJogPosMonitor(QWidget *parent) : MTPWidget(parent)
{
    WidgetLabel* pLabel;

    for (int i = 0; i < 6; i++) {
        __listLabelJointIndex.append(new WidgetLabel(this));
        __listLabelJointValue.append(new WidgetLabel(this));
        __listLabelTCPIndex.append(new WidgetLabel(this));
        __listLabelTCPValue.append(new WidgetLabel(this));
    }

    for (int i = 0; i < 6; i++) {
        pLabel = __listLabelJointIndex.at(i);
        pLabel->setText("Joint " + QString::number(i + 1));
        pLabel->setTextColor(colorLabelIndexText);

        pLabel = __listLabelTCPIndex.at(i);
        pLabel->setTextColor(colorLabelIndexText);
    }

    __listLabelTCPIndex.at(0)->setText("X");
    __listLabelTCPIndex.at(1)->setText("Y");
    __listLabelTCPIndex.at(2)->setText("Z");
    __listLabelTCPIndex.at(3)->setText("RX");
    __listLabelTCPIndex.at(4)->setText("RY");
    __listLabelTCPIndex.at(5)->setText("RZ");

    for (int i = 0; i < 6; i++) {
        pLabel = __listLabelJointValue.at(i);
        pLabel->setTextColor(colorLabelValueText);
        __setJointValue(i, 0);

        pLabel = __listLabelTCPValue.at(i);
        pLabel->setTextColor(colorLabelValueText);
        __setTCPValue(i, 0);
    }

}

WidgetJogPosMonitor::~WidgetJogPosMonitor() {
    WidgetLabel* pLabel;
    for (int i = 0; i < 6; i++) {
        pLabel = __listLabelJointIndex.at(i);
        delete pLabel;

        pLabel = __listLabelTCPIndex.at(i);
        delete pLabel;

        pLabel = __listLabelJointValue.at(i);
        delete pLabel;

        pLabel = __listLabelTCPValue.at(i);
        delete pLabel;
    }
}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//
void WidgetJogPosMonitor::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);

    __widthMargin = static_cast<int>(width() * __ratioMargin / 100);
    __heightMargin = static_cast<int>(height() * __ratioMargin / 100);

    __heightItem = static_cast<int>(height() * __ratioHeightItem / 100);
    __widthLabelIndex = static_cast<int>(width() * __ratioWidthLabelIndex / 100);
    __widthLabelValue = static_cast<int>(width() * __ratioWidthLabelValue / 100);

    WidgetLabel* pLabel;
    for (int i = 0; i < 6; i++) {
        pLabel = __listLabelJointIndex.at(i);
        pLabel->setGeometry(__widthMargin,
                            __heightMargin + (__heightItem + __heightMargin) * i,
                            __widthLabelIndex,
                            __heightItem);

        pLabel = __listLabelJointValue.at(i);
        pLabel->setGeometry(__widthLabelIndex + __widthMargin*2,
                            __heightMargin + (__heightItem + __heightMargin) * i,
                            __widthLabelValue,
                            __heightItem);

        pLabel = __listLabelTCPIndex.at(i);
        pLabel->setGeometry(__widthLabelIndex + __widthLabelValue + __widthMargin*5,
                            __heightMargin + (__heightItem + __heightMargin) * i,
                            __widthLabelIndex,
                            __heightItem);

        pLabel = __listLabelTCPValue.at(i);
        pLabel->setGeometry(__widthLabelIndex*2 + __widthLabelValue + __widthMargin*6,
                            __heightMargin + (__heightItem + __heightMargin) * i,
                            __widthLabelValue,
                            __heightItem);
    }

}

//_______________________________________PRIVATE______________________________________//
void WidgetJogPosMonitor::__setJointValue(int index, double value) {
    WidgetLabel* pLabel;
    QString unit = "˚";
    pLabel = __listLabelJointValue.at(index);
    pLabel->setText(QString::number(value) + unit);
}

void WidgetJogPosMonitor::__setTCPValue(int index, double value) {
    WidgetLabel* pLabel;
    QString unit;
    if (index < 3) {
        unit = "m";
    }
    else {
        unit = "˚";
    }
    pLabel = __listLabelTCPValue.at(index);
    pLabel->setText(QString::number(value) + unit);
}


//--- Slots
void WidgetJogPosMonitor::slotUpdatePos(const QVector<double>& vecJoint, const QVector<double>& vecTCP) {
    for (int i = 0; i < __listLabelJointIndex.size(); i++) {
        __listLabelJointValue.at(i)->setText(QString::number(vecJoint.at(i)));
        __listLabelTCPValue.at(i)->setText(QString::number(vecTCP.at(i)));
    }
}
