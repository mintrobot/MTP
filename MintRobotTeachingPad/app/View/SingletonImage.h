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

#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

//__________________________________________________________
#include <QObject>
#include <QtGui>
#include <QString>
#include <QFontDatabase>

//__________________________________________________________
class SingletonImage : public QObject
{
    Q_OBJECT
    //______________________________________________________
    public:
        static SingletonImage &GetInstance() {
            static SingletonImage instance;
            return instance;
        }

        explicit SingletonImage(QObject *parent = nullptr);
        virtual ~SingletonImage() override;

        QString ID_Background = "bg_pattern3.jpg";
        QString ID_OK = "ok.png";
        QString ID_ADD = "add.png";
        QString ID_MINUS = "minus.png";
        QString ID_CLOSE = "close.png";
        QString ID_DELETE = "delete.png";
        QString ID_SET = "set.png";
        QString ID_EDIT = "edit.png";

        QString ID_ARROW_RIGHT = "arrow_right.png";
        QString ID_ARROW_UP = "arrow_up.png";
        QString ID_ARROW_DOWN = "arrow_down.png";

        QString ID_RETURN = "return.png";
        QString ID_PLAY = "play.png";
        QString ID_PAUSE = "pause.png";
        QString ID_SAVE = "save.png";

        QString ID_FILE = "file.png";
        QString ID_CONTROLLER1 = "controller1.png";
        QString ID_HOME_COMMAND = "home.png";
        QString ID_SETTING = "setting.png";
        QString ID_IO = "input_output.png";
        QString ID_SET_THIS_POSITION = "set_this_position.png";
        QString ID_GET_CURRENT_POSITION = "get_current_position";

        QString ID_TRANS_X_PLUS = "transXplus.png";
        QString ID_TRANS_X_MINUS = "transXminus.png";
        QString ID_TRANS_Y_PLUS = "transYplus.png";
        QString ID_TRANS_Y_MINUS = "transYminus.png";
        QString ID_TRANS_Z_PLUS = "transZplus.png";
        QString ID_TRANS_Z_MINUS = "transZminus.png";
        QString ID_ROT_X_PLUS = "rotXplus.png";
        QString ID_ROT_X_MINUS = "rotXminus.png";
        QString ID_ROT_Y_PLUS = "rotYplus.png";
        QString ID_ROT_Y_MINUS = "rotYminus.png";
        QString ID_ROT_Z_PLUS = "rotZplus.png";
        QString ID_ROT_Z_MINUS = "rotZminus.png";

        QPixmap getPixmap(QString imgId);
        QPixmap getPixmap(QString imgId, int width, int height);

    //______________________________________________________
    protected:
    //______________________________________________________
    private:
        QString FRIFIX = ":/resources/images/";

    //______________________________________________________
    signals:
    //______________________________________________________
    private slots:

};
//__________________________________________________________

#endif // IMAGEMANAGER_H
