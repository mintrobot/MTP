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

#include "SingletonProjectEditorWarning.h"

SingletonProjectEditorWarning::SingletonProjectEditorWarning(QWidget *parent) : MTPWidget (parent) {

    QScreen *screen = QGuiApplication::primaryScreen();
    int width = static_cast<int>(screen->geometry().width() * 0.6);
    int height = static_cast<int>(screen->geometry().height() * 0.6);
    this->setGeometry((screen->geometry().width() - width) / 2, (screen->geometry().height() - height) / 2, width, height);

    __pRectTitle = new WidgetRect(this);
    __pRectTitle->setColor(SingletonColor::GetInstance().ColorDialogTitleBar);

    __pRectContents = new WidgetRect(this);
    __pRectContents->setColor(SingletonColor::GetInstance().ColorDialogContetnstBackground);

    __pLabelTitle = new WidgetLabel(this);
    __pLabelTitle->setTextColor(SingletonColor::GetInstance().ColorLabelError);
    __pLabelTitle->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelTitle->setText("WARNING");

    __pLabelContents = new WidgetLabel(this);
    __pLabelContents->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
    __pLabelContents->setAlign(WidgetLabel::ALIGN_CENTER);

    __pButtonClose = new WidgetButton(this);
    __pButtonClose->setButtonImage(SingletonImage::GetInstance().ID_CLOSE);
    __pButtonClose->setMargin(10);
    __pButtonClose->setColor(SingletonColor::GetInstance().getColorWithAlpha(SingletonColor::GetInstance().ColorDialogTitleBar, 0xff));
    __pButtonClose->setColorClicked(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);

    connect(__pButtonClose, SIGNAL(onClick(int)), this, SLOT(closeDialog()));

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setVisible(false);
}

SingletonProjectEditorWarning::~SingletonProjectEditorWarning() {

}


// Protected
void SingletonProjectEditorWarning::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);

    __heightTitleBar = static_cast<int>(height() * __ratioTitleHeight / 100);
    __pRectTitle->setGeometry(0, 0, width(), __heightTitleBar);
    __pRectContents->setGeometry(0, __heightTitleBar, width(), height() - __heightTitleBar);
    __pLabelTitle->setGeometry(0, 0, width(), __heightTitleBar);
    __pLabelContents->setGeometry(0, __heightTitleBar, width(), height() - __heightTitleBar);
    __pButtonClose->setGeometry(width() - __heightTitleBar, 0, __heightTitleBar, __heightTitleBar);

}

void SingletonProjectEditorWarning::warningEmptyProject() {
    __pLabelContents->setText("Project is empty");
    this->show();
}

void SingletonProjectEditorWarning::warningOnBrake() {
    __pLabelContents->setText("Brake is Activating");
    this->show();
}

void SingletonProjectEditorWarning::warningRobotIsOperating() {
    __pLabelContents->setText("Robot is operating");
    this->show();
}

void SingletonProjectEditorWarning::warningRobotNotReady() {
    __pLabelContents->setText("Robot is not ready");
    this->show();
}

void SingletonProjectEditorWarning::warningNotOperable() {
    QString contents = "Robot is not operable\n\n";
    contents += "Check the below status are correctly prepared\n\n\n";
    contents += "Robot : Operating\n\n";
    contents += "Servo : ON\n\n";
    contents += "Brake : OFF";
    __pLabelContents->setText(contents);
    this->show();
}

void SingletonProjectEditorWarning::warningSelfCollisionPredicted() {
    QString contents = "Self collosion is predicted\n\n";
    contents += "Check your motion is proper in terms of self collision";
    __pLabelContents->setText(contents);
    this->show();
}

void SingletonProjectEditorWarning::warningJointLimit() {
    QString contents = "Joint limit is detected\n\n";
    contents += "Check your motion is proper in terms of joint limitation";
    __pLabelContents->setText(contents);
    this->show();
}

void SingletonProjectEditorWarning::warningTrajectoryGenerateFailed() {
    QString contents = "Trajectory generation is failed\n\n";
    contents += "Check your motion is proper in terms of workspace";
    __pLabelContents->setText(contents);
    this->show();
}

void SingletonProjectEditorWarning::warningCollosionDetected() {
    QString contents = "Collision is detected\n\n";
    __pLabelContents->setText(contents);
    this->show();
}

// Slots
void SingletonProjectEditorWarning::closeDialog() {
    this->hide();
}
