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

#include "MenuFlowControl.h"

//_______________________________________CONSTRUCTOR__________________________________//
MenuFlowControl::MenuFlowControl(QWidget *parent, int id) : Menu(parent, id) {
    setMenuName("FLOW CONTROL");
    setMenuColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    __pButtonIf = new WidgetButton(this, PROJECT_EDITOR_BUTTON_IF);
    __pButtonIf->setText("   If ");
    __pButtonIf->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonIf->setRoundEnable(false, false, false, false);
    __pButtonIf->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonIf->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonIf->setMargin(0);
    appendItem(__pButtonIf);

    __pButtonElseIf = new WidgetButton(this, PROJECT_EDITOR_BUTTON_ELSEIF);
    __pButtonElseIf->setText("   Else If");
    __pButtonElseIf->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonElseIf->setRoundEnable(false, false, false, false);
    __pButtonElseIf->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonElseIf->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonElseIf->setMargin(0);
    appendItem(__pButtonElseIf);

    __pButtonElse = new WidgetButton(this, PROJECT_EDITOR_BUTTON_ELSE);
    __pButtonElse->setText("   Else");
    __pButtonElse->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonElse->setRoundEnable(false, false, false, false);
    __pButtonElse->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonElse->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonElse->setMargin(0);
    appendItem(__pButtonElse);

    __pButtonLoop = new WidgetButton(this, PROJECT_EDITOR_BUTTON_LOOP);
    __pButtonLoop->setText("   Loop");
    __pButtonLoop->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonLoop->setRoundEnable(false, false, false, false);
    __pButtonLoop->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonLoop->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonLoop->setMargin(0);
    appendItem(__pButtonLoop);

    __pButtonDelay = new WidgetButton(this, PROJECT_EDITOR_BUTTON_DELAY);
    __pButtonDelay->setText("   Delay");
    __pButtonDelay->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonDelay->setRoundEnable(false, false, false, false);
    __pButtonDelay->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonDelay->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonDelay->setMargin(0);
    appendItem(__pButtonDelay);

   connect(__pButtonIf, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
   connect(__pButtonElseIf, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
   connect(__pButtonElse, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
   connect(__pButtonLoop, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
   connect(__pButtonDelay, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
}

MenuFlowControl::~MenuFlowControl() {

}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void MenuFlowControl::processSelectedItem(int id) {
    emit onSelectItem(id);
}

