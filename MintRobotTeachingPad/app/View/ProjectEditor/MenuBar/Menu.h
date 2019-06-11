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

#ifndef MENU_H
#define MENU_H

#include "app/view/util/MTPWidget.h"
#include "app/view/util/WidgetRect.h"
#include "app/view/util/WidgetLabel.h"
#include "app/view/util/WidgetButton.h"

#include "app/view/viewid.h"
class Menu : public MTPWidget
{
    Q_OBJECT
    public:
        explicit Menu(QWidget *parent = nullptr, int id = 0);
        virtual ~Menu() override;

        void setMenuName(QString name);
        void setMenuColor(QColor color);

        void expandItems();
        void collapseItems();

        void appendItem(WidgetButton* pItemButton);
        void clearItemList();
        int getItemSize();


    protected:
        virtual void resizeEvent(QResizeEvent * event) override;
        virtual void mousePressEvent(QMouseEvent *event) override;

    private:
        int __sizeItemHeight;

        double __textHeightRatio = 0.8;


        int __ID = 0;
        bool __flagExpandStatus = false;

        QString __strName;
        QList<WidgetButton*>* __pListItem;

        WidgetLabel* __pLabelName;

        WidgetRect* __pRectBackground;
        QColor __activeColor = SingletonColor::GetInstance().ColorButtonEmpashize1Clicked;
        QColor __deactiveColor = SingletonColor::GetInstance().ColorProjectEditorWidgetMenuBackground;

        double __ratioMarginWidth = 3;
        double __ratioMarginHeight = 1;
        int __marginWidth;
        int __marginHeight;


    signals:
        void onExpandItems(int id);
        void onCollapseItems(int id);
        void onClickItem(int id);


    private slots:
        void onClickBtnSlot(int id);

};

#endif // MENU_H
