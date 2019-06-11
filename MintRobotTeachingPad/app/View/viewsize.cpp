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

#include "viewsize.h"

//_______________________________________CONSTRUCTOR__________________________________//
ViewSize::ViewSize(QObject *parent) : QObject(parent) {
    ROBOT_TYPE = 3;

    VIEW_SIZE_DOTPERINCH = 80;
    VIEW_SIZE_CUR_DOTPERINCH = VIEW_SIZE_DOTPERINCH;
    KEY_SIZE = VIEW_SIZE_DOTPERINCH*0.8;
    VIEW_UNIT = KEY_SIZE;
    VIEW_SIZE_MIN_WIDTH = KEY_SIZE*15;
    VIEW_SIZE_MIN_HEIGHT = KEY_SIZE*10;

    MARGIN = 10;
    EDIT_TASKBAR_W = KEY_SIZE*1;
    EDIT_MENUBAR_W = KEY_SIZE*3;
    EDITVIEW_BUTTON_SIZE = KEY_SIZE;
    EDITVIEW_ARROW_SIZE = KEY_SIZE;
    EDITVIEW_NODE_WIDTH = KEY_SIZE*10;

    FONT_RATIO_0 = 0.15;
    FONT_RATIO_1 = 0.2;
    FONT_RATIO_2 = 0.25;
    FONT_RATIO_3 = 0.3;
}
ViewSize::~ViewSize() { }

//_______________________________________PUBLIC_______________________________________//
void ViewSize::setSize(int screenW, int screenH, int dotPerInch) {
    if (dotPerInch < VIEW_SIZE_DOTPERINCH) {
        dotPerInch = VIEW_SIZE_DOTPERINCH;
    }

    if (80 < dotPerInch) {
        dotPerInch = 80 + (dotPerInch - 80)*0.8;
    }

    VIEW_SIZE_CUR_DOTPERINCH = dotPerInch;

    KEY_SIZE = dotPerInch*0.8;
    VIEW_SIZE_MIN_WIDTH = KEY_SIZE*20;
    VIEW_SIZE_MIN_HEIGHT = KEY_SIZE*15;

    int tmpKeySizeW = KEY_SIZE;
    int tmpKeySizeH = KEY_SIZE;
    if (screenW < VIEW_SIZE_MIN_WIDTH) {
        VIEW_SIZE_MIN_WIDTH = screenW;
        tmpKeySizeW = screenW/20;
    }
    if (screenH < VIEW_SIZE_MIN_HEIGHT) {
        VIEW_SIZE_MIN_HEIGHT = screenH;
        tmpKeySizeH = screenH/15;
    }
    if (tmpKeySizeW < tmpKeySizeH) {
        KEY_SIZE = tmpKeySizeW;
    } else {
        KEY_SIZE = tmpKeySizeH;
    }

    VIEW_UNIT = KEY_SIZE;
    VIEW_SIZE_MIN_WIDTH = KEY_SIZE*20;
    VIEW_SIZE_MIN_HEIGHT = KEY_SIZE*15;
    EDIT_TASKBAR_W = KEY_SIZE*1;
    EDIT_MENUBAR_W = KEY_SIZE*4;
    EDITVIEW_BUTTON_SIZE = KEY_SIZE;
    EDITVIEW_ARROW_SIZE = KEY_SIZE;
    EDITVIEW_NODE_WIDTH = KEY_SIZE*10;
}

//_______________________________________PROTECTED____________________________________//

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
