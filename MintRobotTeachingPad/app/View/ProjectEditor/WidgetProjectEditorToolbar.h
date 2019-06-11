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

#ifndef WIDGETPROJECTEDITORTOOLBAR_H
#define WIDGETPROJECTEDITORTOOLBAR_H

#include <QObject>
#include <QList>
#include "app/view/util/WidgetRect.h"
#include "app/view/util/WidgetButton.h"
#include "app/view/util/WidgetLabel.h"
#include "app/view/util/WidgetSlider.h"

#define PROJECT_EDITOR_MENUBAR_BUTTON_JOG           1
#define PROJECT_EDITOR_MENUBAR_BUTTON_DIO           2

#define PROJECT_EDITOR_MENUBAR_BUTTON_EXECUTE       10
#define PROJECT_EDITOR_MENUBAR_BUTTON_NORMAL        12
#define PROJECT_EDITOR_MENUBAR_BUTTON_EDIT          13
#define PROJECT_EDITOR_MENUBAR_BUTTON_DEL           14

#define PROJECT_EDITOR_MENUBAR_BUTTON_INDEXUP       20
#define PROJECT_EDITOR_MENUBAR_BUTTON_INDEX_DOWN    21

class WidgetProjectEditorToolbar : public MTPWidget
{
    Q_OBJECT

public:
    WidgetProjectEditorToolbar(QWidget *parent);
    virtual ~WidgetProjectEditorToolbar() override;

protected:
    virtual void resizeEvent(QResizeEvent * event) override;

private:
    // Members to calculate size
    double __ratioMargin = 0;
    double __ratioSizeUtilityButtons = 100;

    int __widthMargin;
    int __heightMargin;
    int __sizeUtilityButtons;

    // Widget Members
    WidgetRect* __pRectBackground;


    WidgetButton* __pButtonOpenJogPanel;
    WidgetButton* __pButtonOpenDIOPanel;

    WidgetButton* __pButtonExecute;
    WidgetButton* __pButtonEdit;
    WidgetButton* __pButtonDelete;
    int __currentClickMode = PROJECT_EDITOR_MENUBAR_BUTTON_NORMAL;

    WidgetButton* __pButtonIndexUp;
    WidgetButton* __pButtonIndexDown;

signals:
    void signalClickedJogButton();
    void signalClickedIOButton();

    void signalTriggerExecuteMode();
    void signalTirggerNormalMode();
    void signalTriggerDeleteMode();
    void signalTriggerEditMode();

    void signalIndexUp();
    void signalIndexDown();

public slots:
    void slotProcessButton(int ID);
};

#endif // WIDGETPROJECTEDITORTOOLBAR_H
