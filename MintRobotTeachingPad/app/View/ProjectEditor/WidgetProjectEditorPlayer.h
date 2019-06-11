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

#ifndef WIDGETPROJECTEDITORPLAYER_H
#define WIDGETPROJECTEDITORPLAYER_H

#include <QWidget>
#include <QList>
#include "app/view/util/WidgetRect.h"
#include "app/view/util/WidgetButton.h"
#include "app/view/util/WidgetLabel.h"
#include "app/view/util/WidgetSlider.h"

class WidgetProjectEditorPlayer : public QWidget
{
    Q_OBJECT
public:
    typedef enum player_state {
        STOP = 0,
        PLAYING = 1,
        PAUSE = 2,
    } PLAYER_STATE;

    explicit WidgetProjectEditorPlayer(QWidget *parent = nullptr);
    virtual ~WidgetProjectEditorPlayer() override ;

    PLAYER_STATE getState();
    void setState(PLAYER_STATE state);

    //______________________________________________________
    protected:
        virtual void resizeEvent(QResizeEvent * event) override;

    //______________________________________________________
    private:
        double __ratioMarginWidth = 3;
        double __ratioMarginHeight = 3;
        double __ratioSizeButton = 48;
        double __ratioWidthLabelIndex = 13;
        double __ratioWidthLabelValue = 30.5;
        double __ratioHeightLabel = 3;
        double __ratioWidthSlider = 44;
        double __ratioHeightSlider = 6;
        double __ratioWidthLabelSliderMinMax = 20;

        int __marginWidth;
        int __marginHeight;
        int __sizeButton;
        int __widthLabelIndex;
        int __widthLabelValue;
        int __heightLabel;
        int __widthSlider;
        int __heightSlider;
        int __widthSliderMinMax;

        WidgetRect* __pRectBackground;
        WidgetButton* __pButtonPlayPause;
        WidgetButton* __pButtonStopExit;
        WidgetLabel* __pLabelJoint;
        WidgetLabel* __pLabelTCP;
        QList<WidgetLabel*> __listJointIndex;
        QList<WidgetLabel*> __listJointValue;
        QList<WidgetLabel*> __listTCPIndex;
        QList<WidgetLabel*> __listTCPValue;

        PLAYER_STATE __state = STOP;

signals:
        void signalPlayProject();
        void signalPauseProject();
        void signalResumeProject();
        void signalStopProject();

public slots:
        void slotOnPlayPauseButton();
        void slotOnStopExitButton();
        void slotUpdateCurrentPosition(QVector<double> vecJoint, QVector<double> vecTCP);
};

#endif // WIDGETPROJECTEDITORPLAYER_H
