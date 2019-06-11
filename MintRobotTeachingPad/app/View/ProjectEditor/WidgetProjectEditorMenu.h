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

#ifndef MENUBARWIDGET_H
#define MENUBARWIDGET_H

#include "app/view/util/MTPWidget.h"
#include "app/view/projecteditor/menubar/MenuSystem.h"
#include "app/view/projecteditor/menubar/MenuProject.h"
#include "app/view/projecteditor/menubar/MenuRobot.h"
#include "app/view/projecteditor/menubar/MenuFlowControl.h"
#include "app/view/projecteditor/menubar/MenuIO.h"
#include "app/view/projecteditor/dialog/DialogNodeCondition.h"
#include "app/view/projecteditor/dialog/DialogNodeDigitalInOut.h"

class WidgetProjectEditorMenu : public MTPWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit WidgetProjectEditorMenu(QWidget *parent = nullptr);
        virtual ~WidgetProjectEditorMenu() override ;

        // Menu widgets
        MenuSystem* pMenuSystem;
        MenuProject* pMenuProject;
        MenuRobot* pMenuRobot;
        MenuFlowControl* pMenuFlowControl;
        MenuIO* pMenuIO;

    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:        
        int __sizeWidth;
        int __sizeHeight;
        WidgetRect* __pRectBackground;

        double __ratioMarginWidth = 1;
        double __ratioMarginHeight = 1;
        int __marginWidth;
        int __marginHeight;

        double __ratioItemHeight = 6;
        int __heightItem;

        QList<Menu*> listMenu;
        QList<bool> listMenuExpandStatus;
        QList<int> listMenuHeight;
    //______________________________________________________
    signals:
        void onClickItem(int id);
        void onClickItem(QString name, QList<int>* valueList);
        void onClickTitleBtn(int id);

        void signalClickSaveProject();
        void signalClickLoadProject();
        void signalClickPlayProject();

        void onClickNodeAssignVariable();
        void onClickNodeMoveJoint();
        void onClickNodeMoveTCP();
        void onClickNodeIf(ModelNodeConditional::CONDITIONALTYPE type);
        void onClickNodeElseIf(ModelNodeConditional::CONDITIONALTYPE type);
        void onClickNodeElse(ModelNodeConditional::CONDITIONALTYPE type);
        void onClickNodeLoop(ModelNodeConditional::CONDITIONALTYPE type);
        void onClickNodeDelay();
        void onClickNodeSetDigitalOut(ModelNodeDigitalIO::IOTYPE type);
        void onClickNodeWaitDigitalIn(ModelNodeDigitalIO::IOTYPE type);
    //______________________________________________________
    private slots:
        void expandMenuItems(int id);
        void collapseItems(int id);
        void processSelectedMenuItem(int id);
};
//__________________________________________________________


#endif // MENUBARWIDGET_H
