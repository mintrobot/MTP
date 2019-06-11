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

#ifndef SELECTPROJECTITEMWIDGET_H
#define SELECTPROJECTITEMWIDGET_H

//__________________________________________________________
#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QLabel>

#include "app/view/SingletonImage.h"
#include "app/view/SingletonColor.h"
#include "app/view/stringid.h"
#include "app/view/viewid.h"
#include "app/view/viewsize.h"

#include "app/view/util/WidgetRect.h"
#include "app/view/util/WidgetButton.h"



//__________________________________________________________
class FileExplorerItem : public QWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit FileExplorerItem(QWidget *parent = nullptr, int id = 0, QString filename = "");
        virtual ~FileExplorerItem() override;

        void setClicked(bool click);
        void setHeight(int heightPixel);
        QString getFileName();

    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;
        virtual void mousePressEvent(QMouseEvent *event) override;
    //______________________________________________________
    private:
        int __ID = 0;
        QString __strFilename = "";

        int __sizeWidth;
        int __sizeHeight;

        double __ratioWidthMargin = 0.1;
        double __ratioHeightMargin = 0.1;
        int __marginWidth;
        int __marginHeight;

        WidgetRect *__pRectBackground;
        WidgetLabel* __pLabelImage;
        WidgetLabel* __pLabelFileName;

        void calculateCoordinateVariables();
        void redraw();
    //______________________________________________________
    signals:
        void onClick(int id);
    //______________________________________________________
    private slots:

};
//__________________________________________________________


#endif // SELECTPROJECTITEMWIDGET_H
