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

#ifndef SELECTPROJECTWIDGET_H
#define SELECTPROJECTWIDGET_H

//__________________________________________________________
#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>

#include "app/view/SingletonImage.h"
#include "app/view/SingletonColor.h"
#include "app/view/stringid.h"
#include "app/view/viewid.h"
#include "app/view/viewsize.h"

#include "app/view/util/WidgetRect.h"
#include "app/view/util/WidgetButton.h"
#include "app/view/util/WidgetKeypad.h"


#include "Dialog.h"
#include "FileExplorerItem.h"

//#include "app/ui/dialog/selectprojectitemwidget.h"
//__________________________________________________________
class FileExplorer : public QWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit FileExplorer(QWidget *parent = nullptr);
        virtual ~FileExplorer() override;

        void setTitle(QString title);
        void setFileList(QList<QString>* list);

    //______________________________________________________
    protected:
        void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:
        int __selectItemIndex = 0;
        QList<FileExplorerItem*>* __pListFiles;


        int __sizeWidth;
        int __sizeHeight;
        WidgetLabel *__pLabelBackground;

        double __ratioMarginWidth = 1;
        double __ratioMarginHeight = 1;
        int __marginWidth;
        int __marginHeight;

        double __ratioTitleHeight = 6;
        int __heightTitle;

        double __ratioFileItemHeight = 6;
        int __heightFileItem;

        WidgetRect *__pRectTitleBarDecoration;
        WidgetRect *__pRectTitleBarMain;
        WidgetLabel *__pLabelTitle;
        QString __strTitle = "File Explorer";

        double __ratioButtonWidth = 12;
        int __sizeButtonWidth;
        double __ratioButtonHeight = 6;
        int __sizeButtonHeight;
        WidgetButton *__pButtonSelect;
        WidgetButton *__pButtonCancel;

        int __coordinateXList;
        int __coordinateYList;
        int __sizeListWidth;
        int __sizeListHeight;
        int __sizeContainerHeight;
        WidgetRect* __pRecFileList;
        QScrollArea* __pScrollAreaFileList;
        QWidget* __pWidgetContainer;

        void calculateCoordinateVariables();
        void redraw();

    //______________________________________________________
    signals:
        void onClick(int id);
        void onClickCancel();
        void onSelectItem(QString fileName);
    //______________________________________________________
    private slots:
        void closeDialog(int id);
        void selectListItem(int id);

};
//__________________________________________________________


#endif // SELECTPROJECTWIDGET_H
