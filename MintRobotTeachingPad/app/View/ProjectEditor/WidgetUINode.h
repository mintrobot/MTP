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

#ifndef NODE_H
#define NODE_H

#include <QList>
#include <QVBoxLayout>

#include "app/model/nodes/ModelNode.h"
#include "app/view/util/WidgetButton.h"

class WidgetUINode : public MTPWidget
{
    Q_OBJECT
    public:
        WidgetUINode(QWidget *parent = nullptr, int id = 0);
        virtual ~WidgetUINode() override;

        // Actual model data pointer
        ModelNode* pModelNode;

        // Tree variables
        int cal = 0;
        int row = 0;
        WidgetUINode* pUINodeParent;

        // Display functions
        void setOnRunning(bool flagOnRunning);
        void updateText();
        void setColor(QColor color);

        bool flagContainerTop = false;
        bool flagContainerBetween = false;
        bool flagContainerBottom = false;


    protected:
        virtual void resizeEvent(QResizeEvent * event) override;
        virtual void paintEvent(QPaintEvent *event) override;
        virtual void mousePressEvent(QMouseEvent *event) override;
        virtual void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        double __ratioMargin = 3;
        double __ratioWidthCommand = 16;
        double __ratioWidthArgument = 75;
        double __ratioTextHeight = 0.8;

        int __widthMargin;
        int __heightMargin;
        int __widthCommand;
        int __widthArgument;

        QColor __colorRect;

        WidgetLabel* __pLabelCommand;
        WidgetLabel* __plabelArguments;
        QString __strCommandText = "";
        QString __strArgumentText = "";
        QColor  __colorTextLabelCommand = SingletonColor::GetInstance().ColorLabelEmphasize2;
        QColor  __colorTextLabelArgument = SingletonColor::GetInstance().ColorLabelTextDefault;
        WidgetLabel::ALIGN __alignText = WidgetLabel::ALIGN_LEFT;

        QColor __colorBase = SingletonColor::GetInstance().ColorButtonDefaultNormal;
        QColor __colorNormal = SingletonColor::GetInstance().getColorWithAlpha(__colorBase, 0x06);
        QColor __colorSelected = SingletonColor::GetInstance().getColorWithAlpha(__colorBase, 0xff);
        QColor __colorError = SingletonColor::GetInstance().ColorLabelError;
        QColor __colorCurrent;

        bool __flagPressed = false;

    signals:
        void onClickUINode(int row, int cal);

    private slots:

};

#endif // NODE_H
