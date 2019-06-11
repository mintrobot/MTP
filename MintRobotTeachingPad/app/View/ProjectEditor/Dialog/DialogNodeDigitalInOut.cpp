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

#include "DialogNodeDigitalInOut.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogNodeDigitalInOut::DialogNodeDigitalInOut(QWidget *parent) : DialogNode(parent, PROJECT_EDITOR_DIALOG_DIGITAL_INOUT) {

    setSize(60, 40);

    WidgetLabel *pLabel;
    WidgetSlideSwitch *pSwitch;

    for (int i = 0; i < 8; i++) {
        pLabel = new WidgetLabel(getContentsWidget());
        pLabel->setText("Digital Out " + QString::number(i+1));
        pLabel->setTextColor(colorDefaultText);
        pLabel->setAlign(WidgetLabel::ALIGN_CENTER);
        __listLabel.append(pLabel);

        pSwitch = new WidgetSlideSwitch(getContentsWidget(), i);
        connect(pSwitch, SIGNAL(onClick(int)), this, SLOT(slotChangeStatus(int)));
        __listSwitch.append(pSwitch);
    }

    __timeout = 5000;
    __pLabelTimeout = new WidgetLabel(getContentsWidget());
    __pLabelTimeout->setText("Timeout [ms]");
    __pLabelTimeout->setAlign(WidgetLabel::ALIGN_CENTER);

    __pLabelTimeoutValue = new WidgetLabel(getContentsWidget());
    __pLabelTimeoutValue->setText(QString::number(__timeout));
    __pLabelTimeoutValue->setAlign(WidgetLabel::ALIGN_CENTER);

    __pSliderTimeout = new WidgetSlider(getContentsWidget(), true);
    __pSliderTimeout->setRange(0, 10000);
    __pSliderTimeout->setValue(static_cast<int>(__timeout));

    connect(__pSliderTimeout, SIGNAL(valueChanged(int, int)), this, SLOT(setTimeOut(int, int)));
}

DialogNodeDigitalInOut::~DialogNodeDigitalInOut() {

    for(int i = 0; i < 8; i++) {
        delete __listLabel.at(i);
    }

    delete __pLabelTimeout;
    delete __pLabelTimeoutValue;
    delete __pSliderTimeout;
}

//_______________________________________PUBLIC_______________________________________//
void DialogNodeDigitalInOut::initValue(ModelNodeDigitalIO::IOTYPE type) {
    __modelNodeDigitalInOut.ioType = type;
    for (int i = 0; i < 8; i++) {
        __listSwitch.at(i)->setStatus(false);
    }
    __modelNodeDigitalInOut.timeout = 5000;
    __updateTexts();
}

void DialogNodeDigitalInOut::setValue(const ModelNodeDigitalIO& modelNodeDigitalInOut) {
    __modelNodeDigitalInOut.cloneData(modelNodeDigitalInOut);
    __updateTexts();
}

const ModelNodeDigitalIO& DialogNodeDigitalInOut::getValue() {
    return __modelNodeDigitalInOut;
}

//_______________________________________PROTECTED____________________________________//
void DialogNodeDigitalInOut::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);

    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);

    __widthLabel = static_cast<int>(_widthContentsBox * __ratioWidthLabel / 100);
    __widthSwitch = static_cast<int>(_widthContentsBox * __ratioWidthSwitch / 100);

    __heightItem = static_cast<int>(_heightContentsBox * __ratioHeightItem / 100);

    __widthLabelSlider = static_cast<int>(_widthContentsBox * __ratioWidthLabelSlider / 100);
    __heightLabelSlider = static_cast<int>(_heightContentsBox * __ratioHeightLabelSlider / 100);
    __heightLabelSliderValue = static_cast<int>(_heightContentsBox * __ratioHeightLabelSliderValue / 100);
    __heightSlider = static_cast<int>(_heightContentsBox * __ratioHeightSlider / 100);

    __disposeItems();
}

//_______________________________________PRIVATE______________________________________//
void DialogNodeDigitalInOut::__updateTexts() {
    WidgetLabel* pLabel;

    if (__modelNodeDigitalInOut.ioType == ModelNodeDigitalIO::SET) {
        setTitle("Set Digital Out");
    }
    else {
        setTitle("Wait Digital In");
    }

    for (int i = 0; i < 8; i++) {
        pLabel = __listLabel.at(i);
        if (__modelNodeDigitalInOut.ioType == ModelNodeDigitalIO::SET) {
            pLabel->setText("Digital Out " + QString::number(i+1));
        }
        else {
            pLabel->setText("Digital In " + QString::number(i+1));
        }
        __listSwitch.at(i)->setStatus(__modelNodeDigitalInOut.listStatus.at(i));
    }

    __pLabelTimeoutValue->setText(QString::number(__modelNodeDigitalInOut.timeout));
    __disposeItems();

}

void DialogNodeDigitalInOut::__disposeItems() {
    WidgetLabel* pLabel;
    WidgetSlideSwitch* pSwitch;
    int offsetWidth = 0;
    int offsetHeight = 0;

    if (__modelNodeDigitalInOut.ioType == ModelNodeDigitalIO::SET) {
        offsetWidth = __widthLabelSlider / 2;
    }

    for (int i = 0; i < 8; i++) {
        if (i >= 4) {
            if (__modelNodeDigitalInOut.ioType == ModelNodeDigitalIO::SET) {
                offsetWidth = __widthLabelSlider / 2 + __widthMargin*2 + __widthLabel + __widthSwitch;
                offsetHeight = ((__heightMargin + __heightItem) * 4) * -1;
            }
            else {
                offsetWidth = __widthMargin*2 + __widthLabel + __widthSwitch;
                offsetHeight = ((__heightMargin + __heightItem) * 4) * -1;
            }
        }

        pLabel = __listLabel.at(i);
        pLabel->setGeometry(offsetWidth + __widthMargin,
                           offsetHeight +  __heightMargin + (__heightItem + __heightMargin)*i,
                            __widthLabel,
                            __heightItem);

        pSwitch = __listSwitch.at(i);
        pSwitch->setGeometry(offsetWidth + __widthLabel + __widthMargin*2,
                             offsetHeight +  __heightMargin + (__heightItem + __heightMargin)*i,
                             __widthSwitch,
                             __heightItem);
    }

    __pLabelTimeout->setGeometry(__listSwitch.at(4)->geometry().bottomRight().x() + __widthMargin,
                                 __heightMargin,
                                 __widthLabelSlider,
                                 __heightLabelSlider);

    __pLabelTimeoutValue->setGeometry(__listSwitch.at(4)->geometry().bottomRight().x() + __widthMargin,
                                      __heightLabelSlider + __heightMargin*2,
                                      __widthLabelSlider,
                                      __heightLabelSliderValue);

    __pSliderTimeout->setGeometry(__listSwitch.at(4)->geometry().bottomRight().x() + __widthMargin,
                                  __heightLabelSlider + __heightLabelSliderValue + __heightMargin*3,
                                  __widthLabelSlider,
                                  __heightSlider);

    if (__modelNodeDigitalInOut.ioType == ModelNodeDigitalIO::SET) {
        __pLabelTimeout->setVisible(false);
        __pLabelTimeoutValue->setVisible(false);
        __pSliderTimeout->setVisible(false);
    }
    else {
        __pLabelTimeout->setVisible(true);
        __pLabelTimeoutValue->setVisible(true);
        __pSliderTimeout->setVisible(true);
    }
}

//_______________________________________SLOTS________________________________________//
void DialogNodeDigitalInOut::slotChangeStatus(int id) {
    __listSwitch.at(id)->setStatus(__listSwitch.at(id)->getStatus());
    __modelNodeDigitalInOut.listStatus[id] = __listSwitch.at(id)->getStatus();
}

void DialogNodeDigitalInOut::setTimeOut(int id, int timeout) {
    Q_UNUSED(id);
    __pLabelTimeoutValue->setText(QString::number(timeout));
    __modelNodeDigitalInOut.timeout = static_cast<unsigned int>(timeout);
}
