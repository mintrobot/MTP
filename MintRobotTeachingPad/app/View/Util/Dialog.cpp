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

#include "Dialog.h"
//_______________________________________CONSTRUCTOR__________________________________//
Dialog::Dialog(QWidget *parent, int widgetID) : MTPWidget(parent, widgetID) {
    // init background
    __pRectBackground = new WidgetRect(this);
    __pRectBackground->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorDialogBackground, 0xcc));

    __pRectContents = new WidgetRect(this);
    __pRectContents->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);

    // init title bar
    __pRectTitle = new WidgetRect(this);
    __pRectTitle->setColor(SingletonColor::GetInstance().ColorDialogTitleBar);
    __pLabelTitle = new WidgetLabel(this);

    // init dialog window buttons
    __pButtonOk = new WidgetButton(this, VIEW_ID_OK);
    __pButtonOk->setButtonImage(SingletonImage::GetInstance().ID_OK);
    __pButtonOk->setMargin(10);
    QColor c = SingletonColor::GetInstance().ColorDialogTitleBar;
    __pButtonOk->setColor(SingletonColor::GetInstance().getColorWithAlpha(c, 0xff));
    __pButtonOk->setColorClicked(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    __pButtonClose = new WidgetButton(this, VIEW_ID_CANCEL);
    __pButtonClose->setButtonImage(SingletonImage::GetInstance().ID_CLOSE);
    __pButtonClose->setMargin(10);
    c = SingletonColor::GetInstance().ColorDialogTitleBar;
    __pButtonClose->setColor(SingletonColor::GetInstance().getColorWithAlpha(c, 0xff));
    __pButtonClose->setColorClicked(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    // init connections
    connect(__pButtonOk, SIGNAL(onClick(int)), this, SLOT(closeDialog(int)));
    connect(__pButtonClose, SIGNAL(onClick(int)), this, SLOT(closeDialog(int)));
}

Dialog::~Dialog() {

}

//_______________________________________PUBLIC_______________________________________//
void Dialog::setSize(double ratioWidth, double ratioHeight) {
    __ratioWidth = ratioWidth;
    __ratioHeight = ratioHeight;
}

void Dialog::setTitle(QString titleName) {
    __titleName = titleName;
    __pLabelTitle->setText(__titleName);
}

QWidget* Dialog::getContentsWidget() {
    return static_cast<QWidget*>(__pRectContents);
}
//_______________________________________PROTECTED____________________________________//
void Dialog::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);
    _widthContentsBox = static_cast<int>(width() * __ratioWidth / 100);
    _heightContentsBox = static_cast<int>(height() * __ratioHeight / 100);
    _coordinateXContentsBox = static_cast<int>((width() - _widthContentsBox) / 2);
    _coordinateYContentsBox = static_cast<int>((height() - _heightContentsBox) / 2);
    __heightTitleBar = static_cast<int>(height() * __ratioTitleHeight / 100);

    __pRectBackground->setGeometry(0, 0, width(), height());
    __pRectContents->setGeometry(_coordinateXContentsBox, _coordinateYContentsBox, _widthContentsBox, _heightContentsBox);
    __pRectTitle->setGeometry(_coordinateXContentsBox, _coordinateYContentsBox - __heightTitleBar, _widthContentsBox, __heightTitleBar);
    __pLabelTitle->setGeometry(_coordinateXContentsBox + 10, _coordinateYContentsBox - __heightTitleBar, _widthContentsBox, __heightTitleBar);

    __pButtonClose->setGeometry(_coordinateXContentsBox + _widthContentsBox - __heightTitleBar,
                                _coordinateYContentsBox - __heightTitleBar,
                                __heightTitleBar,
                                __heightTitleBar);

    __pButtonOk->setGeometry(_coordinateXContentsBox + _widthContentsBox - __heightTitleBar*2,
                                _coordinateYContentsBox - __heightTitleBar,
                                __heightTitleBar,
                                __heightTitleBar);

    if (!_flagOkButton) {
        __pButtonOk->hide();
    }
}
//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void Dialog::closeDialog(int id) {
    if (id == VIEW_ID_OK) {
        emit onDialogClickOK(getWidgetID());
    }
    this->setVisible(false);
}
