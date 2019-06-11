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

#ifndef MOVEJOINT6_H
#define MOVEJOINT6_H

#include "app/Controller/SingletonConfiguration.h"
#include "app/Model/SingletonInterfaceManager.h"
#include "app/View/Util/WidgetLabel.h"
#include "app/View/Util/WidgetRect.h"
#include "app/View/Util/WidgetButton.h"
#include "app/view/util/WidgetSliderBar.h"

//__________________________________________________________
class WidgetJogJoint : public MTPWidget
{
    Q_OBJECT
//______________________________________________________
public:
    explicit WidgetJogJoint(QWidget *parent = nullptr);
    virtual  ~WidgetJogJoint() override;

    void setPos(const QVector<double>& vecJoint, const QVector<double>& vecTCP);

//______________________________________________________
protected:
    virtual void resizeEvent(QResizeEvent * event) override;

//______________________________________________________
private:
    double __ratioMargin = 3;

    double __ratioHeightItem = 13.16;
    double __ratioWidthLabelIndex = 15;
    double __ratioWidthSliderBar = 43.68;

    int __widthMargin;
    int __heightMargin;
    int __heightItem;
    int __widthLabelIndex;
    int __widthSliderBar;

    QList<WidgetLabel*> __listLabelJointIndex;
    QList<WidgetButton*> __listButtonJointMinus;
    QList<WidgetButton*> __listButtonJointPlus;
    QList<WidgetSliderBar*> __listSliderBar;

    WidgetLabel* getLabel(QString text, bool title);
    WidgetButton* getButton(int id, bool plus);

    QColor __colorLabelIndexText = SingletonColor::GetInstance().ColorLabelEmphasize2;


//______________________________________________________
signals:


//______________________________________________________
private slots:
    void slotUpdatePos(const QVector<double>& vecJoint, const QVector<double>& vecTCP);
    void slotJogIncrease(int index);
    void slotJogDecrease(int index);
    void slotStop();

};
//__________________________________________________________


#endif // MOVEJOINT6_H
