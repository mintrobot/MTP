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

#ifndef VIEWSIZE_H
#define VIEWSIZE_H

//__________________________________________________________
#include <QObject>
#include <QtGui>
#include <QString>
#include <QFontDatabase>
//#include "app/debug/debug.h"

//__________________________________________________________
class ViewSize : public QObject
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit ViewSize(QObject *parent = nullptr);
        ~ViewSize();

        static ViewSize &GetInstance() {
            static ViewSize instance;
            return instance;
        }

        //===============================
        //서피스3 - 2160*1440
        //서피스4 - 2763*1824
        //lcd   - 1920*1080
        //mac   - 2560*1600
        //1920*1200-모듈
        //1280*800-뉴모
        //1024*768-진영
        //===============================
        int ROBOT_TYPE = 3;

        int VIEW_SIZE_DOTPERINCH;
        int VIEW_SIZE_CUR_DOTPERINCH;
        int VIEW_SIZE_MIN_WIDTH;
        int VIEW_SIZE_MIN_HEIGHT;

        int KEY_SIZE;
        int VIEW_UNIT;
        int MARGIN;

        int EDIT_TASKBAR_W;
        int EDIT_MENUBAR_W;
        int EDITVIEW_BUTTON_SIZE;
        int EDITVIEW_ARROW_SIZE;
        int EDITVIEW_NODE_WIDTH;

        double FONT_RATIO_0 = 0.1;
        double FONT_RATIO_1 = 0.15;
        double FONT_RATIO_2 = 0.2;
        double FONT_RATIO_3 = 0.25;

        void setSize(int screenW, int screenH,int dotPerInch);

    //______________________________________________________
    protected:
    //______________________________________________________
    private:
    //______________________________________________________
    signals:
    //______________________________________________________
    private slots:

};
//__________________________________________________________

#endif // VIEWSIZE_H
