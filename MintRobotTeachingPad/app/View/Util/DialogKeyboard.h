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

#ifndef SAVEPROJECTWIDGET_H
#define SAVEPROJECTWIDGET_H

#include "app/view/util/Dialog.h"
#include "app/view/util/WidgetKeyboard.h"

class DialogKeyboard : public Dialog
{
    Q_OBJECT
    public:
        explicit DialogKeyboard(QWidget *parent = nullptr);
        virtual ~DialogKeyboard() override;
        void initValue();
        void setText(QString text);
        QString getValue();

    protected:
        virtual void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:

        QString __strText = "";

        double __ratioMargin = 3;
        double __ratioHeightText = 8;
        int __widthMargin;
        int __heightMargin;
        int __heightText;

        WidgetLabel* __pLabelText;
        WidgetKeyboard* __pWidgetKeyboard;

        void initEditTextView();
        void initKeyboard();

        void __calculateCoordinateVariabels();
        void __redraw();

    //______________________________________________________
    signals:
        void onClick(QString name);
        void onClickCancel();
    //______________________________________________________
    private slots:
        void onClickOkBtn(int id);
        void onClickCancelBtn(int id);
        void changeValue(QString value);

};
//__________________________________________________________


#endif // SAVEPROJECTWIDGET_H
