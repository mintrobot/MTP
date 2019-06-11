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

#include "DialogSelectCompareCondition.h"

//_______________________________________CONSTRUCTOR__________________________________//
DialogSelectCompareCondition::DialogSelectCompareCondition(QWidget *parent) : Dialog(parent) {

    setSize(30, 35);
    setTitle("Select Compare Condition");

    WidgetLabel* equal = new WidgetLabel(getContentsWidget());
    equal->setText("IS EQUAL (==)");
    WidgetLabel* bigger = new WidgetLabel(getContentsWidget());
    bigger->setText("IS GREATER THAN (>)");

    WidgetLabel* bigger_equal = new WidgetLabel(getContentsWidget());
    bigger_equal->setText("IS GREATER THAN or EQUAL TO (>=)");

    WidgetLabel* smaller = new WidgetLabel(getContentsWidget());
    smaller->setText("IS LESS THAN (<)");

    WidgetLabel* smaller_equal = new WidgetLabel(getContentsWidget());
    smaller_equal->setText("IS LESS THAN or EQUAL TO (<=)");

    WidgetLabel* different = new WidgetLabel(getContentsWidget());
    different->setText("IS NOT (!=))");


    __listLabel.append(equal);
    __listLabel.append(bigger);
    __listLabel.append(bigger_equal);
    __listLabel.append(smaller);
    __listLabel.append(smaller_equal);
    __listLabel.append(different);

    WidgetCheckBox* check;
    for (int i = 0; i < __listLabel.size(); i++) {
            check = new WidgetCheckBox(getContentsWidget(), i);
            connect(check, SIGNAL(onChangeCheckStatus(int, bool)), this, SLOT(changeAssignCondition(int, bool)));
            __listCheckBox.append(check);
    }

    changeAssignCondition(0, true);
}

DialogSelectCompareCondition::~DialogSelectCompareCondition() {
    for (int i = 0; i < __listLabel.size(); i++) {
        delete __listLabel.at(i);
        delete __listCheckBox.at(i);
    }
}

//_______________________________________PUBLIC_______________________________________//
DialogSelectCompareCondition::COMPARE_CONDITION DialogSelectCompareCondition::getCompareCondition() {
    return __compareConditionIndex;
}

//_______________________________________PROTECTED____________________________________//
void DialogSelectCompareCondition::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);

    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);
    __heightItem = static_cast<int>(_heightContentsBox * __ratioHeightItem / 100);

    WidgetCheckBox* check;
    WidgetLabel* label;

    for (int i = 0; i < __listLabel.size(); i++) {
        check = __listCheckBox.at(i);
        label = __listLabel.at(i);

        check->setButtonSize(__heightItem);
        check->setGeometry(__widthMargin,
                           __heightMargin + (__heightMargin + __heightItem) * i,
                           __heightItem,
                           __heightItem);

        label->setGeometry(__heightItem + __widthMargin*2,
                                    __heightMargin + (__heightMargin + __heightItem) * i,
                                    _widthContentsBox - __heightItem - __widthMargin * 3,
                                    __heightItem);
    }
}


//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void DialogSelectCompareCondition::changeAssignCondition(int index, bool status) {

    QList<int> listTmp;
    for(int i = 0; i < 6; i++) {
        if (i != index) {
            listTmp.append(i);
        }
    }
    if (status) {
        __listCheckBox.at(index)->setCheckStatus(true);
        for (int i = 0 ; i < listTmp.size(); i++) {
            __listCheckBox.at(listTmp.at(i))->setCheckStatus(false);
        }
        if (index == 0) {
            __compareConditionIndex = EQUAL;
        }
        else if (index == 1) {
            __compareConditionIndex = GREATER;
        }
        else if (index == 2) {
            __compareConditionIndex = GREATER_EQUAL;
        }
        else if (index == 3) {
            __compareConditionIndex = LESS;
        }
        else if (index == 4) {
            __compareConditionIndex = LESS_EQUAL;
        }
        else if (index == 5) {
            __compareConditionIndex = DIFFERENT;
        }
    }
}

