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

#include "FileExplorer.h"

//_______________________________________CONSTRUCTOR__________________________________//
FileExplorer::FileExplorer(QWidget *parent) : QWidget(parent) {
    __pListFiles = new QList<FileExplorerItem*>();

    // init background
    __pLabelBackground = new WidgetLabel(this);

    // init titlebar
    __pRectTitleBarDecoration = new WidgetRect(this);
    __pRectTitleBarMain = new WidgetRect(this);
    __pRectTitleBarDecoration->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Normal);
    __pRectTitleBarMain->setColor(SingletonColor::GetInstance().ColorDialogTitleBar);
    __pLabelTitle = new WidgetLabel(this);

    // init Buttons
    __pButtonSelect = new WidgetButton(this, VIEW_ID_OK);
    __pButtonSelect->setText("SELECT");
    __pButtonSelect->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonSelect->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorDialogContetnstBackground, 0xff));
    __pButtonSelect->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonEmpashize2Clicked, 0xff));

    __pButtonCancel = new WidgetButton(this, VIEW_ID_CANCEL);
    __pButtonCancel->setText("CANCEL");
    __pButtonCancel->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pButtonCancel->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorDialogContetnstBackground, 0xff));
    __pButtonCancel->setColorClicked(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorButtonEmpashize2Clicked, 0xff));

    // init file list
    __pRecFileList = new WidgetRect(this);
    __pRecFileList->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorDialogContetnstBackground, 0x15));
    __pWidgetContainer = new QWidget(this);
    __pScrollAreaFileList = new QScrollArea(this);
    __pScrollAreaFileList->setWidget(__pWidgetContainer);
    __pScrollAreaFileList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    __pScrollAreaFileList->setStyleSheet("background-color:transparent;");

    connect(__pButtonSelect, SIGNAL(onClick(int)), this, SLOT(closeDialog(int)));
    connect(__pButtonCancel, SIGNAL(onClick(int)), this, SLOT(closeDialog(int)));

}

FileExplorer::~FileExplorer() {

}

//_______________________________________PUBLIC_______________________________________//
void FileExplorer::setTitle(QString title) {
    __strTitle = title;
}

void FileExplorer::setFileList(QList<QString>* list) {
    FileExplorerItem* item;
    if (__pListFiles->size() > 0) {
        for (int i = 0; i < __pListFiles->size(); i++) {
            item = __pListFiles->at(i);
            item->disconnect();
            delete __pListFiles->at(i);
        }
        __pListFiles->clear();
    }

    for (int i = 0; i < list->size(); i++) {
        item = new FileExplorerItem(__pWidgetContainer, i, list->at(i));
        connect(item, SIGNAL(onClick(int)), this, SLOT(selectListItem(int)));
        __pListFiles->append(item);
    }
}

//_______________________________________PROTECTED____________________________________//
void FileExplorer::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event)
    redraw();
}

void FileExplorer::calculateCoordinateVariables() {
    __sizeWidth = width();
    __sizeHeight = height();

    __marginWidth = static_cast<int>(__sizeWidth * __ratioMarginWidth / 100);
    __marginHeight = static_cast<int>(__sizeHeight * __ratioMarginHeight / 100);

    __heightTitle = static_cast<int>(__sizeHeight * __ratioTitleHeight / 100);
    __heightFileItem = static_cast<int>(__sizeHeight * __ratioFileItemHeight / 100);

    __coordinateXList = __marginWidth;
    __coordinateYList = __heightTitle + __marginHeight;
    __sizeListWidth = __sizeWidth - __marginWidth*2;
    __sizeListHeight = __sizeHeight - __heightTitle * 4 - __marginHeight * 2;

    __sizeContainerHeight = __heightFileItem * (__pListFiles->size() + 1);

    __sizeButtonWidth = static_cast<int>(__sizeWidth * __ratioButtonWidth / 100);
    __sizeButtonHeight = static_cast<int>(__sizeHeight * __ratioButtonHeight / 100);
}

void FileExplorer::redraw() {
    calculateCoordinateVariables();

    QPixmap pixmap = SingletonImage::GetInstance().getPixmap(SingletonImage::GetInstance().ID_Background, width(), height());
    __pLabelBackground->setPixmap(pixmap);
    __pLabelBackground->setGeometry(0, 0, __sizeWidth, __sizeHeight);

    __pRectTitleBarDecoration->setGeometry(0, 0, 15, __heightTitle);
    __pRectTitleBarMain->setGeometry(15, 0, __sizeWidth - 15, __heightTitle);
    __pLabelTitle->setGeometry(15 + __marginWidth, 0, __sizeWidth - 15 - __marginWidth, __heightTitle);
    __pLabelTitle->setText(__strTitle);

    __pRecFileList->setGeometry(__coordinateXList, __coordinateYList, __sizeListWidth, __sizeListHeight);
    __pScrollAreaFileList->setGeometry(__coordinateXList, __coordinateYList, __sizeListWidth, __sizeListHeight);

    __pWidgetContainer->setGeometry(__coordinateXList, __coordinateYList, __sizeListWidth - __marginWidth * 2, __sizeContainerHeight);

    FileExplorerItem* label;
    for (int i=0; i <__pListFiles->size(); i++) {
        label = __pListFiles->at(i);
        label->setGeometry(__marginWidth,
                           __heightFileItem * i + __marginHeight,
                           __sizeListWidth,
                           __heightFileItem);
    }

    __pButtonSelect->setGeometry(__sizeWidth - __sizeButtonWidth * 2 - __marginWidth * 2,
                                 __coordinateYList + __sizeListHeight + __marginHeight,
                                 __sizeButtonWidth,
                                 __sizeButtonHeight);

    __pButtonCancel->setGeometry(__sizeWidth - __sizeButtonWidth - __marginWidth,
                                 __coordinateYList + __sizeListHeight + __marginHeight,
                                 __sizeButtonWidth,
                                 __sizeButtonHeight);
}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void FileExplorer::closeDialog(int id) {
    if (VIEW_ID_OK == id) {
        FileExplorerItem* item = __pListFiles->at(__selectItemIndex);
        if (__selectItemIndex < __pListFiles->size()) {
            item = __pListFiles->at(__selectItemIndex);
            emit onSelectItem(item->getFileName());
        }
    }
    this->setVisible(false);
}


void FileExplorer::selectListItem(int id) {
    FileExplorerItem* item;
    if (__selectItemIndex < __pListFiles->size()) {
        item = __pListFiles->at(__selectItemIndex);
        item->setClicked(false);
    }
    item = __pListFiles->at(id);
    item->setClicked(true);
    __selectItemIndex = id;
}
