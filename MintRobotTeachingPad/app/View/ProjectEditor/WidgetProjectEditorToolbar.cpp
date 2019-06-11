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

#include "WidgetProjectEditorToolbar.h"

//--- Constructor
WidgetProjectEditorToolbar::WidgetProjectEditorToolbar(QWidget *parent) : MTPWidget (parent) {

    __pRectBackground = new WidgetRect(this);
    __pRectBackground->setColor(SingletonColor::GetInstance().ColorProjectEditorWidgetMenuBackground);

    // Utility Buttons
    __pButtonOpenJogPanel = new WidgetButton(this, PROJECT_EDITOR_MENUBAR_BUTTON_JOG);
    __pButtonOpenJogPanel->setButtonImage(SingletonImage::GetInstance().ID_CONTROLLER1);
    __pButtonOpenJogPanel->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    __pButtonOpenJogPanel->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);

    __pButtonOpenDIOPanel = new WidgetButton(this, PROJECT_EDITOR_MENUBAR_BUTTON_DIO);
    __pButtonOpenDIOPanel->setButtonImage(SingletonImage::GetInstance().ID_IO);
    __pButtonOpenDIOPanel->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    __pButtonOpenDIOPanel->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);

    __pButtonExecute = new WidgetButton(this, PROJECT_EDITOR_MENUBAR_BUTTON_EXECUTE);
    __pButtonExecute->setText("Exe");
    __pButtonExecute->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonExecute->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    __pButtonExecute->setColorClicked(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    __pButtonEdit = new WidgetButton(this, PROJECT_EDITOR_MENUBAR_BUTTON_EDIT);
    __pButtonEdit->setText("Edit");
    __pButtonEdit->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonEdit->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    __pButtonEdit->setColorClicked(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    __pButtonDelete = new WidgetButton(this, PROJECT_EDITOR_MENUBAR_BUTTON_DEL);
    __pButtonDelete->setText("Del");
    __pButtonDelete->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonDelete->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    __pButtonDelete->setColorClicked(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);


    __pButtonIndexUp = new WidgetButton(this, PROJECT_EDITOR_MENUBAR_BUTTON_INDEXUP);
    __pButtonIndexUp->setButtonImage(SingletonImage::GetInstance().ID_ARROW_UP);
    __pButtonIndexUp->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    __pButtonIndexUp->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);

    __pButtonIndexDown = new WidgetButton(this, PROJECT_EDITOR_MENUBAR_BUTTON_INDEX_DOWN);
    __pButtonIndexDown->setButtonImage(SingletonImage::GetInstance().ID_ARROW_DOWN);
    __pButtonIndexDown->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
    __pButtonIndexDown->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);


    // Connections
    connect(__pButtonOpenJogPanel, SIGNAL(onClick(int)), this, SLOT(slotProcessButton(int)));
    connect(__pButtonOpenDIOPanel, SIGNAL(onClick(int)), this, SLOT(slotProcessButton(int)));

    connect(__pButtonExecute, SIGNAL(onClick(int)), this, SLOT(slotProcessButton(int)));
    connect(__pButtonEdit, SIGNAL(onClick(int)), this, SLOT(slotProcessButton(int)));
    connect(__pButtonDelete, SIGNAL(onClick(int)), this, SLOT(slotProcessButton(int)));

    connect(__pButtonIndexUp, SIGNAL(onClick(int)), this, SLOT(slotProcessButton(int)));
    connect(__pButtonIndexDown, SIGNAL(onClick(int)), this, SLOT(slotProcessButton(int)));
}

WidgetProjectEditorToolbar::~WidgetProjectEditorToolbar() {

}


//--- Protected
void WidgetProjectEditorToolbar::resizeEvent(QResizeEvent * event) {

    Q_UNUSED(event);

    __widthMargin = static_cast<int>(width() * __ratioMargin / 100);
    __heightMargin = static_cast<int>(height() * __ratioMargin / 100);
    __sizeUtilityButtons = static_cast<int>(width() * __ratioSizeUtilityButtons / 100);

    __pRectBackground->setGeometry(0, 0, width(), height());

    // Place Utiliy Buttons
    __pButtonOpenJogPanel->setGeometry(__widthMargin, 0, __sizeUtilityButtons, __sizeUtilityButtons);
    __pButtonOpenDIOPanel->setGeometry(__widthMargin, __pButtonOpenJogPanel->geometry().bottomLeft().y() + __heightMargin, __sizeUtilityButtons, __sizeUtilityButtons);

    __pButtonExecute->setGeometry(__widthMargin, static_cast<int>(__ratioSizeUtilityButtons * 3), __sizeUtilityButtons, __sizeUtilityButtons);
    __pButtonEdit->setGeometry(__widthMargin, __pButtonExecute->geometry().bottomLeft().y() + __heightMargin, __sizeUtilityButtons, __sizeUtilityButtons);
    __pButtonDelete->setGeometry(__widthMargin, __pButtonEdit->geometry().bottomLeft().y() + __heightMargin, __sizeUtilityButtons, __sizeUtilityButtons);

    __pButtonIndexDown->setGeometry(__widthMargin, height() - __sizeUtilityButtons - __heightMargin, __sizeUtilityButtons, __sizeUtilityButtons);
    __pButtonIndexUp->setGeometry(__widthMargin, __pButtonIndexDown->geometry().topLeft().y() - __sizeUtilityButtons - __heightMargin*2, __sizeUtilityButtons, __sizeUtilityButtons);

}


//--- Slots
void WidgetProjectEditorToolbar::slotProcessButton(int ID) {

    switch(ID) {
    case PROJECT_EDITOR_MENUBAR_BUTTON_JOG:
        emit signalClickedJogButton();
        break;

    case PROJECT_EDITOR_MENUBAR_BUTTON_DIO:
        emit signalClickedIOButton();
        break;

    case PROJECT_EDITOR_MENUBAR_BUTTON_EXECUTE:
        if (__currentClickMode == PROJECT_EDITOR_MENUBAR_BUTTON_EXECUTE) {
            __pButtonExecute->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
            __currentClickMode = PROJECT_EDITOR_MENUBAR_BUTTON_NORMAL;
            emit signalTirggerNormalMode();
        }
        else {
            __pButtonExecute->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);
            __pButtonEdit->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
            __pButtonDelete->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
            __currentClickMode = PROJECT_EDITOR_MENUBAR_BUTTON_EXECUTE;
            emit signalTriggerExecuteMode();
        }
        update();
        break;

    case PROJECT_EDITOR_MENUBAR_BUTTON_EDIT:
        if (__currentClickMode == PROJECT_EDITOR_MENUBAR_BUTTON_EDIT) {
            __pButtonEdit->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
            __currentClickMode = PROJECT_EDITOR_MENUBAR_BUTTON_NORMAL;
            emit signalTirggerNormalMode();
        }
        else {
            __pButtonExecute->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
            __pButtonEdit->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);
            __pButtonDelete->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
            __currentClickMode = PROJECT_EDITOR_MENUBAR_BUTTON_EDIT;
            emit signalTriggerEditMode();
        }
        update();
        break;

    case PROJECT_EDITOR_MENUBAR_BUTTON_DEL:
        if (__currentClickMode == PROJECT_EDITOR_MENUBAR_BUTTON_DEL) {
            __pButtonDelete->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
            __currentClickMode = PROJECT_EDITOR_MENUBAR_BUTTON_NORMAL;
            emit signalTirggerNormalMode();
        }
        else {
            __pButtonExecute->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
            __pButtonEdit->setColor(SingletonColor::GetInstance().ColorButtonDefaultNormal);
            __pButtonDelete->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);
            __currentClickMode = PROJECT_EDITOR_MENUBAR_BUTTON_DEL;
            emit signalTriggerDeleteMode();
        }
        update();
        break;

    case PROJECT_EDITOR_MENUBAR_BUTTON_INDEXUP:
        emit signalIndexUp();
        break;

    case PROJECT_EDITOR_MENUBAR_BUTTON_INDEX_DOWN:
        emit signalIndexDown();
        break;
    }
}

