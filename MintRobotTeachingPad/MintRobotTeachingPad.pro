QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MintRobotTeachingPad
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    resources.qrc

HEADERS += \
    app/Controller/Comm/BlockingTCPSocket.h \
    app/Controller/Comm/CommProtocol.h \
    app/Controller/Comm/ConfigureComm.h \
    app/Controller/Comm/WorkerConnectionHandler.h \
    app/Controller/Comm/WorkerStatusUpdater.h \
    app/Controller/Runtime/ProjectSaveLoadManager.h \
    app/Controller/Runtime/ThreadProjectPlayer.h \
    app/Controller/SingletonComm.h \
    app/Controller/SingletonConfiguration.h \
    app/Controller/SingletonRuntimeProject.h \
    app/Model/Interface/InterfaceNodeStatusNotifier.h \
    app/Model/Interface/InterfaceRobot.h \
    app/Model/Nodes/ModelNode.h \
    app/Model/Nodes/ModelNodeAssignVariable.h \
    app/Model/Nodes/ModelNodeConditional.h \
    app/Model/Nodes/ModelNodeContainer.h \
    app/Model/Nodes/ModelNodeDelay.h \
    app/Model/Nodes/ModelNodeDigitalIO.h \
    app/Model/Nodes/ModelNodeDummy.h \
    app/Model/Nodes/ModelNodeMoveRobot.h \
    app/Model/Project/ModelProject.h \
    app/Model/Project/ModelValue.h \
    app/Model/SingletonFactoryModelNode.h \
    app/Model/SingletonInterfaceManager.h \
    app/View/Menu/ViewMainMenu.h \
    app/View/ProjectEditor/Dialog/DialogAssignValue.h \
    app/View/ProjectEditor/Dialog/DialogExecuteNode.h \
    app/View/ProjectEditor/Dialog/DialogIOPanel.h \
    app/View/ProjectEditor/Dialog/DialogJogPanel.h \
    app/View/ProjectEditor/Dialog/DialogNode.h \
    app/View/ProjectEditor/Dialog/DialogNodeAssignVariable.h \
    app/View/ProjectEditor/Dialog/DialogNodeCondition.h \
    app/View/ProjectEditor/Dialog/DialogNodeDelay.h \
    app/View/ProjectEditor/Dialog/DialogNodeDigitalInOut.h \
    app/View/ProjectEditor/Dialog/DialogNodeMoveRobot.h \
    app/View/ProjectEditor/Dialog/DialogSelectAssignOperator.h \
    app/View/ProjectEditor/Dialog/DialogSelectCompareCondition.h \
    app/View/ProjectEditor/Dialog/DialogSelectVariable.h \
    app/View/ProjectEditor/Dialog/WidgetJogJoint.h \
    app/View/ProjectEditor/Dialog/WidgetJogPosMonitor.h \
    app/View/ProjectEditor/Dialog/WidgetJogTCPRotation.h \
    app/View/ProjectEditor/Dialog/WidgetJogTCPTranslation.h \
    app/View/ProjectEditor/MenuBar/Menu.h \
    app/View/ProjectEditor/MenuBar/MenuFlowControl.h \
    app/View/ProjectEditor/MenuBar/MenuIO.h \
    app/View/ProjectEditor/MenuBar/MenuProject.h \
    app/View/ProjectEditor/MenuBar/MenuRobot.h \
    app/View/ProjectEditor/MenuBar/MenuSystem.h \
    app/View/ProjectEditor/ViewProjectEditor.h \
    app/View/ProjectEditor/WidgetProjectEditorMenu.h \
    app/View/ProjectEditor/WidgetProjectEditorNodeView.h \
    app/View/ProjectEditor/WidgetProjectEditorPlayer.h \
    app/View/ProjectEditor/WidgetProjectEditorToolbar.h \
    app/View/ProjectEditor/WidgetUINode.h \
    app/View/RobotConfig/DialogRobotConfiguration.h \
    app/View/Util/Dialog.h \
    app/View/Util/DialogKeyboard.h \
    app/View/Util/DialogKeypad.h \
    app/View/Util/FileExplorer.h \
    app/View/Util/FileExplorerItem.h \
    app/View/Util/MTPWidget.h \
    app/View/Util/WidgetButton.h \
    app/View/Util/WidgetCheckBox.h \
    app/View/Util/WidgetKeyboard.h \
    app/View/Util/WidgetKeypad.h \
    app/View/Util/WidgetLabel.h \
    app/View/Util/WidgetRect.h \
    app/View/Util/WidgetSlider.h \
    app/View/Util/WidgetSliderBar.h \
    app/View/Util/WidgetSlideSwitch.h \
    app/View/SingletonColor.h \
    app/View/SingletonFont.h \
    app/View/SingletonImage.h \
    app/View/SingletonProjectEditorWarning.h \
    app/View/stringid.h \
    app/View/viewid.h \
    app/View/viewsize.h \
    app/View/SingletonMainWindow.h

SOURCES += \
    app/Controller/Comm/BlockingTCPSocket.cpp \
    app/Controller/Comm/WorkerConnectionHandler.cpp \
    app/Controller/Comm/WorkerStatusUpdater.cpp \
    app/Controller/Runtime/ProjectSaveLoadManager.cpp \
    app/Controller/Runtime/ThreadProjectPlayer.cpp \
    app/Controller/SingletonComm.cpp \
    app/Controller/SingletonConfiguration.cpp \
    app/Controller/SingletonRuntimeProject.cpp \
    app/Model/Interface/InterfaceNodeStatusNotifier.cpp \
    app/Model/Interface/InterfaceRobot.cpp \
    app/Model/Nodes/ModelNode.cpp \
    app/Model/Nodes/ModelNodeAssignVariable.cpp \
    app/Model/Nodes/ModelNodeConditional.cpp \
    app/Model/Nodes/ModelNodeContainer.cpp \
    app/Model/Nodes/ModelNodeDelay.cpp \
    app/Model/Nodes/ModelNodeDigitalIO.cpp \
    app/Model/Nodes/ModelNodeDummy.cpp \
    app/Model/Nodes/ModelNodeMoveRobot.cpp \
    app/Model/Project/ModelProject.cpp \
    app/Model/Project/ModelValue.cpp \
    app/Model/SingletonFactoryModelNode.cpp \
    app/Model/SingletonInterfaceManager.cpp \
    app/View/Menu/ViewMainMenu.cpp \
    app/View/ProjectEditor/Dialog/DialogAssignValue.cpp \
    app/View/ProjectEditor/Dialog/DialogExecuteNode.cpp \
    app/View/ProjectEditor/Dialog/DialogIOPanel.cpp \
    app/View/ProjectEditor/Dialog/DialogJogPanel.cpp \
    app/View/ProjectEditor/Dialog/DialogNode.cpp \
    app/View/ProjectEditor/Dialog/DialogNodeAssignVariable.cpp \
    app/View/ProjectEditor/Dialog/DialogNodeCondition.cpp \
    app/View/ProjectEditor/Dialog/DialogNodeDelay.cpp \
    app/View/ProjectEditor/Dialog/DialogNodeDigitalInOut.cpp \
    app/View/ProjectEditor/Dialog/DialogNodeMoveRobot.cpp \
    app/View/ProjectEditor/Dialog/DialogSelectAssignOperator.cpp \
    app/View/ProjectEditor/Dialog/DialogSelectCompareCondition.cpp \
    app/View/ProjectEditor/Dialog/DialogSelectVariable.cpp \
    app/View/ProjectEditor/Dialog/WidgetJogJoint.cpp \
    app/View/ProjectEditor/Dialog/WidgetJogPosMonitor.cpp \
    app/View/ProjectEditor/Dialog/WidgetJogTCPRotation.cpp \
    app/View/ProjectEditor/Dialog/WidgetJogTCPTranslation.cpp \
    app/View/ProjectEditor/MenuBar/Menu.cpp \
    app/View/ProjectEditor/MenuBar/MenuFlowControl.cpp \
    app/View/ProjectEditor/MenuBar/MenuIO.cpp \
    app/View/ProjectEditor/MenuBar/MenuProject.cpp \
    app/View/ProjectEditor/MenuBar/MenuRobot.cpp \
    app/View/ProjectEditor/MenuBar/MenuSystem.cpp \
    app/View/ProjectEditor/ViewProjectEditor.cpp \
    app/View/ProjectEditor/WidgetProjectEditorMenu.cpp \
    app/View/ProjectEditor/WidgetProjectEditorNodeView.cpp \
    app/View/ProjectEditor/WidgetProjectEditorPlayer.cpp \
    app/View/ProjectEditor/WidgetProjectEditorToolbar.cpp \
    app/View/ProjectEditor/WidgetUINode.cpp \
    app/View/RobotConfig/DialogRobotConfiguration.cpp \
    app/View/Util/Dialog.cpp \
    app/View/Util/DialogKeyboard.cpp \
    app/View/Util/DialogKeypad.cpp \
    app/View/Util/FileExplorer.cpp \
    app/View/Util/FileExplorerItem.cpp \
    app/View/Util/MTPWidget.cpp \
    app/View/Util/WidgetButton.cpp \
    app/View/Util/WidgetCheckBox.cpp \
    app/View/Util/WidgetKeyboard.cpp \
    app/View/Util/WidgetKeypad.cpp \
    app/View/Util/WidgetLabel.cpp \
    app/View/Util/WidgetRect.cpp \
    app/View/Util/WidgetSlider.cpp \
    app/View/Util/WidgetSliderBar.cpp \
    app/View/Util/WidgetSlideSwitch.cpp \
    app/View/SingletonColor.cpp \
    app/View/SingletonFont.cpp \
    app/View/SingletonImage.cpp \
    app/View/SingletonProjectEditorWarning.cpp \
    app/View/viewsize.cpp \
    main.cpp \
    app/View/SingletonMainWindow.cpp
