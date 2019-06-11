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

#ifndef DIALOGSELECTASSIGNCONDITION_H
#define DIALOGSELECTASSIGNCONDITION_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QScrollArea>
#include <QScrollBar>
#include <QButtonGroup>
#include <QRadioButton>


#include "app/view/SingletonImage.h"
#include "app/view/SingletonColor.h"
#include "app/view/stringid.h"
#include "app/view/viewid.h"
#include "app/view/viewsize.h"

#include "app/view/util/WidgetRect.h"
#include "app/view/util/WidgetButton.h"
#include "app/view/util/WidgetKeypad.h"

//#include "app/controller/configurationmanager.h"

#include "app/view/util/WidgetLabel.h"

#include "app/view/util/Dialog.h"

#include "app/view/util/WidgetCheckBox.h"


class DialogSelectCompareCondition : public Dialog
{
    Q_OBJECT
    //______________________________________________________
    public:
    typedef enum compare_condition {
        EQUAL = 0,
        GREATER = 1,
        GREATER_EQUAL = 2,
        LESS = 3,
        LESS_EQUAL = 4,
        DIFFERENT = 5,
    } COMPARE_CONDITION;

        explicit DialogSelectCompareCondition(QWidget *parent = nullptr);
        virtual ~DialogSelectCompareCondition() override;

        COMPARE_CONDITION getCompareCondition();

    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:
        double __ratioMargin = 3;
        double __ratioHeightItem = 13.16;

        int __widthMargin;
        int __heightMargin;
        int __heightItem;

        QList<WidgetCheckBox*> __listCheckBox;
        QList<WidgetLabel*> __listLabel;

        WidgetLabel* __pLabelName;
        WidgetLabel* __pLabelValue;

        //---
        COMPARE_CONDITION __compareConditionIndex = EQUAL;

    //______________________________________________________
    signals:
        void onClickEditName(QString name);
        void onClickValue(double value);

    //______________________________________________________
    private slots:
        void changeAssignCondition(int index, bool status);
};

#endif // DIALOGSELECTASSIGNCONDITION_H
