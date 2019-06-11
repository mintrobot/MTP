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

#include "MenuProject.h"

//_______________________________________CONSTRUCTOR__________________________________//
MenuProject::MenuProject(QWidget *parent, int id) : Menu(parent, id) {
    setMenuName("PROJECT");
    setMenuColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    __pButtonNewVariable = new WidgetButton(this, PROJECT_EDITOR_BUTTON_ADD_NEW_VARIABLE);
    __pButtonNewVariable->setText("   Assign Variable");
    __pButtonNewVariable->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonNewVariable->setRoundEnable(false, false, false, false);
    __pButtonNewVariable->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonNewVariable->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonNewVariable->setMargin(0);
    appendItem(__pButtonNewVariable);

   connect(__pButtonNewVariable, SIGNAL(onClick(int)), this, SIGNAL(onSelectItem(int)));

}

MenuProject::~MenuProject() {

    delete __pButtonNewVariable;
    for (int i = 0; i < __listVariables.size(); i++) {
        delete __listVariables.at(i);
    }
}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void MenuProject::processButtons(int id) {
    Q_UNUSED(id)
}
