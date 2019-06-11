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

#ifndef SETOUTPUTSETTING_H
#define SETOUTPUTSETTING_H

#include "app/view/util/Dialog.h"
#include "app/view/util/WidgetSlider.h"
#include "app/view/util/WidgetSlideSwitch.h"
#include "app/model/nodes/ModelNodeDigitalIO.h"
#include "DialogNode.h"

class DialogNodeDigitalInOut : public DialogNode
{
    Q_OBJECT
    //______________________________________________________
public:
    explicit DialogNodeDigitalInOut(QWidget *parent = nullptr);
    virtual ~DialogNodeDigitalInOut() override;

    void initValue(ModelNodeDigitalIO::IOTYPE type);
    void setValue(const ModelNodeDigitalIO& modelNodeDigitalInOut);
    const ModelNodeDigitalIO& getValue();

protected:
    virtual void resizeEvent(QResizeEvent * event) override;

private:
    ModelNodeDigitalIO __modelNodeDigitalInOut;

    // Variables for coordinates
    double __ratioMargin = 3;

    double __ratioWidthLabel = 20;
    double __ratioWidthSwitch = 14.5;
    double __ratioHeightItem = 21.25;

    double __ratioWidthLabelSlider = 15;
    double __ratioHeightLabelSlider = 10;
    double __ratioHeightLabelSliderValue = 10;
    double __ratioHeightSlider = 58;

    int __widthMargin;
    int __heightMargin;

    int __widthLabel;
    int __widthSwitch;
    int __heightItem;

    int __widthLabelSlider;
    int __heightLabelSlider;
    int __heightLabelSliderValue;
    int __heightSlider;

    void __disposeItems();

    // Variables used insternally
    int __indexSelected = -1;
    int __indexPreSelected = -1;
    bool __statusPre = false;
    bool __status = false;


    // Widgets
    QList<WidgetLabel*> __listLabel;
    QList<WidgetSlideSwitch*> __listSwitch;
//    QList<bool> __listSwitchStatus;


    // Using only for wait type
    unsigned int  __timeout;
    WidgetLabel* __pLabelTimeout;
    WidgetLabel* __pLabelTimeoutValue;
    WidgetSlider* __pSliderTimeout;


    // Colors
    QColor colorDefaultText = SingletonColor::GetInstance().ColorLabelTextDefault;
    QColor colorTImeoutText = SingletonColor::GetInstance().ColorLabelEmphasize2;


    // Private Methods
    void __updateTexts();

signals:


private slots:
    void slotChangeStatus(int id);
    void setTimeOut(int id, int timeout);

};
//__________________________________________________________

#endif // SETOUTPUTSETTING_H
