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

#include "SingletonFont.h"

//_______________________________________CONSTRUCTOR__________________________________//
SingletonFont::SingletonFont(QObject *parent) : QObject(parent) {

    __listFontBold = new QList<QFont>();
    for (int i=1; i<mFontMaxSize; i++) {
        int id = QFontDatabase::addApplicationFont(FRIFIX+BOLD);
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont font(family);
        font.setPixelSize(i);
        __listFontBold->append(font);
    }

    __listFontLight = new QList<QFont>();
    for (int i=1; i<mFontMaxSize; i++) {
        int id = QFontDatabase::addApplicationFont(FRIFIX+LIGHT);
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont font(family);
        font.setPixelSize(i);
        font.setStyleStrategy(QFont::PreferAntialias);
        __listFontLight->append(font);
    }
}

SingletonFont::~SingletonFont() {

}

//_______________________________________PUBLIC_______________________________________//
QFont SingletonFont::getFontBold(int fontSize) {
    if (fontSize < mFontMaxSize) {
        return __listFontBold->at(fontSize-1);
    } else {
        int id = QFontDatabase::addApplicationFont(FRIFIX+BOLD);
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont font(family);
        font.setStyleStrategy(QFont::PreferAntialias);
        font.setPixelSize(fontSize);
        return font;
    }
}

QFont SingletonFont::getFontLight(int fontSize) {
    if (fontSize < mFontMaxSize) {
        return __listFontLight->at(fontSize-1);
    } else {
        int id = QFontDatabase::addApplicationFont(FRIFIX+LIGHT);
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont font(family);
        font.setStyleStrategy(QFont::PreferAntialias);
        font.setPixelSize(fontSize);
        return font;
    }
}
//_______________________________________PROTECTED____________________________________//

//_______________________________________PRIVATE______________________________________//

//_______________________________________SLOTS________________________________________//
