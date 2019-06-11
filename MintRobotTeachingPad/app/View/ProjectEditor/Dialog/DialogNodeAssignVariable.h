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

#ifndef VARIABLENODESETTING_H
#define VARIABLENODESETTING_H

//__________________________________________________________
#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QScrollArea>
#include <QScrollBar>

#include "app/view/SingletonImage.h"
#include "app/view/SingletonColor.h"
#include "app/view/stringid.h"
#include "app/view/viewid.h"
#include "app/view/viewsize.h"

#include "app/view/util/WidgetRect.h"
#include "app/view/util/WidgetButton.h"
#include "app/view/util/WidgetKeypad.h"

#include "app/view/util/WidgetLabel.h"
#include "app/view/util/DialogKeyboard.h"

#include "DialogSelectAssignOperator.h"
#include "DialogAssignValue.h"
#include "DialogSelectVariable.h"

#include "DialogNode.h"

//__________________________________________________________
class DialogNodeAssignVariable : public DialogNode
{
    Q_OBJECT
//______________________________________________________
public:
    explicit DialogNodeAssignVariable(QWidget *parent = nullptr);
    virtual ~DialogNodeAssignVariable() override;

public:
    //--- Public Methods
    void initValue();
    void setValue(const ModelNodeAssignVariable& modelAssignVariable);
    const ModelNodeAssignVariable& getValue();
    void setVariableIDList(const QList<QString>& listVariableName);

    //--- Public Variables


protected:
    virtual void resizeEvent(QResizeEvent * event) override;


private:
    //-- Private Members
    ModelNodeAssignVariable __modelNodeAssignVariable;

    double __ratioMargin = 3;
    double __ratioHeightItem = 45.5;
    double __ratioWidthLabel = 20;
    double __ratioWidthButtonName = 46.1;
    double __ratioWidthButtonSelectVariable = 21.9;
    double __ratioWidthAssignButtons = 21.6;

    int __heightItem;
    int __widthLabel;
    int __widthButtonName;
    int __widthButtonSelectVariable;
    int __widthButtonSelectOperator;
    int __widthAssignButtons;
    int __widthMargin;
    int __heightMargin;

    WidgetLabel* __pLabelName;
    WidgetLabel* __pLabelValue;
    WidgetButton* __pButtonName;
    WidgetButton* __pButtonSelectVariable;

    WidgetButton* __pButtonTarget1;
    bool __flagButtonTarget1VariableID = false;
    WidgetButton* __pButtonTarget2;
    bool __flagButtonTarget2VariableID = false;
    WidgetButton* __pButtonAssignOperator;

    DialogKeyboard* __pDialogKeyboard;
    DialogAssignValue* __pDialogAssignValue;
    DialogSelectVariable* __pDialogSelectVariable;
    DialogSelectAssignOperator* __pDialogSelectAssignOperator;


    //---
    int __indexCurrentEditTarget = 1;


    // Private Methods
    void __updateTexts();
//______________________________________________________
signals:
    void onClickEditName(QString name);
    void onClickValue(double value);

//______________________________________________________
private slots:
    void slotOpenDialogKeyboard();
    void slotOpenDialogSelectVariable();
    void slotOpenDialogAssignVariable(int index);
    void slotOpenDialogSelectAssignOperator();
    void slotAssignVariableName();
    void slotAssignSelectedVariable();
    void slotAssignVariableValue();
    void slotAssignOperator();
};
//__________________________________________________________

#endif // VARIABLENODESETTING_H
