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

#ifndef WAITNODESETTING_H
#define WAITNODESETTING_H

#include "app/view/util/Dialog.h"
#include "app/view/util/WidgetKeypad.h"
#include "app/model/nodes/ModelNodeDelay.h"
#include "DialogNode.h"

class DialogNodeDelay : public DialogNode
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit DialogNodeDelay(QWidget *parent = nullptr);
        virtual ~DialogNodeDelay() override;

        void initValue();
        void setValue(const ModelNodeDelay& modelNodeDelay);
        const ModelNodeDelay& getValue();

    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;


    //______________________________________________________
    private:
        ModelNodeDelay __modelNodeDelay;

        double __ratioMargin = 3;

        double __ratioWidthLabel = 30;
        double __ratioWidthLabelValue = 81;
        double __ratioHeightLabel = 10;
        double __ratioWidthKeypad = 94;
        double __ratioHeightKeypad = 81;

        int __widthMargin;
        int __heightMargin;
        int __widthLabel;
        int __heightLabel;
        int __widthLabelValue;
        int __heightLabelValue;
        int __widthKeypad;
        int __heightKeypad;

        WidgetLabel* __pLabel;
        WidgetLabel* __pLabelValue;
        WidgetKeypad* __pKeypadNumber;

        //---
        unsigned int __delayms;
    //______________________________________________________
    signals:

    //______________________________________________________
    private slots:

        void updateValue(QString value);
};
//__________________________________________________________

#endif // WAITNODESETTING_H
