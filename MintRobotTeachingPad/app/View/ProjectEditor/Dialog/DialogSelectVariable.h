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

#ifndef DIALOGSELECTVARIABLE_H
#define DIALOGSELECTVARIABLE_H

#include <QListWidget>

#include "app/view/util/Dialog.h"

class DialogSelectVariable : public Dialog
{
    Q_OBJECT

public:
    explicit DialogSelectVariable(QWidget *parent = nullptr);
    virtual ~DialogSelectVariable() override;

    void initValues();
    void setVariableIDList(const QList<QString>& listVariableName);
    QString getValue();

//______________________________________________________
protected:
    virtual void resizeEvent(QResizeEvent * event) override;

//______________________________________________________
private:
    double __ratioMargin = 3;
    double __ratioWidthLabelValue = 94;
    double __ratioHeightContentsSection = 90;
    double __ratioHeightItemInVariableList = 6;


    int __widthMargin;
    int __heightMargin;
    int __widthContentsSection;
    int __heightContentsSection;
    int __heightItemInVariableList;

    QList<WidgetLabel*> __listLabel;
    QListWidget* __pListWidgetScrollArea;

    bool __flagFirst = true;

    // -----
    QString __strValue = "0";


//______________________________________________________
signals:
    void onClickEditName(QString name);
    void onClickValue(double value);

//______________________________________________________
private slots:
    void updateVariableAssign(QListWidgetItem* pItem);
};

#endif // DIALOGSELECTVARIABLE_H
