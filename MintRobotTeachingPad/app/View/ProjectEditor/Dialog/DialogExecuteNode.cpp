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

#include "DialogExecuteNode.h"

//--- Constructor
DialogExecuteNode::DialogExecuteNode(QWidget* parent) : Dialog(parent) {

    setTitle("Execute Node");
    setSize(30, 16);
}

DialogExecuteNode::~DialogExecuteNode() {

}

//--- Public



//--- Protected
void DialogExecuteNode::resizeEvent(QResizeEvent * event) {
    Dialog::resizeEvent(event);
    __widthMargin = static_cast<int>(_widthContentsBox * __ratioMargin / 100);
    __heightMargin = static_cast<int>(_heightContentsBox * __ratioMargin / 100);
    __widthLabelCommand = static_cast<int>(width() * __ratioWidthCommand / 100);
    __widthLabelArguments = static_cast<int>(width() * __ratioWidthArguments / 100);

    __pLabelCommand->setGeometry(__widthMargin, __heightMargin, __widthLabelCommand, height()/2);
    __pLabelArguments->setGeometry(__pLabelCommand->geometry().bottomRight().x() + __widthMargin, __heightMargin, __widthLabelArguments, height()/2);
}