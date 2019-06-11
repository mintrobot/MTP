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

#include "MenuSystem.h"

//_______________________________________CONSTRUCTOR__________________________________//
MenuSystem::MenuSystem(QWidget *parent, int id) : Menu(parent, id) {

    setMenuName("SYSTEM");
    setMenuColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    __pButtonSaveProject = new WidgetButton(this, PROJECT_EDITOR_MENU_SAVE_PROJECT);
    __pButtonSaveProject->setText("   Save Project");
    __pButtonSaveProject->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonSaveProject->setRoundEnable(false, false, false, false);
    __pButtonSaveProject->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonSaveProject->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonSaveProject->setMargin(0);
    appendItem(__pButtonSaveProject);

    __pButtonLoadProject = new WidgetButton(this, PROJECT_EDITOR_MENU_LOAD_PROJECT);
    __pButtonLoadProject->setText("   Load Project");
    __pButtonLoadProject->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonLoadProject->setRoundEnable(false, false, false, false);
    __pButtonLoadProject->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonLoadProject->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonLoadProject->setMargin(0);
    appendItem(__pButtonLoadProject);

    __pButtonPlayProject = new WidgetButton(this, PROJECT_EDITOR_MENU_PLAY_PROJECT);
    __pButtonPlayProject->setText("   Play Project");
    __pButtonPlayProject->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonPlayProject->setRoundEnable(false, false, false, false);
    __pButtonPlayProject->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonPlayProject->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonPlayProject->setMargin(0);
    appendItem(__pButtonPlayProject);

    __pButtonExit = new WidgetButton(this, VIEW_ID_MAIN_MENU_PROJECT_CLOSE_EDITOR);
    __pButtonExit->setText("   Exit");
    __pButtonExit->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonExit->setRoundEnable(false, false, false, false);
    __pButtonExit->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonExit->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonExit->setMargin(0);
    appendItem(__pButtonExit);

   connect(__pButtonSaveProject, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
   connect(__pButtonLoadProject, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
   connect(__pButtonPlayProject, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
   connect(__pButtonExit, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));

}

MenuSystem::~MenuSystem() {

}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void MenuSystem::processSelectedItem(int id) {
    emit onSelectItem(id);
}
