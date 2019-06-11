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

#include "FileExplorerItem.h"

//_______________________________________CONSTRUCTOR__________________________________//
FileExplorerItem::FileExplorerItem(QWidget *parent, int id, QString filename) : QWidget(parent) {
    __ID = id;
    __strFilename = filename;

    __pRectBackground = new WidgetRect(this);
    __pRectBackground->setColor(SingletonColor::GetInstance().ColorButtonEmpashize2Clicked);
    __pRectBackground->setVisible(false);
    __pLabelImage = new WidgetLabel(this);
    __pLabelFileName = new WidgetLabel(this);
}

FileExplorerItem::~FileExplorerItem() {

}

//_______________________________________PUBLIC_______________________________________//
void FileExplorerItem::setClicked(bool clicked) {
    __pRectBackground->setVisible(clicked);
}

QString FileExplorerItem::getFileName() {
    return __strFilename;
}

//_______________________________________PROTECTED____________________________________//
void FileExplorerItem::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event)
    redraw();
}

void FileExplorerItem::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    emit onClick(__ID);
}

//_______________________________________PRIVATE______________________________________//
void FileExplorerItem::calculateCoordinateVariables() {
    __sizeWidth = width();
    __sizeHeight = height();

    __marginWidth = static_cast<int>(__sizeWidth * __ratioWidthMargin / 100);
    __marginHeight = static_cast<int>(__sizeHeight * __ratioHeightMargin / 100);
}

void FileExplorerItem::redraw() {
    calculateCoordinateVariables();
    __pRectBackground->setGeometry(0, 0, __sizeWidth, __sizeHeight);

    QString imgId = SingletonImage::GetInstance().ID_FILE;
    QPixmap pixmap = SingletonImage::GetInstance().getPixmap(SingletonImage::GetInstance().ID_FILE, __sizeHeight, __sizeHeight);
    __pLabelImage->setPixmap(pixmap);
    __pLabelImage->setGeometry(__marginWidth, 0, __sizeHeight, __sizeHeight);

    __pLabelFileName->setGeometry(__marginWidth*2 + __sizeHeight, 0, __sizeWidth - __sizeHeight, __sizeHeight - __marginHeight);
    __pLabelFileName->setText(__strFilename);
}
//_______________________________________SLOTS________________________________________//
