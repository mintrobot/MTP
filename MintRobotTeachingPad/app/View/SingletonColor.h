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

#ifndef COLOR_H
#define COLOR_H

//__________________________________________________________
#include <QObject>
#include <QColor>

//__________________________________________________________
class SingletonColor : public QObject
{
    Q_OBJECT
//______________________________________________________
public:
    explicit SingletonColor(QObject *parent = nullptr);
    ~SingletonColor();

    static SingletonColor &GetInstance() {
        static SingletonColor instance;
        return instance;
    }

private:
    // Color Preset
    QColor WHITE;
    QColor BLACK;

    QColor LIGHT_GRAY;
    QColor MID_GRAY;
    QColor DARK_GRAY;

    QColor RED;
    QColor GREEN;
    QColor BLUE;
    QColor CYAN;
    QColor YELLOW;
    QColor MEGENTA;

    QColor DARKRED;
    QColor FORESTGREEN;
    QColor DARKBLUE;
    QColor ICEBLUE;
    QColor MINT;
    QColor PEACH;
    QColor ORANGE;
    QColor PURPLE;

public:
    // Colors of Butons
    QColor ColorButtonDefaultNormal;
    QColor ColorButtonDefaultClicked;

    QColor ColorButtonEmpashize1Normal;
    QColor ColorButtonEmpashize1Clicked;

    QColor ColorButtonEmpashize2Normal;
    QColor ColorButtonEmpashize2Clicked;

    QColor ColorButtonEmpashize3Normal;
    QColor ColorButtonEmpashize3Clicked;

    QColor ColorButtonEmergencyStop;
    QColor ColorButtonEmergencyStopClicked;

    // Color of Label Text
    QColor ColorLabelTextDefault;
    QColor ColorLabelEmphasize1;
    QColor ColorLabelEmphasize2;
    QColor ColorLabelEmphasize3;
    QColor ColorLabelError;
    QColor ColorLabelWarning;
    QColor ColorLabelNormal;

    // Color of Dialog Widget
    QColor ColorDialogBackground;
    QColor ColorDialogTitleBar;
    QColor ColorDialogContetnstBackground;

    // Color of Project Editor
    QColor ColorProjectEditorNodeItemBackgound;
    QColor ColorNodeAssignVariable;
    QColor ColorNodeMoveRobot;
    QColor ColorNodeDelay;
    QColor ColorNodeConditional;
    QColor ColorNodeDigitalIO;

    QColor ColorProjectEditorWidgetMenuBackground;
    QColor ColorProjectEditorMenuText;
    QColor ColorProjectEditorItemText;

    QColor ColorAssignOperatorButton;

    QColor getColorWithAlpha(QColor color, int alpha) {
        return QColor(color.red(), color.green(), color.blue(), alpha);
    }

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

#endif // COLOR_H
