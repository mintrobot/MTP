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

#include "WidgetProjectEditorMenu.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetProjectEditorMenu::WidgetProjectEditorMenu(QWidget *parent) : MTPWidget(parent) {

    __pRectBackground = new WidgetRect(this);
    __pRectBackground->setColor(SingletonColor::GetInstance().ColorProjectEditorWidgetMenuBackground);

    pMenuSystem = new MenuSystem(this, VIEW_ID_MAIN_MENU_SYSTEM);
    pMenuProject = new MenuProject(this, VIEW_ID_MAIN_MENU_PROJECT);
    pMenuRobot = new MenuRobot(this, VIEW_ID_MAIN_MENU_ROBOT);
    pMenuFlowControl = new MenuFlowControl(this, VIEW_ID_MAIN_MENU_FLOWCONTROL);
    pMenuIO = new MenuIO(this, VIEW_ID_MAIN_MENU_IO);

    listMenu.append(pMenuSystem);
    listMenu.append(pMenuProject);
    listMenu.append(pMenuRobot);
    listMenu.append(pMenuFlowControl);
    listMenu.append(pMenuIO);

    for (int i = 0; i < listMenu.size(); i++){
        listMenuExpandStatus.append(false);
        listMenuHeight.append(0);
    }

    connect(pMenuSystem, SIGNAL(onExpandItems(int)), this, SLOT(expandMenuItems(int)));
    connect(pMenuSystem, SIGNAL(onCollapseItems(int)), this, SLOT(collapseItems(int)));
    connect(pMenuSystem, SIGNAL(onSelectItem(int)), this, SLOT(processSelectedMenuItem(int)));

    connect(pMenuProject, SIGNAL(onExpandItems(int)), this, SLOT(expandMenuItems(int)));
    connect(pMenuProject, SIGNAL(onCollapseItems(int)), this, SLOT(collapseItems(int)));
    connect(pMenuProject, SIGNAL(onSelectItem(int)), this, SLOT(processSelectedMenuItem(int)));

    connect(pMenuRobot, SIGNAL(onExpandItems(int)), this, SLOT(expandMenuItems(int)));
    connect(pMenuRobot, SIGNAL(onCollapseItems(int)), this, SLOT(collapseItems(int)));
    connect(pMenuRobot, SIGNAL(onSelectItem(int)), this, SLOT(processSelectedMenuItem(int)));

    connect(pMenuFlowControl, SIGNAL(onExpandItems(int)), this, SLOT(expandMenuItems(int)));
    connect(pMenuFlowControl, SIGNAL(onCollapseItems(int)), this, SLOT(collapseItems(int)));
    connect(pMenuFlowControl, SIGNAL(onSelectItem(int)), this, SLOT(processSelectedMenuItem(int)));

    connect(pMenuIO, SIGNAL(onExpandItems(int)), this, SLOT(expandMenuItems(int)));
    connect(pMenuIO, SIGNAL(onCollapseItems(int)), this, SLOT(collapseItems(int)));
    connect(pMenuIO, SIGNAL(onSelectItem(int)), this, SLOT(processSelectedMenuItem(int)));

}

WidgetProjectEditorMenu::~WidgetProjectEditorMenu() {

}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//
void WidgetProjectEditorMenu::resizeEvent(QResizeEvent * event) {

    Q_UNUSED(event);

    __sizeWidth = width();
    __sizeHeight = height();

    __marginWidth = static_cast<int>(__sizeWidth * __ratioMarginWidth / 100);
    __marginHeight = static_cast<int>(__sizeHeight * __ratioMarginHeight / 100);

    __heightItem = static_cast<int>(__sizeHeight * __ratioItemHeight / 100);

    for (int i =0; i < listMenu.size(); i++) {
        bool status = listMenuExpandStatus.at(i);
        if (status) {
            listMenuHeight[i] = __heightItem + __heightItem * listMenu.at(i)->getItemSize();
        }
        else {
            listMenuHeight[i] = __heightItem;
        }
    }
    __pRectBackground->setGeometry(0, 0, __sizeWidth, __sizeHeight);


    int cumulatedHeight = 0;
    for (int i = 0; i < listMenu.size(); i++) {
        listMenu.at(i)->setGeometry(0, cumulatedHeight, __sizeWidth, listMenuHeight.at(i));
        cumulatedHeight += listMenuHeight.at(i);
    }
}

//_______________________________________PRIVATE______________________________________//


//_______________________________________SLOTS________________________________________//
void WidgetProjectEditorMenu::expandMenuItems(int id) {
    int indexExpandItem = 0;
    Menu* pMenu;
    for (int i = 0; i < listMenu.size(); i++) {
        pMenu = listMenu.at(i);
        pMenu->collapseItems();
        listMenuExpandStatus[i] = false;
    }

    switch(id) {
    case VIEW_ID_MAIN_MENU_SYSTEM:
        indexExpandItem = 0;
        break;

    case VIEW_ID_MAIN_MENU_PROJECT:
        indexExpandItem = 1;
        break;

    case VIEW_ID_MAIN_MENU_ROBOT:
        indexExpandItem = 2;
        break;

    case VIEW_ID_MAIN_MENU_FLOWCONTROL:
        indexExpandItem = 3;
        break;

    case VIEW_ID_MAIN_MENU_IO:
        indexExpandItem = 4;
        break;
    }
    listMenuExpandStatus[indexExpandItem] = true;    
    resizeEvent(nullptr);
    update();
}

void WidgetProjectEditorMenu::collapseItems(int id) {
    int indexExpandItem = 0;
    switch(id) {
    case VIEW_ID_MAIN_MENU_SYSTEM:
        indexExpandItem = 0;
        break;

    case VIEW_ID_MAIN_MENU_PROJECT:
        indexExpandItem = 1;
        break;

    case VIEW_ID_MAIN_MENU_ROBOT:
        indexExpandItem = 2;
        break;

    case VIEW_ID_MAIN_MENU_FLOWCONTROL:
        indexExpandItem = 3;
        break;

    case VIEW_ID_MAIN_MENU_IO:
        indexExpandItem = 4;
        break;
    }
    listMenuExpandStatus[indexExpandItem] = false;
    resizeEvent(nullptr);
    update();
}

void WidgetProjectEditorMenu::processSelectedMenuItem(int id) {

    switch (id) {
    case PROJECT_EDITOR_MENU_SAVE_PROJECT:
        emit signalClickSaveProject();
        break;

    case PROJECT_EDITOR_MENU_LOAD_PROJECT:
        emit signalClickLoadProject();
        break;

    case PROJECT_EDITOR_MENU_PLAY_PROJECT:
        emit signalClickPlayProject();
        break;

    case PROJECT_EDITOR_BUTTON_ADD_NEW_VARIABLE:
        emit onClickNodeAssignVariable();
        break;

    case PROJECT_EDITOR_BUTTON_MOVE_ROBOT_JOINT:
        emit onClickNodeMoveJoint();
        break;

    case PROJECT_EDITOR_BUTTON_MOVE_ROBOT_TCP:
        emit onClickNodeMoveTCP();
        break;

    case PROJECT_EDITOR_BUTTON_IF:
        emit onClickNodeIf(ModelNodeConditional::IF);
        break;

    case PROJECT_EDITOR_BUTTON_ELSEIF:
        emit onClickNodeElseIf(ModelNodeConditional::ELSEIF);
        break;

    case PROJECT_EDITOR_BUTTON_ELSE:
        emit onClickNodeElse(ModelNodeConditional::ELSE);
        break;

    case PROJECT_EDITOR_BUTTON_LOOP:
        emit onClickNodeLoop(ModelNodeConditional::LOOP);
        break;

    case PROJECT_EDITOR_BUTTON_DELAY:
        emit onClickNodeDelay();
        break;

    case PROJECT_EDITOR_BUTTON_SET_DIGITAL_OUT:
        emit onClickNodeSetDigitalOut(ModelNodeDigitalIO::SET);
        break;

    case PROJECT_DEITOR_BUTTON_WAIT_DIGITAL_IN:
        emit onClickNodeWaitDigitalIn(ModelNodeDigitalIO::WAIT);
        break;
    }
}
