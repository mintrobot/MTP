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

#include "SingletonColor.h"

//_______________________________________CONSTRUCTOR__________________________________//
SingletonColor::SingletonColor(QObject *parent) : QObject(parent) {

    QColor WHITE;
    QColor BLACK;

    QColor LIGHT_GRAY;
    QColor MID_GRAY;
    QColor DARK_GRAY;

    QColor RED;
    QColor GREEN;
    QColor BLUE;

    QColor YELLOW;
    QColor ICEBLUE;
    QColor MINT;
    QColor PEACH;
    QColor ORANGE;
    QColor PURPLE;

    // Color Preset
    WHITE = QColor(0xee, 0xee, 0xee);
    BLACK = QColor(0x06, 0x06, 0x06);

    LIGHT_GRAY = QColor(0x50, 0x50, 0x50);
    MID_GRAY = QColor(0x30, 0x30, 0x30);
    DARK_GRAY = QColor(0x20, 0x20, 0x20);

    RED = QColor(0xff,0x00,0x00);
    GREEN = QColor(0x00, 0xff, 0x00);
    BLUE = QColor(0x00, 0x00, 0xff);
    CYAN = QColor(0x00, 0xff, 0xff);
    YELLOW = QColor(0xff, 0xff, 0x00);
    MEGENTA = QColor(0xff, 0x00, 0xff);

    DARKRED = QColor(0x66, 0x00, 0x00);
    FORESTGREEN = QColor(0x00, 0x66, 0x00);
    DARKBLUE = QColor(0x00, 0x00, 0x66);
    ICEBLUE = QColor(0x4a,0x78,0x9c);
    MINT = QColor(0x3e,0xb4,0x89);
    PEACH = QColor(0xe9,0x6d,0x63);
    ORANGE = QColor(0xf7,0x96,0x46);
    PURPLE = QColor(0x80,0x64,0xa2);

    // Colors of Butons
    ColorButtonDefaultNormal = MID_GRAY;
    ColorButtonDefaultClicked =  LIGHT_GRAY;

    ColorButtonEmpashize1Normal = getColorWithAlpha(FORESTGREEN, 0x30);
    ColorButtonEmpashize1Clicked = FORESTGREEN;

    ColorButtonEmpashize2Normal = getColorWithAlpha(ORANGE, 0x30);
    ColorButtonEmpashize2Clicked = ORANGE;

    ColorButtonEmpashize3Normal = getColorWithAlpha(ICEBLUE, 0x30);
    ColorButtonEmpashize3Clicked = ICEBLUE;

    ColorButtonEmergencyStop = DARKRED;
    ColorButtonEmergencyStopClicked = RED;

    // Color of Label Text
    ColorLabelTextDefault = WHITE;
    ColorLabelEmphasize1 = MINT;
    ColorLabelEmphasize2 = ORANGE;
    ColorLabelEmphasize3 = ICEBLUE;
    ColorLabelError = RED;
    ColorLabelWarning = YELLOW;
    ColorLabelNormal = GREEN;

    // Color of Dialog Widget
    ColorDialogBackground = LIGHT_GRAY;
    ColorDialogTitleBar = BLACK;
    ColorDialogContetnstBackground = DARK_GRAY;

    // Color of Project Editor
    ColorProjectEditorNodeItemBackgound = DARK_GRAY;
    ColorNodeAssignVariable = PURPLE;
    ColorNodeMoveRobot = FORESTGREEN;
    ColorNodeDelay = MEGENTA;
    ColorNodeConditional = YELLOW;
    ColorNodeDigitalIO = ORANGE;

    ColorProjectEditorWidgetMenuBackground = BLACK;
    ColorProjectEditorMenuText = WHITE;
    ColorProjectEditorItemText = ORANGE;

    ColorAssignOperatorButton = QColor(0x80,0x64,0xa2);
}

SingletonColor::~SingletonColor() {

}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
