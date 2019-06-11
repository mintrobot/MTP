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

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

//__________________________________________________________
#include <QObject>
#include <QtGui>
#include <QString>
#include <QFontDatabase>
#include <QLabel>

//__________________________________________________________
class SingletonFont : public QObject
{
    Q_OBJECT
    //______________________________________________________
    public:
        static SingletonFont &GetInstance() {
            static SingletonFont instance;
            return instance;
        }

        explicit SingletonFont(QObject *parent = nullptr);
        ~SingletonFont();

        bool mFontEnable = true;

        QFont getFontBold(int fontSize);
        QFont getFontLight(int fontSize);
    //______________________________________________________
    protected:
    //______________________________________________________
    private:
        QString FRIFIX = ":/resources/font/";
        QString BOLD = "OpenSans-Bold.ttf";
        QString LIGHT = "OpenSans-Regular.ttf";

        bool mInit = false;
        void initFont();
        int mFontMaxSize = 300;
        QList<QFont> *__listFontBold;
        QList<QFont> *__listFontLight;
    //______________________________________________________
    signals:
    //______________________________________________________
    private slots:

};

//__________________________________________________________

#endif // FONTMANAGER_H
