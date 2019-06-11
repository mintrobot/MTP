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

#ifndef EDITWIDGET_H
#define EDITWIDGET_H

//__________________________________________________________

#include <QString>
#include <QtMath>

#include "app/view/util/MTPWidget.h"

#include "dialog/DialogNodeAssignVariable.h"
#include "dialog/DialogNodeMoveRobot.h"
#include "dialog/DialogNodeCondition.h"
#include "dialog/DialogNodeDelay.h"
#include "dialog/DialogNodeDigitalInOut.h"

#include "dialog/DialogJogPanel.h"
#include "dialog/DialogIOPanel.h"

#include "WidgetProjectEditorMenu.h"
#include "WidgetProjectEditorNodeView.h"
#include "WidgetProjectEditorPlayer.h"
#include "WidgetProjectEditorToolbar.h"

#include "app/model/SingletonFactoryModelNode.h"

#include "app/controller/SingletonRuntimeProject.h"
#include "app/controller/runtime/ProjectSaveLoadManager.h"

#include "app/view/SingletonProjectEditorWarning.h"


//__________________________________________________________
class ViewProjectEditor : public MTPWidget
{
    Q_OBJECT

public:
    explicit ViewProjectEditor(QWidget *parent = nullptr);
    virtual ~ViewProjectEditor() override;


protected:
    virtual void resizeEvent(QResizeEvent * event) override;


private:
    //-------------------------------------------//
    //--- GUI related variables and functions ---//
    //-------------------------------------------//
    WidgetLabel *__pLabelBackground;

    // Basic Widgets
    WidgetProjectEditorMenu* __pWidgetProjectEditorMenu;
    WidgetProjectEditorNodeView* __pWidgetProjectEditorNodeView;
    WidgetProjectEditorToolbar* __pWidgetProjectEditorToolbar;
    WidgetProjectEditorPlayer* __pWidgetProjectEditorPlayer;

    WidgetButton* __pButtonStop;
    WidgetButton* __pButtonServoOnOff;
    WidgetButton* __pButtonBrakeOnOff;
    WidgetLabel* __pLabelRobotStatus;
    WidgetLabel* __pLabelRobotStatusValue;
    WidgetLabel* __pLabelServoStatus;
    WidgetLabel* __pLabelServoStatusValue;
    WidgetLabel* __pLabelBrakeStatus;
    WidgetLabel* __pLabelBrakeStatusValue;
    WidgetLabel* __pLabelConnectionStatus;
    WidgetLabel* __pLabelConnectionStatusValue;

    // Dialogs for node setting
    DialogNodeAssignVariable* __pDialogAssignVariable;
    DialogNodeMoveRobot* __pDialogMoveRobot;
    DialogNodeCondition* __pDialogNodeCondition;
    DialogNodeDelay* __pDialogNodeDelay;
    DialogNodeDigitalInOut* __pDialogNodeDigitalInOut;

    // Dialogs for a control panel (jog and digital IO)
    DialogJogPanel* __pDialogJogPanel;
    DialogIOPanel* __pDialogIOPanel;

    // Widget placement variables
    double __ratioNodeView = 76;
    double __ratioToolbar = 4;
    double __ratioMenu = 20;
    int __widthNodeView;
    int __widthToolbar;
    int __widthMenu;

    // Dialogs control methods
    void __openDialogAssignVariable(DialogNode::EDITMODE editMode, ModelNodeAssignVariable* pModelNodeAssignVariable);
    void __openDialogConditional(DialogNode::EDITMODE editMode, ModelNodeConditional::CONDITIONALTYPE conditionalType, ModelNodeConditional* pModelNodeConditional);
    void __openDialogDelay(DialogNode::EDITMODE editMode, ModelNodeDelay* pModelNodeDelay);
    void __openDialogDigitalInOut(DialogNode::EDITMODE editMode, ModelNodeDigitalIO::IOTYPE ioType, ModelNodeDigitalIO* pModelNodeDigitalIO);
    void __openDialogMoveRobot(DialogNode::EDITMODE editMode, ModelNodeMoveRobot::MOVETYPE moveType, ModelNodeMoveRobot* pModelNodeMoveRobot);


    //----------------------------------------------------//
    //--- Control flow related variables and functions ---//
    //----------------------------------------------------//
    // Node edit
    ModelProject* __pModelProject;
    QUuid __uuidCurrentEditNode = nullptr;

    //Robot and controller status flag
    bool __flagConnectionStatus = false;
    bool __flagRobotReadyStatus = false;
    bool __flagServoStatus = false;
    bool __flagBrakeStatus = true;

    // Node control methods
    WidgetUINode* __findUINodeFromHash(QUuid nodeID);

    // Status control
    bool __isOperable();
    void __updateConnectionStatus(bool flagStatus);
    void __updateRobotStatus(InterfaceRobot::ROBOT_STATUS robotStatus);
    void __updateControllerStatus(InterfaceRobot::CONTROLLER_STATUS controllerStatus);
    void __updateErrorStatus(InterfaceRobot::ERROR_STATUS errorStatus);
    void __updateServoStatus(bool flagStatus);
    void __updateBrakeStatus(bool flagStatus);

    // Manipulate robot
    void __stopRobot();
    void __setServoStatus(bool flagStatus);
    void __setBrakeStatus(bool flagStatus);

    // Project management
    void __playProject();
    void __pauseProject();
    void __resumeProject();
    void __stopProject();
    void __saveProject();
    void __loadProject();

signals:


private slots:
    void slotUpdateStatus(InterfaceRobot::ROBOT_STATUS robotStatus,
                          InterfaceRobot::CONTROLLER_STATUS controllerStatus,
                          InterfaceRobot::ERROR_STATUS errorStatus);

    void slotUpdateConnectionStatus(bool connection);


    void slotOpenJogPanel();
    void slotOpenIOPanel();

    void slotOpenDialogAssignVariableNew();
    void slotOpenDialogMoveJoint();
    void slotOpenDialogMoveTCP();
    void slotOpenDialogCondition(ModelNodeConditional::CONDITIONALTYPE type);
    void slotOpenDialogDelay();
    void slotOpenDigitalInOutNode(ModelNodeDigitalIO::IOTYPE type);

    void slotOpenProjectPlayer();

    void slotProcessEditNode(QUuid uuidEditNode);

    void slotSaveProject();
    void slotLoadProject();

    void slotPlayProject();
    void slotPauseProject();
    void slotResumeProject();
    void slotStopProject();

    void slotEmergencyStop();
    void slotToggleServoOnOff();
    void slotToggleBrakeOnOff();


    void slotProcessAppliedNodeInformation(int dialogID);

    virtual void slotOnRunningNode(QUuid nodeID);
    virtual void slotOnFinishedNode(QUuid nodeID);
    virtual void slotOnErrorNode(QUuid nodeID);
    virtual void slotOnFinishedPlayingProject();

};
//__________________________________________________________

#endif // EDITWIDGET_H
