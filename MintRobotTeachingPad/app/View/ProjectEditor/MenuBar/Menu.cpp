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

#include "Menu.h"

//_______________________________________CONSTRUCTOR__________________________________//
Menu::Menu(QWidget *parent, int id) : MTPWidget(parent) {
    __ID = id;
    __pListItem = new QList<WidgetButton*>();

    __pRectBackground = new WidgetRect(this);
    __pRectBackground->setColor(SingletonColor::GetInstance().ColorProjectEditorWidgetMenuBackground);

    __pLabelName = new WidgetLabel(this);
}

Menu::~Menu() {

}

//_______________________________________PUBLIC_______________________________________//
void Menu::setMenuName(QString name) {
    __strName = name;
    __pLabelName->setText(__strName);
    __pLabelName->setTextHeightPixel(static_cast<int>(__textHeightRatio * height()));
    __pLabelName->setTextColor(SingletonColor::GetInstance().ColorProjectEditorMenuText);
}

void Menu::setMenuColor(QColor color) {
    __activeColor = color;
}

int Menu::getItemSize() {
    return __pListItem->size();
}

void Menu::expandItems() {
    WidgetButton* item;
    for (int i = 0; i < __pListItem->size(); i++) {
        item = __pListItem->at(i);
        item->setVisible(true);
    }
    __pRectBackground->setColor(__activeColor);
    __flagExpandStatus = true;
}

void Menu::collapseItems() {
    WidgetButton* item;
    for (int i = 0; i < __pListItem->size(); i++) {
        item = __pListItem->at(i);
        item->setVisible(false);
    }
    __pRectBackground->setColor(__deactiveColor);
    __flagExpandStatus = false;
}

void Menu::appendItem(WidgetButton* item) {
    item->setTextColor(SingletonColor::GetInstance().ColorProjectEditorItemText);
    item->setVisible(false);
    __pListItem->append(item);
}

void Menu::clearItemList() {
    WidgetButton* item;
    for (int i = 0; i < __pListItem->size(); i++) {
        item = __pListItem->at(i);
        item->disconnect();
        delete item;
    }
    __pListItem->clear();
}


//_______________________________________PROTECTED____________________________________//
void Menu::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);

    if (__flagExpandStatus) {
        if (__pListItem->size() > 0) {
            __sizeItemHeight = height() / (__pListItem->size() + 1);
        }
        else {
            __sizeItemHeight = height();
        }
    }
    else {
        __sizeItemHeight = height();
    }
    __marginWidth = static_cast<int>(width() * __ratioMarginWidth / 100);
    __marginHeight = static_cast<int>(height() * __ratioMarginHeight / 100);

    __pRectBackground->setGeometry(0, 0, width(), height());
    __pLabelName->setGeometry(__marginWidth, 0, width() - __marginWidth, __sizeItemHeight);
    WidgetButton* pItem;
    for (int i = 0; i < __pListItem->size(); i++) {
        pItem = __pListItem->at(i);
        pItem->setGeometry(0, __sizeItemHeight + __sizeItemHeight * i, width(), __sizeItemHeight);
    }
}

void Menu::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    if (__flagExpandStatus) {
        onCollapseItems(__ID);
        collapseItems();
    }
    else {
        onExpandItems(__ID);
        expandItems();
    }
    resizeEvent(nullptr);
    update();
}

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
void Menu::onClickBtnSlot(int id) {
    emit onClickItem(id);
}
