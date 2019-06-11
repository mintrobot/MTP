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

#include "DialogIOPanel.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogIOPanel::DialogIOPanel(QWidget *parent) : Dialog(parent) {
    setTitle("Digital IO");
    setSize(80,80);
    _flagOkButton = false;

    __pLabelIn = new WidgetLabel(getContentsWidget());
    __pLabelIn->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelIn->setText("Input");
    __pLabelIn->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);

    __pLabelOut = new WidgetLabel(getContentsWidget());
    __pLabelOut->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelOut->setText("Out");
    __pLabelOut->setTextColor(SingletonColor::GetInstance().ColorLabelEmphasize2);

    __pStateHigh = new QState();
    __pStateLow = new QState();

    WidgetLabel* pLabel;
    WidgetSlideSwitch* pSwitch;
    for(int i = 0; i < 8; i++) {
        pLabel = new WidgetLabel(getContentsWidget());
        pLabel->setAlign(WidgetLabel::ALIGN_CENTER);
        pLabel->setText("Index " + QString::number(i));
        __listWidgetLabelInput.append(pLabel);

        pLabel = new WidgetLabel(getContentsWidget());
        pLabel->setAlign(WidgetLabel::ALIGN_CENTER);
        pLabel->setText("Index " + QString::number(i));
        __listWidgetLabelOutput.append(pLabel);

        pSwitch = new WidgetSlideSwitch(getContentsWidget());
        pSwitch->setRoundRatio(0.1);
        pSwitch->setClickable(false);
        __listStateButtonInput.append(pSwitch);

        pSwitch = new WidgetSlideSwitch(getContentsWidget(), i);
        pSwitch->setRoundRatio(0.1);
        __listToggleButtonOutput.append(pSwitch);
        connect(pSwitch, SIGNAL(onClick(int)), this, SLOT(slotToggleOut(int)));

        __listStateInput.append(false);
        __listStateOutput.append(false);
    }
}

DialogIOPanel::~DialogIOPanel() {

}

//_______________________________________PUBLIC_______________________________________//


//_______________________________________PROTECTED____________________________________//
void DialogIOPanel::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);

    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);

    __widthItem = static_cast<int>(_widthContentsBox * __ratioWidthItem / 100);
    __heightItem = static_cast<int>(_heightContentsBox * __ratioHeightItem / 100);


    __pLabelIn->setGeometry(__widthMargin, __heightMargin, __widthItem * 2 + __widthMargin, __heightItem);
    __pLabelOut->setGeometry(__pLabelIn->geometry().bottomRight().x() + __widthMargin,
                             __heightMargin,
                             __widthItem * 2 + __widthMargin,
                             __heightItem);

    __listWidgetLabelInput.at(0)->setGeometry(__widthMargin,
                                              __pLabelIn->geometry().bottomLeft().y() + __heightMargin,
                                              __widthItem,
                                              __heightItem);

    __listStateButtonInput.at(0)->setGeometry(__listWidgetLabelInput.at(0)->geometry().bottomRight().x() + __widthMargin,
                                             __listWidgetLabelInput.at(0)->geometry().topLeft().y(),
                                             __widthItem,
                                             __heightItem);

    __listWidgetLabelOutput.at(0)->setGeometry(__listStateButtonInput.at(0)->geometry().bottomRight().x() + __widthMargin,
                                              __listWidgetLabelInput.at(0)->geometry().topLeft().y(),
                                              __widthItem,
                                              __heightItem);

    __listToggleButtonOutput.at(0)->setGeometry(__listWidgetLabelOutput.at(0)->geometry().bottomRight().x() + __widthMargin,
                                             __listWidgetLabelInput.at(0)->geometry().topLeft().y(),
                                             __widthItem,
                                             __heightItem);


    for (int i = 1; i < 8; i++) {
        __listWidgetLabelInput.at(i)->setGeometry(__widthMargin,
                                                  __listWidgetLabelInput.at(i-1)->geometry().bottomLeft().y() + __heightMargin,
                                                  __widthItem,
                                                  __heightItem);

        __listStateButtonInput.at(i)->setGeometry(__listWidgetLabelInput.at(i-1)->geometry().bottomRight().x() + __widthMargin,
                                                 __listWidgetLabelInput.at(i)->geometry().topLeft().y(),
                                                 __widthItem,
                                                 __heightItem);


        __listWidgetLabelOutput.at(i)->setGeometry(__listStateButtonInput.at(i)->geometry().bottomRight().x() + __widthMargin,
                                                   __listWidgetLabelInput.at(i)->geometry().topLeft().y(),
                                                   __widthItem,
                                                   __heightItem);

        __listToggleButtonOutput.at(i)->setGeometry(__listWidgetLabelOutput.at(i)->geometry().bottomRight().x() + __widthMargin,
                                                 __listWidgetLabelInput.at(i)->geometry().topLeft().y(),
                                                 __widthItem,
                                                 __heightItem);

    }
}
//_______________________________________PRIVATE______________________________________//


//_______________________________________SLOTS________________________________________//
void DialogIOPanel::slotToggleOut(int index) {

    __listStateOutput[index] = !__listStateOutput[index];
    SingletonComm::GetInstance().setIOStatus(index, __listStateOutput[index]);

}



void DialogIOPanel::slotUpdatedIO(const QVector<bool>& vecDigitalIn, const QVector<bool>& vecDigitalOut) {
    Q_UNUSED(vecDigitalOut);
    for (int i = 0; i < 8; i++) {
        __listStateInput[i] = vecDigitalIn.at(i);
        if (__listStateInput[i]) {
            __listStateButtonInput.at(i)->setStatus(true);
        }
        else {
            __listStateButtonInput.at(i)->setStatus(false);
        }
    }
    update();
}

