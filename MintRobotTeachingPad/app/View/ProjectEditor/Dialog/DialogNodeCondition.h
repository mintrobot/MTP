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

#ifndef IFSETTINGNODE_H
#define IFSETTINGNODE_H

#include "app/Model/Nodes/ModelNodeConditional.h"
#include "DialogSelectCompareCondition.h"
#include "DialogAssignValue.h"
#include "DialogNode.h"

//__________________________________________________________
class DialogNodeCondition : public DialogNode
{
    Q_OBJECT

public:
    explicit DialogNodeCondition(QWidget *parent = nullptr);
    virtual ~DialogNodeCondition() override;

    //--- Public Methods
    void initValue(ModelNodeConditional::CONDITIONALTYPE type);
    void setValue(const ModelNodeConditional& modelConditional);
    const ModelNodeConditional& getValue();

    void setVariableIDList(const QList<QString>& listVariableName);


protected:
    virtual void resizeEvent(QResizeEvent * event) override;


private:
    //--- Private Members
    ModelNodeConditional __modelNodeConditional;

    double __ratioMargin = 3;
    double __ratioHeightItem = 94;
    double __ratioWidthLabel = 20;
    double __ratioWidthButton = 21.6;

    int __widthMargin;
    int __heightMargin;
    int __heightItem;
    int __widthLabel;
    int __widthButton;

    WidgetLabel* __pLabelCondition;
    WidgetButton* __pButtonTarget1;
    bool __flagButtonTarget1VariableID = false;
    WidgetButton* __pButtonCompareCondition;
    WidgetButton* __pButtonTarget2;
    bool __flagButtonTarget2VariableID = false;


    DialogSelectCompareCondition* __pDialogSelectCompareCondition;
    DialogAssignValue* __pDialogSelectVariable;

    int __indexCurrentEditTarget = 1;

    // Private Methods
    void __updateTexts();

signals:
    void onClickValue(double value);
    void onClickValue(QString valueName);
    void onClickSelectOtherCondition();

//______________________________________________________
private slots:
    void openDialogSelectAssignCondition();
    void openDialogSelectVariable(int);
    void slotAssignVariableValue();
    void slotAssignCondition();
};

#endif // IFSETTINGNODE_H
