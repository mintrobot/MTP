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

#include "MenuIO.h"

//_______________________________________CONSTRUCTOR__________________________________//
MenuIO::MenuIO(QWidget *parent, int id) : Menu(parent, id) {
    setMenuName("I/O CONTROL");
    setMenuColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    __pButtonSetDigitalOut = new WidgetButton(this, PROJECT_EDITOR_BUTTON_SET_DIGITAL_OUT);
    __pButtonSetDigitalOut->setText("   Set Out");
    __pButtonSetDigitalOut->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonSetDigitalOut->setRoundEnable(false, false, false, false);
    __pButtonSetDigitalOut->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonSetDigitalOut->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonSetDigitalOut->setMargin(0);
    appendItem(__pButtonSetDigitalOut);

    __pButtonWaitDigitalInput = new WidgetButton(this, PROJECT_DEITOR_BUTTON_WAIT_DIGITAL_IN);
    __pButtonWaitDigitalInput->setText("   Wait In");
    __pButtonWaitDigitalInput->setTextAlign(WidgetLabel::ALIGN_LEFT);
    __pButtonWaitDigitalInput->setRoundEnable(false, false, false, false);
    __pButtonWaitDigitalInput->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorProjectEditorNodeItemBackgound, 0xff));
    __pButtonWaitDigitalInput->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonDefaultClicked, 0xff));
    __pButtonWaitDigitalInput->setMargin(0);
    appendItem(__pButtonWaitDigitalInput);

    connect(__pButtonSetDigitalOut, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
    connect(__pButtonWaitDigitalInput, SIGNAL(onClick(int)), this, SLOT(processSelectedItem(int)));
}

MenuIO::~MenuIO() {

}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void MenuIO::processSelectedItem(int id) {
    emit onSelectItem(id);
}

