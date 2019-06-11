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

#include "ViewProjectEditor.h"

//_______________________________________CONSTRUCTOR__________________________________//
ViewProjectEditor::ViewProjectEditor(QWidget *parent) : MTPWidget(parent) {

    __pLabelBackground = new WidgetLabel(this);

    // Basic Widgets
    __pWidgetProjectEditorMenu = new WidgetProjectEditorMenu(this);
    __pWidgetProjectEditorNodeView = new WidgetProjectEditorNodeView(this);
    __pWidgetProjectEditorToolbar = new WidgetProjectEditorToolbar(this);
    __pWidgetProjectEditorPlayer = new WidgetProjectEditorPlayer(this);
    __pWidgetProjectEditorPlayer->setVisible(false);

    __pButtonStop = new WidgetButton(this);
    __pButtonStop->setText("STOP ROBOT");
    __pButtonStop->setColor(SingletonColor::GetInstance().ColorButtonEmergencyStop);
    __pButtonStop->setColorClicked(SingletonColor::GetInstance().ColorButtonEmergencyStopClicked);
    __pButtonStop->setRoundRatio(0.1);

    __pButtonServoOnOff = new WidgetButton(this);
    __pButtonServoOnOff->setText("SERVO ON");
    __pButtonServoOnOff->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Normal);
    __pButtonServoOnOff->setColorClicked(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);
    __pButtonServoOnOff->setRoundRatio(0.1);

    __pButtonBrakeOnOff = new WidgetButton(this);
    __pButtonBrakeOnOff->setText("BRAKE OFF");
    __pButtonBrakeOnOff->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);
    __pButtonBrakeOnOff->setColorClicked(SingletonColor::GetInstance().ColorButtonDefaultClicked);
    __pButtonBrakeOnOff->setRoundRatio(0.1);


    __pLabelRobotStatus = new WidgetLabel(this);
    __pLabelRobotStatus->setText("Robot Status");
    __pLabelRobotStatus->setTextHeightRatio(0.8);
    __pLabelRobotStatus->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);

    __pLabelRobotStatusValue = new WidgetLabel(this);
    __pLabelRobotStatusValue->setText("Not Ready");
    __pLabelRobotStatusValue->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelRobotStatusValue->setTextHeightRatio(0.8);
    __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelError);

    __pLabelServoStatus = new WidgetLabel(this);
    __pLabelServoStatus->setText("Servo Status");
    __pLabelServoStatus->setTextHeightRatio(0.8);
    __pLabelServoStatus->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);

    __pLabelServoStatusValue = new WidgetLabel(this);
    __pLabelServoStatusValue->setText("Off");
    __pLabelServoStatusValue->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelServoStatusValue->setTextHeightRatio(0.8);
    __pLabelServoStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelError);

    __pLabelBrakeStatus = new WidgetLabel(this);
    __pLabelBrakeStatus->setText("Brake Status");
    __pLabelBrakeStatus->setTextHeightRatio(0.8);
    __pLabelBrakeStatus->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);

    __pLabelBrakeStatusValue = new WidgetLabel(this);
    __pLabelBrakeStatusValue->setText("On");
    __pLabelBrakeStatusValue->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelBrakeStatusValue->setTextHeightRatio(0.8);
    __pLabelBrakeStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelNormal);

    __pLabelConnectionStatus = new WidgetLabel(this);
    __pLabelConnectionStatus->setText("Connection");
    __pLabelConnectionStatus->setTextHeightRatio(0.8);
    __pLabelConnectionStatus->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);

    __pLabelConnectionStatusValue = new WidgetLabel(this);
    __pLabelConnectionStatusValue->setText("Disconnected");
    __pLabelConnectionStatusValue->setTextHeightRatio(0.8);
    __pLabelConnectionStatusValue->setAlign(WidgetLabel::ALIGN_CENTER);
    __pLabelConnectionStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelError);


    // Dialogs for node setting
    __pDialogAssignVariable = new DialogNodeAssignVariable(this);
    __pDialogAssignVariable->setVisible(false);

    __pDialogMoveRobot = new DialogNodeMoveRobot(this);
    __pDialogMoveRobot->setVisible(false);

    __pDialogNodeCondition = new DialogNodeCondition(this);
    __pDialogNodeCondition->setVisible(false);

    __pDialogNodeDelay = new DialogNodeDelay(this);
    __pDialogNodeDelay->setVisible(false);

    __pDialogNodeDigitalInOut = new DialogNodeDigitalInOut(this);
    __pDialogNodeDigitalInOut->setVisible(false);


    // Dialogs for panel (jog and digital IO)
    __pDialogJogPanel = new DialogJogPanel(this);
    __pDialogJogPanel->setVisible(false);

    __pDialogIOPanel = new DialogIOPanel(this);
    __pDialogIOPanel->setVisible(false);


    //--- Signal settings
    // Save Load Execute
    connect(__pWidgetProjectEditorMenu, SIGNAL(signalClickSaveProject()), this, SLOT(slotSaveProject()));
    connect(__pWidgetProjectEditorMenu, SIGNAL(signalClickLoadProject()), this, SLOT(slotLoadProject()));
    connect(__pWidgetProjectEditorMenu, SIGNAL(signalClickPlayProject()), this, SLOT(slotOpenProjectPlayer()));

    // Open dialogs for nodes
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeAssignVariable()), this, SLOT(slotOpenDialogAssignVariableNew()));
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeMoveJoint()), this, SLOT(slotOpenDialogMoveJoint()));
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeMoveTCP()), this, SLOT(slotOpenDialogMoveTCP()));
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeIf(ModelNodeConditional::CONDITIONALTYPE)), this, SLOT(slotOpenDialogCondition(ModelNodeConditional::CONDITIONALTYPE)));
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeElseIf(ModelNodeConditional::CONDITIONALTYPE)), this, SLOT(slotOpenDialogCondition(ModelNodeConditional::CONDITIONALTYPE)));
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeElse(ModelNodeConditional::CONDITIONALTYPE)), this, SLOT(slotOpenDialogCondition(ModelNodeConditional::CONDITIONALTYPE)));
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeLoop(ModelNodeConditional::CONDITIONALTYPE)), this, SLOT(slotOpenDialogCondition(ModelNodeConditional::CONDITIONALTYPE)));
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeDelay()), this, SLOT(slotOpenDialogDelay()));
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeSetDigitalOut(ModelNodeDigitalIO::IOTYPE)), this, SLOT(slotOpenDigitalInOutNode(ModelNodeDigitalIO::IOTYPE)));
    connect(__pWidgetProjectEditorMenu, SIGNAL(onClickNodeWaitDigitalIn(ModelNodeDigitalIO::IOTYPE)), this, SLOT(slotOpenDigitalInOutNode(ModelNodeDigitalIO::IOTYPE)));

    // Applied adjusted information of nodes
    connect(__pDialogAssignVariable, SIGNAL(onDialogClickOK(int)), this, SLOT(slotProcessAppliedNodeInformation(int)));
    connect(__pDialogMoveRobot, SIGNAL(onDialogClickOK(int)), this, SLOT(slotProcessAppliedNodeInformation(int)));
    connect(__pDialogNodeCondition, SIGNAL(onDialogClickOK(int)), this, SLOT(slotProcessAppliedNodeInformation(int)));
    connect(__pDialogNodeDelay, SIGNAL(onDialogClickOK(int)), this, SLOT(slotProcessAppliedNodeInformation(int)));
    connect(__pDialogNodeDigitalInOut, SIGNAL(onDialogClickOK(int)), this, SLOT(slotProcessAppliedNodeInformation(int)));

    // Toolbar functions
    connect(__pWidgetProjectEditorToolbar, SIGNAL(signalClickedJogButton()), this, SLOT(slotOpenJogPanel()));
    connect(__pWidgetProjectEditorToolbar, SIGNAL(signalClickedIOButton()), this, SLOT(slotOpenIOPanel()));
    connect(__pWidgetProjectEditorToolbar, SIGNAL(signalTirggerNormalMode()), __pWidgetProjectEditorNodeView, SLOT(slotSetNormalMode()));
    connect(__pWidgetProjectEditorToolbar, SIGNAL(signalTriggerExecuteMode()), __pWidgetProjectEditorNodeView, SLOT(slotSetExecuteMode()));
    connect(__pWidgetProjectEditorToolbar, SIGNAL(signalTriggerEditMode()), __pWidgetProjectEditorNodeView, SLOT(slotSetEditMode()));
    connect(__pWidgetProjectEditorToolbar, SIGNAL(signalTriggerDeleteMode()), __pWidgetProjectEditorNodeView, SLOT(slotSetDeleteMode()));
    connect(__pWidgetProjectEditorToolbar, SIGNAL(signalIndexUp()), __pWidgetProjectEditorNodeView, SLOT(slotIndexUp()));
    connect(__pWidgetProjectEditorToolbar, SIGNAL(signalIndexDown()), __pWidgetProjectEditorNodeView, SLOT(slotIndexDown()));

    // Project Player
    connect(__pWidgetProjectEditorPlayer, SIGNAL(signalPlayProject()), this, SLOT(slotPlayProject()));
    connect(__pWidgetProjectEditorPlayer, SIGNAL(signalPauseProject()), this, SLOT(slotPauseProject()));
    connect(__pWidgetProjectEditorPlayer, SIGNAL(signalResumeProject()), this, SLOT(slotResumeProject()));
    connect(__pWidgetProjectEditorPlayer, SIGNAL(signalStopProject()), this, SLOT(slotStopProject()));

    // Node Viewer
    connect(__pWidgetProjectEditorNodeView, SIGNAL(signalEditNode(QUuid)), this, SLOT(slotProcessEditNode(QUuid)));

    // Updated status
    connect(SingletonInterfaceManager::GetInstance().getInterfaceRobot(),
            SIGNAL(signalUpdateConnectionStatus(bool)),
            this,
            SLOT(slotUpdateConnectionStatus(bool)));

    connect(SingletonInterfaceManager::GetInstance().getInterfaceRobot(),
            SIGNAL(signalUpdatedPos(const QVector<double>&, const QVector<double>&)),
            __pDialogJogPanel,
            SIGNAL(signalUpdatedPos(const QVector<double>&, const QVector<double>&)));

    connect(SingletonInterfaceManager::GetInstance().getInterfaceRobot(),
            SIGNAL(signalUpdatedPos(const QVector<double>&, const QVector<double>&)),
            __pWidgetProjectEditorPlayer,
            SLOT(slotUpdateCurrentPosition(const QVector<double>&, const QVector<double>&)));

    connect(SingletonInterfaceManager::GetInstance().getInterfaceRobot(),
            SIGNAL(signalUpdatedIO(const QVector<bool>&, const QVector<bool>&)),
            __pDialogIOPanel,
            SLOT(slotUpdatedIO(const QVector<bool>&, const QVector<bool>&)));

    connect(SingletonInterfaceManager::GetInstance().getInterfaceRobot(),
            SIGNAL(signalUpdateStatus(InterfaceRobot::ROBOT_STATUS, InterfaceRobot::CONTROLLER_STATUS, InterfaceRobot::ERROR_STATUS)),
            this,
            SLOT(slotUpdateStatus(InterfaceRobot::ROBOT_STATUS, InterfaceRobot::CONTROLLER_STATUS, InterfaceRobot::ERROR_STATUS)));

    // Emergency Stop
    connect(__pButtonStop, SIGNAL(onClick(int)), this, SLOT(slotEmergencyStop()));

    // Servo, Brake
    connect(__pButtonServoOnOff, SIGNAL(onClick(int)), this, SLOT(slotToggleServoOnOff()));
    connect(__pButtonBrakeOnOff, SIGNAL(onClick(int)), this, SLOT(slotToggleBrakeOnOff()));
    __pModelProject = new ModelProject();
}

ViewProjectEditor::~ViewProjectEditor() {

}

//_______________________________________PUBLIC_______________________________________//


//_______________________________________PROTECTED____________________________________//
void ViewProjectEditor::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event);

    __widthNodeView = static_cast<int>(width() * __ratioNodeView / 100);
    __widthToolbar = static_cast<int>(width() * __ratioToolbar / 100);
    __widthMenu = static_cast<int>(width() * __ratioMenu / 100);

    QPixmap pixmap = SingletonImage::GetInstance().getPixmap(SingletonImage::GetInstance().ID_Background, width(), height());
    __pLabelBackground->setPixmap(pixmap);
    __pLabelBackground->setGeometry(0, 0, width() - __widthMenu, height());

    __pWidgetProjectEditorNodeView->setGeometry(0, 0, __widthNodeView, height());
    __pWidgetProjectEditorToolbar->setGeometry(__widthNodeView, 0, __widthToolbar, height());
    __pWidgetProjectEditorMenu->setGeometry(__widthNodeView + __widthToolbar, 0, __widthMenu, static_cast<int>(height()));
    __pWidgetProjectEditorPlayer->setGeometry(__widthNodeView + __widthToolbar, 0, __widthMenu, static_cast<int>(height()));

    __pButtonStop->setGeometry(__widthNodeView + __widthToolbar, static_cast<int>(height() * 0.6), __widthMenu, static_cast<int>(height() * 0.06));
    __pButtonServoOnOff->setGeometry(__widthNodeView + __widthToolbar, __pButtonStop->geometry().bottomLeft().y(), __widthMenu, __pButtonStop->geometry().height());
    __pButtonBrakeOnOff->setGeometry(__widthNodeView + __widthToolbar, __pButtonServoOnOff->geometry().bottomLeft().y(), __widthMenu, __pButtonStop->geometry().height());


    __pLabelRobotStatus->setGeometry(__widthNodeView + __widthToolbar, __pButtonBrakeOnOff->geometry().bottomLeft().y(), __widthMenu/2, static_cast<int>(height() * 0.06));
    __pLabelRobotStatusValue->setGeometry(__widthNodeView + __widthToolbar + __widthMenu/2, __pLabelRobotStatus->geometry().top(), __widthMenu/2, static_cast<int>(height() * 0.06));
    __pLabelServoStatus->setGeometry(__widthNodeView + __widthToolbar, __pLabelRobotStatus->geometry().bottomLeft().y(), __widthMenu/2, static_cast<int>(height() * 0.06));
    __pLabelServoStatusValue->setGeometry(__widthNodeView + __widthToolbar + __widthMenu/2, __pLabelServoStatus->geometry().top(), __widthMenu/2, static_cast<int>(height() * 0.06));
    __pLabelBrakeStatus->setGeometry(__widthNodeView + __widthToolbar, __pLabelServoStatus->geometry().bottomLeft().y(), __widthMenu/2, static_cast<int>(height() * 0.06));
    __pLabelBrakeStatusValue->setGeometry(__widthNodeView + __widthToolbar + __widthMenu/2, __pLabelBrakeStatus->geometry().top(), __widthMenu/2, static_cast<int>(height() * 0.06));
    __pLabelConnectionStatus->setGeometry(__widthNodeView + __widthToolbar, __pLabelBrakeStatus->geometry().bottomLeft().y(), __widthMenu/2, static_cast<int>(height() * 0.06));
    __pLabelConnectionStatusValue->setGeometry(__widthNodeView + __widthToolbar + __widthMenu/2, __pLabelConnectionStatus->geometry().top(), __widthMenu/2, static_cast<int>(height() * 0.06));


    __pDialogAssignVariable->setGeometry(0, 0, width(), height());
    __pDialogMoveRobot->setGeometry(0, 0, width(), height());

    __pDialogNodeCondition->setGeometry(0, 0, width(), height());
    __pDialogNodeDelay->setGeometry(0, 0, width(), height());

    __pDialogNodeDigitalInOut->setGeometry(0, 0, width(), height());

    __pDialogJogPanel->setGeometry(0, 0, width(), height());
    __pDialogIOPanel->setGeometry(0, 0, width(), height());
}

//_______________________________________PRIVATE______________________________________//
WidgetUINode* ViewProjectEditor::__findUINodeFromHash(QUuid nodeID) {
    QHash<QUuid, WidgetUINode*>::const_iterator i = __pWidgetProjectEditorNodeView->hashUINode().find(nodeID);
    if (i != __pWidgetProjectEditorNodeView->hashUINode().end()) {
        return i.value();
    }
    else {
        return nullptr;
    }
}

bool ViewProjectEditor::__isOperable() {
    if (__flagRobotReadyStatus && __flagConnectionStatus && __flagServoStatus && !__flagBrakeStatus) {
        return true;
    }
    else {
        return false;
    }
}

void ViewProjectEditor::__updateRobotStatus(InterfaceRobot::ROBOT_STATUS robotStatus) {
    switch(robotStatus) {
    case InterfaceRobot::ROBOT_STATUS_NOT_READY:
        __pLabelRobotStatusValue->setText("Not Ready");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelError);
        __flagRobotReadyStatus = false;
        break;

    case InterfaceRobot::ROBOT_STATUS_PREPARING:
        __pLabelRobotStatusValue->setText("Preparing");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelWarning);
        __flagRobotReadyStatus = false;
        break;

    case InterfaceRobot::ROBOT_STATUS_READY:
        __pLabelRobotStatusValue->setText("Ready to operate");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelTextDefault);
        __flagRobotReadyStatus = false;
        break;

    case InterfaceRobot::ROBOT_STATUS_OPEARTING:
        __pLabelRobotStatusValue->setText("Operating");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelNormal);
        __flagRobotReadyStatus = true;
        break;
    }
}

void ViewProjectEditor::__updateControllerStatus(InterfaceRobot::CONTROLLER_STATUS controllerStatus) {

    switch(controllerStatus) {
    case InterfaceRobot::CONTROLLER_SERVO_ON_BRAKE_OFF:
        __updateServoStatus(true);
        __updateBrakeStatus(false);
        break;

    case InterfaceRobot::CONTROLLER_SERVO_OFF_BRAKE_ON:
        __updateServoStatus(false);
        __updateBrakeStatus(true);
        break;

    case InterfaceRobot::CONTROLLER_SERVO_ON_BRAKE_ON:
        __updateServoStatus(true);
        __updateBrakeStatus(true);
        break;

    case InterfaceRobot::CONTROLLER_SERVO_OFF_BRAKE_OFF:
        __updateServoStatus(false);
        __updateBrakeStatus(false);
        break;
    }
}

void ViewProjectEditor::__updateErrorStatus(InterfaceRobot::ERROR_STATUS errorStatus) {

    switch(errorStatus) {
    case InterfaceRobot::ERROR_STATUS_NO_ERROR:
        __pLabelRobotStatusValue->setText("No error");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelWarning);
        break;

    case InterfaceRobot::ERROR_STATUS_SELF_COLLISION_WARNING:
        __pLabelRobotStatusValue->setText("Collosion Predicted");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelWarning);
        __stopRobot();
        __pauseProject();
        SingletonProjectEditorWarning::GetInstance().warningSelfCollisionPredicted();
        break;

    case InterfaceRobot::ERROR_STATUS_JOINT_LIMIT_ERROR:
        __pLabelRobotStatusValue->setText("Joint Limit");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelError);
        __stopRobot();
        __pauseProject();
        SingletonProjectEditorWarning::GetInstance().warningJointLimit();
        break;

    case InterfaceRobot::ERROR_STATUS_TRAJECTORY_FAILED_ERROR:
        __pLabelRobotStatusValue->setText("Trajectory Error");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelError);
        __stopRobot();
        __pauseProject();
        SingletonProjectEditorWarning::GetInstance().warningTrajectoryGenerateFailed();
        break;

    case InterfaceRobot::ERROR_STATUS_COLLISION_DETECTION_ERROR:
        __pLabelRobotStatusValue->setText("Collision Detected");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelError);
        __stopRobot();
        __pauseProject();
        SingletonProjectEditorWarning::GetInstance().warningCollosionDetected();
        break;
    }
}

void ViewProjectEditor::__updateConnectionStatus(bool flagStatus) {
    if (flagStatus) {
        __pLabelConnectionStatusValue->setText("Connected");
        __pLabelConnectionStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelNormal);
        __flagConnectionStatus = true;
    }
    else {
        __pLabelRobotStatusValue->setText("Not Ready");
        __pLabelRobotStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelWarning);
        __pLabelConnectionStatusValue->setText("Disonnected");
        __pLabelConnectionStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelError);
        __flagConnectionStatus = false;
    }
}

void ViewProjectEditor::__updateServoStatus(bool flagStatus) {
    if (flagStatus) {
        __pLabelServoStatusValue->setText("ON");
        __pLabelServoStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelNormal);
        __pButtonServoOnOff->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Normal);
        __flagServoStatus = true;
    }
    else {
        __pLabelServoStatusValue->setText("OFF");
        __pLabelServoStatusValue->setTextColor(SingletonColor::GetInstance().ColorLabelError);
        __pButtonServoOnOff->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);
        __flagServoStatus = false;
    }
}

void ViewProjectEditor::__updateBrakeStatus(bool flagStatus) {
    if (flagStatus) {
        __pLabelBrakeStatus->setText("ON");
        __pLabelBrakeStatus->setTextColor(SingletonColor::GetInstance().ColorLabelNormal);
        __pButtonBrakeOnOff->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Normal);
        __flagBrakeStatus = true;
    }
    else {
        __pLabelBrakeStatus->setText("OFF");
        __pLabelBrakeStatus->setTextColor(SingletonColor::GetInstance().ColorLabelError);
        __pButtonBrakeOnOff->setColor(SingletonColor::GetInstance().ColorButtonEmpashize1Clicked);
        __flagBrakeStatus = false;
    }
}

void ViewProjectEditor::__stopRobot() {
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->stopRobot();
}

void ViewProjectEditor::__setServoStatus(bool flagStatus) {
    if (!__flagRobotReadyStatus) {
        SingletonProjectEditorWarning::GetInstance().warningRobotNotReady();
        return;
    }
    if (__flagBrakeStatus) {
        SingletonProjectEditorWarning::GetInstance().warningOnBrake();
        return;
    }
    if (__pWidgetProjectEditorPlayer->getState() == WidgetProjectEditorPlayer::PLAYING) {
        SingletonProjectEditorWarning::GetInstance().warningRobotIsOperating();
        return;
    }
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->setServoActiveStatus(flagStatus);
}

void ViewProjectEditor::__setBrakeStatus(bool flagStatus) {
    if (!__flagRobotReadyStatus) {
        SingletonProjectEditorWarning::GetInstance().warningRobotNotReady();
        return;
    }
    if (__pWidgetProjectEditorPlayer->getState() == WidgetProjectEditorPlayer::PLAYING) {
        SingletonProjectEditorWarning::GetInstance().warningOnBrake();
        return;
    }
    SingletonInterfaceManager::GetInstance().getInterfaceRobot()->setBrakeActiveStatus(flagStatus);
}

void ViewProjectEditor::__playProject() {
    if (!__isOperable()) {
        SingletonProjectEditorWarning::GetInstance().warningNotOperable();
        return;
    }

    __pModelProject = new ModelProject();
    if (__pWidgetProjectEditorNodeView->exportToProject(__pModelProject) == false) {
        SingletonProjectEditorWarning::GetInstance().warningEmptyProject();
        return;
    }
    else {
        SingletonRuntimeProject::GetInstance().setNotifier(reinterpret_cast<InterfaceNodeStatusNotifier*>(this));
        SingletonRuntimeProject::GetInstance().setProjectModel(__pModelProject);
        SingletonRuntimeProject::GetInstance().playProject();
        __pWidgetProjectEditorPlayer->setState(WidgetProjectEditorPlayer::PLAYING);
    }
}

void ViewProjectEditor::__pauseProject() {
    SingletonRuntimeProject::GetInstance().pauseProject();
    __pWidgetProjectEditorPlayer->setState(WidgetProjectEditorPlayer::PAUSE);

}

void ViewProjectEditor::__resumeProject() {
    SingletonRuntimeProject::GetInstance().resumeProject();
    __pWidgetProjectEditorPlayer->setState(WidgetProjectEditorPlayer::PLAYING);

}

void ViewProjectEditor::__stopProject() {
    SingletonRuntimeProject::GetInstance().stopProject();
    __pWidgetProjectEditorPlayer->setState(WidgetProjectEditorPlayer::STOP);

}

void ViewProjectEditor::__saveProject() {
    if (__pModelProject != nullptr) {
        delete __pModelProject;
        __pModelProject = nullptr;
    }
    __pModelProject = new ModelProject;
    __pWidgetProjectEditorNodeView->exportToProject(__pModelProject);
    if (__pModelProject == nullptr) {
        SingletonProjectEditorWarning::GetInstance().warningEmptyProject();
        return;
    }
    else {
        ProjectSaveLoadManager::GetInstance().saveToJson("test", __pModelProject);
    }
}

void ViewProjectEditor::__loadProject() {
    if (__pModelProject != nullptr) {
        delete __pModelProject;
        __pModelProject = nullptr;
    }
    __pModelProject = new ModelProject();
    ProjectSaveLoadManager::GetInstance().loadFromJson("test", __pModelProject);
    __pWidgetProjectEditorNodeView->importFromProject(__pModelProject);
}


void ViewProjectEditor::__openDialogAssignVariable(DialogNode::EDITMODE editMode, ModelNodeAssignVariable* pModelNodeAssignVariable) {
    __pDialogAssignVariable->editMode = editMode;
    if (editMode == DialogNode::NEW) {
        __pDialogAssignVariable->initValue();
    }
    else if (editMode == DialogNode::EDIT) {
        __pDialogAssignVariable->setValue(*pModelNodeAssignVariable);
    }
    __pDialogAssignVariable->setVariableIDList(__pWidgetProjectEditorNodeView->listVariableName());
    __pDialogAssignVariable->show();
}

void ViewProjectEditor::__openDialogConditional(DialogNode::EDITMODE editMode, ModelNodeConditional::CONDITIONALTYPE conditionalType, ModelNodeConditional* pModelNodeConditional) {
    __pDialogNodeCondition->editMode = editMode;
    if (editMode == DialogNode::NEW) {
        __pDialogNodeCondition->initValue(conditionalType);
    }
    else if (editMode == DialogNode::EDIT) {
        __pDialogNodeCondition->setValue(*pModelNodeConditional);
    }
    __pDialogNodeCondition->setVariableIDList(__pWidgetProjectEditorNodeView->listVariableName());
    __pDialogNodeCondition->show();
}

void ViewProjectEditor::__openDialogDelay(DialogNode::EDITMODE editMode, ModelNodeDelay* pModelNodeDelay) {
    __pDialogNodeDelay->editMode = editMode;
    if (editMode == DialogNode::NEW) {
        __pDialogNodeDelay->initValue();
    }
    else if (editMode == DialogNode::EDIT) {
        __pDialogNodeDelay->setValue(*pModelNodeDelay);
    }
    __pDialogNodeDelay->show();
}

void ViewProjectEditor::__openDialogDigitalInOut(DialogNode::EDITMODE editMode, ModelNodeDigitalIO::IOTYPE ioType, ModelNodeDigitalIO* pModelNodeDigitalIO) {
    __pDialogNodeDigitalInOut->editMode = editMode;
    if (editMode == DialogNode::NEW) {
        __pDialogNodeDigitalInOut->initValue(ioType);
    }
    else if (editMode == DialogNode::EDIT) {
        __pDialogNodeDigitalInOut->setValue(*pModelNodeDigitalIO);
    }
    __pDialogNodeDigitalInOut->show();
}

void ViewProjectEditor::__openDialogMoveRobot(DialogNode::EDITMODE editMode, ModelNodeMoveRobot::MOVETYPE moveType, ModelNodeMoveRobot* pModelNodeMoveRobot) {
    __pDialogMoveRobot->editMode = editMode;
    if (editMode == DialogNode::NEW) {
        __pDialogMoveRobot->initValue(moveType);
    }
    else if (editMode == DialogNode::EDIT) {
        __pDialogMoveRobot->setValue(*pModelNodeMoveRobot);
    }
    __pDialogMoveRobot->setVariableIDList(__pWidgetProjectEditorNodeView->listVariableName());
    __pDialogMoveRobot->show();
}

//_______________________________________SLOTS________________________________________//
void ViewProjectEditor::slotUpdateConnectionStatus(bool connection) {
    __updateConnectionStatus(connection);
}


void ViewProjectEditor::slotUpdateStatus(InterfaceRobot::ROBOT_STATUS robotStatus,
                                         InterfaceRobot::CONTROLLER_STATUS controllerStatus,
                                         InterfaceRobot::ERROR_STATUS errorStatus) {
    __updateRobotStatus(robotStatus);
    __updateControllerStatus(controllerStatus);
    __updateErrorStatus(errorStatus);
}

void ViewProjectEditor::slotOpenJogPanel() {
    __pDialogJogPanel->setVisible(true);
}

void ViewProjectEditor::slotOpenIOPanel() {
    __pDialogIOPanel->setVisible(true);
}

void ViewProjectEditor::slotOpenProjectPlayer() {
    __pWidgetProjectEditorPlayer->setVisible(true);
}

void ViewProjectEditor::slotOpenDialogAssignVariableNew() {
    __openDialogAssignVariable(DialogNode::NEW, nullptr);
}

void ViewProjectEditor::slotProcessEditNode(QUuid uuidEditNode) {
    WidgetUINode* pUINode = __findUINodeFromHash(uuidEditNode);
    if (pUINode != nullptr) {
        __uuidCurrentEditNode = uuidEditNode;
        ModelNode::NODETYPE nodeType = pUINode->pModelNode->getNodeType();

        if (nodeType == ModelNode::ASSIGN_VARIABLE) {
            __openDialogAssignVariable(DialogNode::EDIT, static_cast<ModelNodeAssignVariable*>(pUINode->pModelNode));
        }
        else if (nodeType == ModelNode::CONDITIONAL) {
            ModelNodeConditional* pModelNodeConditional = static_cast<ModelNodeConditional*>(pUINode->pModelNode);
            ModelNodeConditional::CONDITIONALTYPE conditionalType = pModelNodeConditional->conditionalType;
            __openDialogConditional(DialogNode::EDIT, conditionalType, pModelNodeConditional);
        }
        else if (nodeType == ModelNode::DELAY) {
            __openDialogDelay(DialogNode::EDIT, static_cast<ModelNodeDelay*>(pUINode->pModelNode));
        }
        else if (nodeType == ModelNode::DIGITAL_INOUT) {
            ModelNodeDigitalIO* pModelNodeDigitalInOut = static_cast<ModelNodeDigitalIO*>(pUINode->pModelNode);
            ModelNodeDigitalIO::IOTYPE ioType = pModelNodeDigitalInOut->ioType;
            __openDialogDigitalInOut(DialogNode::EDIT, ioType, pModelNodeDigitalInOut);
        }
        else if (nodeType == ModelNode::MOVE_ROBOT) {
            ModelNodeMoveRobot* pModelNodeMoveRobot = static_cast<ModelNodeMoveRobot*>(pUINode->pModelNode);
            ModelNodeMoveRobot::MOVETYPE moveType = pModelNodeMoveRobot->moveType;
            __openDialogMoveRobot(DialogNode::EDIT, moveType, pModelNodeMoveRobot);
        }
    }
}

void ViewProjectEditor::slotOpenDialogMoveJoint() {
    __openDialogMoveRobot(DialogNode::NEW, ModelNodeMoveRobot::JOINT_INTERPOLATION, nullptr);
}

void ViewProjectEditor::slotOpenDialogMoveTCP() {
    __openDialogMoveRobot(DialogNode::NEW, ModelNodeMoveRobot::TCP_LINEAR_INTERPOLATION, nullptr);
}

void ViewProjectEditor::slotOpenDialogCondition(ModelNodeConditional::CONDITIONALTYPE type) {
    __openDialogConditional(DialogNode::NEW, type, nullptr);
}

void ViewProjectEditor::slotOpenDialogDelay() {
    __openDialogDelay(DialogNode::NEW, nullptr);
}

void ViewProjectEditor::slotOpenDigitalInOutNode(ModelNodeDigitalIO::IOTYPE type) {
    __openDialogDigitalInOut(DialogNode::NEW, type, nullptr);
}

void ViewProjectEditor::slotPlayProject() {
    __playProject();
}

void ViewProjectEditor::slotPauseProject() {
    __pauseProject();
}

void ViewProjectEditor::slotResumeProject() {
    __resumeProject();
}

void ViewProjectEditor::slotStopProject() {
    __stopProject();
}

void ViewProjectEditor::slotProcessAppliedNodeInformation(int dialogID) {

    WidgetUINode* pUINode = nullptr;
    if (dialogID == PROJECT_EDITOR_DIALOG_ASSIGN_VARIABLE) {
        ModelNodeAssignVariable* pModelNodeAssignVariable = nullptr;
        if (__pDialogAssignVariable->editMode == DialogNode::NEW) {
            pUINode = new WidgetUINode(nullptr);
            pUINode->setColor(SingletonColor::GetInstance().ColorNodeAssignVariable);
            pModelNodeAssignVariable = SingletonFactoryModelNode::GetInstance().createNodeAssignVariable();
            pModelNodeAssignVariable->cloneData(__pDialogAssignVariable->getValue());
            pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeAssignVariable);
        }
        else {
            pUINode = __findUINodeFromHash(__uuidCurrentEditNode);
            if (pUINode != nullptr) {
                pModelNodeAssignVariable = static_cast<ModelNodeAssignVariable*>(pUINode->pModelNode);
                pModelNodeAssignVariable->cloneData(__pDialogAssignVariable->getValue());
                pUINode->updateText();
            }
            return;
        }
    }
    else if (dialogID == PROJECT_EDITOR_DIALOG_MOVE_ROBOT) {
        ModelNodeMoveRobot* pModelNodeMoveRobot = nullptr;
        if (__pDialogMoveRobot->editMode == DialogNode::NEW) {
            pUINode = new WidgetUINode(nullptr);
            pUINode->setColor(SingletonColor::GetInstance().ColorNodeMoveRobot);
            pModelNodeMoveRobot  = SingletonFactoryModelNode::GetInstance().createNodeMoveRobot();
            pModelNodeMoveRobot->cloneData(__pDialogMoveRobot->getValue());
            pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeMoveRobot);
        }
        else {
            pUINode = __findUINodeFromHash(__uuidCurrentEditNode);
            if (pUINode != nullptr) {
                pModelNodeMoveRobot = static_cast<ModelNodeMoveRobot*>(pUINode->pModelNode);
                pModelNodeMoveRobot->cloneData(__pDialogMoveRobot->getValue());
                pUINode->updateText();
            }
            return;
        }
    }
    else if (dialogID == PROJECT_EDITOR_DIALOG_CONDITIONAL) {
        ModelNodeConditional* pModelNodeConditional = nullptr;
        if (__pDialogNodeCondition->editMode == DialogNode::NEW) {
            pUINode = new WidgetUINode(nullptr);
            pUINode->setColor(SingletonColor::GetInstance().ColorNodeConditional);
            pModelNodeConditional  = SingletonFactoryModelNode::GetInstance().createNodeConditional();
            pModelNodeConditional->cloneData(__pDialogNodeCondition->getValue());
            pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeConditional);
            if (pModelNodeConditional->conditionalType == ModelNodeConditional::IF || pModelNodeConditional->conditionalType == ModelNodeConditional::LOOP) {
                pUINode->flagContainerTop = true;
            }
            else {
                pUINode->flagContainerBetween = true;
            }
        }
        else {
            pUINode = __findUINodeFromHash(__uuidCurrentEditNode);
            if (pUINode != nullptr) {
                pModelNodeConditional = static_cast<ModelNodeConditional*>(pUINode->pModelNode);
                pModelNodeConditional->cloneData(__pDialogNodeCondition->getValue());
                pUINode->updateText();
            }
            return;
        }
    }
    else if (dialogID == PROJECT_EDITOR_DIALOG_DELAY) {
        ModelNodeDelay* pModelNodeDelay = nullptr;
        if (__pDialogNodeDelay->editMode == DialogNode::NEW) {
            pUINode = new WidgetUINode(nullptr);
            pUINode->setColor(SingletonColor::GetInstance().ColorNodeDelay);
            pModelNodeDelay = SingletonFactoryModelNode::GetInstance().createNodeDelay();
            pModelNodeDelay->cloneData(__pDialogNodeDelay->getValue());
            pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeDelay);
        }
        else {
            pUINode = __findUINodeFromHash(__uuidCurrentEditNode);
            if (pUINode != nullptr) {
                pModelNodeDelay = static_cast<ModelNodeDelay*>(pUINode->pModelNode);
                pModelNodeDelay->cloneData(__pDialogNodeDelay->getValue());
                pUINode->updateText();
            }
            return;
        }
    }
    else if (dialogID == PROJECT_EDITOR_DIALOG_DIGITAL_INOUT) {
        ModelNodeDigitalIO* pModelNodeDigitalInOut = nullptr;
        if (__pDialogNodeDigitalInOut->editMode == DialogNode::NEW) {
            pUINode = new WidgetUINode(nullptr);
            pUINode->setColor(SingletonColor::GetInstance().ColorNodeDigitalIO);
            pModelNodeDigitalInOut = SingletonFactoryModelNode::GetInstance().createNodeDigitalInOut();
            pModelNodeDigitalInOut->cloneData(__pDialogNodeDigitalInOut->getValue());
            pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeDigitalInOut);
        }
        else {
            pUINode = __findUINodeFromHash(__uuidCurrentEditNode);
            if (pUINode != nullptr) {
                pModelNodeDigitalInOut = static_cast<ModelNodeDigitalIO*>(pUINode->pModelNode);
                pModelNodeDigitalInOut->cloneData(__pDialogNodeDigitalInOut->getValue());
                pUINode->updateText();
            }
            return;
        }
    }
    pUINode->updateText();
    __pWidgetProjectEditorNodeView->insertNode(pUINode);
}

void ViewProjectEditor::slotOnRunningNode(QUuid nodeID) {
    WidgetUINode* pUINode = __findUINodeFromHash(nodeID);
    if (pUINode != nullptr) {
        pUINode->setOnRunning(true);
    }
}


void ViewProjectEditor::slotOnFinishedNode(QUuid nodeID) {
    WidgetUINode* pUINode = __findUINodeFromHash(nodeID);
    if (pUINode != nullptr) {
        pUINode->setOnRunning(false);
    }
}

void ViewProjectEditor::slotOnErrorNode(QUuid nodeID) {
    Q_UNUSED(nodeID)
}

void ViewProjectEditor::slotOnFinishedPlayingProject() {
    __pWidgetProjectEditorPlayer->setState(WidgetProjectEditorPlayer::STOP);
}

void ViewProjectEditor::slotSaveProject() {
    __saveProject();
}

void ViewProjectEditor::slotLoadProject() {
    __loadProject();
}

void ViewProjectEditor::slotEmergencyStop() {
    __stopRobot();
}

void ViewProjectEditor::slotToggleServoOnOff() {
    if (__flagServoStatus) {
        __setServoStatus(false);
    }
    else {
        __setServoStatus(true);
    }
}

void ViewProjectEditor::slotToggleBrakeOnOff() {
    if (__flagBrakeStatus) {
        __setBrakeStatus(false);
    }
    else {
        __setBrakeStatus(true);
    }
}
