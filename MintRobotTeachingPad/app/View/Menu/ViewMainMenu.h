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

// The widget class representing main memu

#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

//__________________________________________________________
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QList>
//#include "app/view/resource/image.h"
//#include "app/view/resource/color.h"
#include "app/view/stringid.h"
#include "app/view/viewid.h"
#include "app/view/viewsize.h"

//#include "app/view/util/rect.h"
#include "app/view/util/WidgetButton.h"
//#include "app/view/util/KeypadNumber.h"

#include "app/view/util/FileExplorer.h"
#include "app/view/robotconfig/DialogRobotConfiguration.h"
#include "app/view/util/DialogKeyboard.h"

#include "app/view/projecteditor/ViewProjectEditor.h"

//__________________________________________________________
class ViewMainMenu : public QWidget
{
    Q_OBJECT
    //______________________________________________________
    public:
        explicit ViewMainMenu(QWidget *parent = nullptr);
        virtual ~ViewMainMenu() override;

        ViewProjectEditor* pViewProjectEditor;
        DialogRobotConfiguration* pDialogRobotConfiguration;

        void init();
    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:
        QList<WidgetButton*> __listButton;
        WidgetLabel* __backGround;

        void __initMenuButton();

        void __redrawBackGround();
        void __redrawMenuButton();

    //______________________________________________________
    signals:
        // This signal is triggered from Button instances (mItem1-5)
        void onClick(int id);
    //______________________________________________________
    private slots:
        void slotSaveConfiguration();
        void onClickMenu(int id);

};
//__________________________________________________________

#endif // HOMEWIDGET_H
