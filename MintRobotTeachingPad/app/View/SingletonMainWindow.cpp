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

#include "SingletonMainWindow.h"

//_______________________________________CONSTRUCTOR__________________________________//
SingletonMainWindow::SingletonMainWindow(QMainWindow *parent) : QMainWindow(parent) {
//    mTimer = new QTimer(this);
//    connect(mTimer, SIGNAL(timeout()), this, SLOT(onTimerResize()));
    pViewMainMenu = new ViewMainMenu(this);
}

SingletonMainWindow::~SingletonMainWindow() {

}

//Intro* MainWindow::getIntroWidget() { return mIntro;}
//ViewMainMenu* MainWindow::getHomeWidget() {   return mMainMenu;}
//ProjectEditor* MainWindow::getProjectEditorWidget() {   return mProejctEditor;}
//ProejctSelectDialog* MainWindow::getProjectSelectDialogWidget() {  return mProjectSelectDialog;}
//Log* MainWindow::getLogWidget() { return mLog;}
//LogItemPrintWidget* MainWindow::getLogItemPrintWiget() { return mLogItemPrintWiget;}
//RobotTypeSettingDialog* MainWindow::getRobotTypeSettingDialogWidget() { return mRobotTypeSettingDialog;}
//NetSettingDialog* MainWindow::getNetSettingDialogWidget() { return mNetSettingDialog;}
//ClientConnectingWidget* MainWindow::getClientConnectingWidget() { return mClientConnectiongWidget;}

//void MainWindow::onRunNodeId(int nodeId) {
//    mProejctEditor->onRunNodeId(nodeId);
//}

//void MainWindow::onIOState(QByteArray io) {
//    mProejctEditor->onIOState(io);
//}

//QString MainWindow::getIp() {
//    mHomeWidget->setVisibleSetNetItem(false);
//    return mNetSettingDialog->getIp();
//}

//_______________________________________PUBLIC_______________________________________//

//_______________________________________PROTECTED____________________________________//
void SingletonMainWindow::resizeEvent(QResizeEvent * event) {
    Q_UNUSED(event)

//    resizeWindow();

    pViewMainMenu->setGeometry(0, 0, width(), height());


//    initIntroWidget();
//    initHomeWidget();
//    initEditWidget();
//    initSelectProjectWidget();
//    initLogWidget();
//    initLogItemPrintWidget();
//    initRobotSetting();
//    initNetSettingDialog();
//    initClientConnectingWidget();

}

//void MainWindow::moveEvent(QMoveEvent * event ) {
//    Q_UNUSED(event)
//    resizeWindow();
//    initIntroWidget();
//    initHomeWidget();
//    initEditWidget();
//    initSelectProjectWidget();
//    initLogWidget();
//    initLogItemPrintWidget();
//    initRobotSetting();
//    initNetSettingDialog();
//    initClientConnectingWidget();
//}

//ProejctEditor *MainWindow::getProejctEditorWidget() const
//{
//    return mProejctEditor;
//}

//void MainWindow::setProjctEditorWidget(ProejctEditor *proejctEditorWidget)
//{
//    mProejctEditor = proejctEditorWidget;
//}


//_______________________________________PRIVATE______________________________________//
void SingletonMainWindow::resizeWindow() {
    int x = geometry().x();
    int y = geometry().y();

    QScreen *screen0 = QGuiApplication::screens().at(0);
    int screenW = screen0->size().width();
    int screenH = screen0->size().height();
    int dotPerInch = static_cast<int>(screen0->physicalDotsPerInch());

    if (QGuiApplication::screens().size() == 2) {
        QScreen *screen1 = QGuiApplication::screens().at(1);
        bool inScreen1 = false;
        if (0 < screen1->geometry().x()) {
            if (screenW <= x) { inScreen1 = true;}
        } else {
            if (x <= 0) { inScreen1 = true;}
        }
        if (inScreen1) {
            screenW = screen1->size().width();
            screenH = screen1->size().height();
            dotPerInch = static_cast<int>(screen1->physicalDotsPerInch());
        }
    }

    ViewSize::GetInstance().setSize(screenW, screenH, dotPerInch);

    int w = width();
    int h = height();
    if (w < ViewSize::GetInstance().VIEW_SIZE_MIN_WIDTH) {
        w = ViewSize::GetInstance().VIEW_SIZE_MIN_WIDTH;
    }

    if (h < ViewSize::GetInstance().VIEW_SIZE_MIN_HEIGHT) {
        h = ViewSize::GetInstance().VIEW_SIZE_MIN_HEIGHT;
    }

    if (y < 30) {
        y = 30;
    }

    if (screenH - 50 < y) {
        y = screenH - 50;
    }

    setGeometry(x, y, w, h);
}

//void MainWindow::initIntroWidget() {
//    if (!mInit) {
//        mIntro = new Intro(this);
//        connect(mIntro, SIGNAL(onIntroFinish()), this, SIGNAL(onIntroFinish()));
//        mIntro->setVisible(false);
//    }
//    mIntro->setGeometry(0, 0, width(), height());
//}

//void MainWindow::initHomeWidget() {
//    if (!mInit) {
//        mMainMenu = new ViewMainMenu(this);
//        connect(mMainMenu, SIGNAL(onClick(int)), this, SIGNAL(onMenuSelected(int)));
//        mMainMenu->setVisible(false);
//    }
//    mMainMenu->setGeometry(0, 0, width(), height());
//}

//void MainWindow::initEditWidget() {
//    if (!mInit) {
//        mProejctEditor = new ProjectEditor(this);

//        // Jog signals
//        connect(mProejctEditor, SIGNAL(onClickJogTCP(int)), this, SIGNAL(onClickJogTCP(int)));
//        connect(mProejctEditor, SIGNAL(onClickJogJoint(int,bool)), this, SIGNAL(onClickJogJoint(int, bool)));
//        connect(mProejctEditor, SIGNAL(onClickHomePosition()), this, SIGNAL(onClickHomePosition()));
//        connect(mProejctEditor, SIGNAL(onClickDirectTeachingStart()), this, SIGNAL(onClickDirectTeachingStart()));
//        connect(mProejctEditor, SIGNAL(onClickDirectTeachingStop()), this, SIGNAL(onClickDirectTeachingStop()));
//        connect(mProejctEditor, SIGNAL(onStop()), this, SIGNAL(onStop()));

//        connect(mProejctEditor, SIGNAL(onChangeJoint(int,float)), this, SIGNAL(onChangeJoint(int, float)));

//        // Project Menu
//        connect(mProejctEditor, SIGNAL(onClickReturnBtn()), this, SIGNAL(onClickCloseProjectEditorBtn()));
//        connect(mProejctEditor, SIGNAL(onClickSaveBtn(bool, QString, QList<VariableDataNode>, QList<PositionDataNode>, QList<DataNode*>)), this, SIGNAL(onClickProjectSaveBtn(bool, QString, QList<VariableDataNode>, QList<PositionDataNode>, QList<DataNode*>)));
//        connect(mProejctEditor, SIGNAL(onClickRunBtn()), this, SIGNAL(onClickProjectRunBtn()));
//        connect(mProejctEditor, SIGNAL(onClickPauseBtn()), this, SIGNAL(onClickProjectPauseBtn()));
//        connect(mProejctEditor, SIGNAL(onClickReplayBtn()), this, SIGNAL(onClickProjectResumeBtn()));
//        connect(mProejctEditor, SIGNAL(onClickStopBtn()), this, SIGNAL(onClickProjectStopBtn()));
//        connect(mProejctEditor, SIGNAL(onChangeRunSpeed(int)), this, SIGNAL(onChangeProjectRunSpeed(int)));



//        connect(mProejctEditor, SIGNAL(onClickSetting(double,double,double)), this, SIGNAL(onClickSetting(double,double,double)));
//        connect(mProejctEditor, SIGNAL(onClickOutBtn(int,int)), this, SIGNAL(onClickOutBtn(int, int)));
//        connect(mProejctEditor, SIGNAL(onClickSetThisPositionBtn(PositionDataNode)), this, SIGNAL(onClickSetThisPositionBtn(PositionDataNode)));

//        connect(this, SIGNAL(onUpdateRobotStatus(RobotStatus*)), mProejctEditor, SLOT(updateRobotStatus(RobotStatus*)));
//        mProejctEditor->setVisible(false);
//    }
//    mProejctEditor->setGeometry(0, 0, width(), height());
//}

//void MainWindow::initSelectProjectWidget() {
//    if (!mInit) {
//        mProjectSelectDialog = new ProejctSelectDialog(this);
//        mProjectSelectDialog->setVisible(false);
//        connect(mProjectSelectDialog, SIGNAL(onClick(int)), this, SIGNAL(onClickSelectProjectOk(int)));
//        connect(mProjectSelectDialog, SIGNAL(onClickCancel()), this, SIGNAL(onClickSelectProjectCancel()));
//        connect(mProjectSelectDialog, SIGNAL(onClickDelete(int)), this, SIGNAL(onClickSelectProjectDelete(int)));

//        mProjectSelectDialog->setVisible(false);
//    }
//    mProjectSelectDialog->setGeometry(0, 0, width(), height());
//}

//void MainWindow::initLogWidget() {
//    if (!mInit) {
//        mLog = new Log(this);
//        mLog->setVisible(false);
//        connect(mLog, SIGNAL(onClick(int)), this, SIGNAL(onClickLogFileOk(int)));
//        connect(mLog, SIGNAL(onClickCancel()), this, SIGNAL(onClickLogFileCancel()));
//        connect(mLog, SIGNAL(onClickDelete(int)), this, SIGNAL(onClickLogFileDelete(int)));

//        mLog->setVisible(false);
//    }
//    mLog->setGeometry(0, 0, width(), height());
//}

//void MainWindow::initLogItemPrintWidget() {
//    if (!mInit) {
//        mLogItemPrintWiget = new LogItemPrintWidget(this);
//        mLogItemPrintWiget->setVisible(false);
//        connect(mLogItemPrintWiget, SIGNAL(onClick()), this, SIGNAL(onClickLogItemPrintOk()));
//        connect(mLogItemPrintWiget, SIGNAL(onClickDelete(QString)), this, SIGNAL(onClickLogItemPrintDelete(QString)));

//        mLogItemPrintWiget->setVisible(false);
//    }
//    mLogItemPrintWiget->setGeometry(0, 0, width(), height());
//}

//void MainWindow::initRobotSetting() {
//    if (!mInit) {
//        mRobotTypeSettingDialog = new RobotTypeSettingDialog(this, ConfigurationManager::GetInstance().robotType);
//        connect(mRobotTypeSettingDialog, SIGNAL(onClickApply(int)), this, SLOT(onClickRobotConfigurationApply(int)));
//        connect(mRobotTypeSettingDialog, SIGNAL(onClickCancel()), this, SLOT(onClickRobotConfigurationCancel()));
//        mRobotTypeSettingDialog->setVisible(false);
//    }
//    mRobotTypeSettingDialog->setGeometry(0, 0, width(), height());
//}

//void MainWindow::initNetSettingDialog() {
//    if (!mInit) {
//        mNetSettingDialog = new NetSettingDialog(this);
//        connect(mNetSettingDialog, SIGNAL(onClickApply(QString)), this, SLOT(onClickNetworkConfigurationApply(QString)));
//        connect(mNetSettingDialog, SIGNAL(onClickCancel()), this, SLOT(onClickNetworkConfigurationCancel()));
//        mNetSettingDialog->setVisible(false);
//    }
//    mNetSettingDialog->setGeometry(0, 0, width(), height());
//}

//void MainWindow::initClientConnectingWidget() {
//    if (!mInit) {
//        mClientConnectiongWidget = new ClientConnectingWidget(this);
//        mClientConnectiongWidget->setVisible(false);
//    }
//    mClientConnectiongWidget->setGeometry(0, 0, width(), height());
//}

////_______________________________________SLOTS________________________________________//
//void MainWindow::onTimerResize() {
//    if (mPreWidth == width()) {
//        if (mPreHeight == height()) {
//            mTimerStart = false;
//            mTimer->stop();
//            resizeWindow();
//            return ;
//        }
//    }
//    mPreWidth = width();
//    mPreHeight = height();
//}

//void MainWindow::onClickRobotConfigurationApply(int index) {
//    mRobotTypeSettingDialog->setVisible(false);
//    emit onRobotTypeSettingChanged(index);
//}

//void MainWindow::onClickRobotConfigurationCancel() {
//    if (mInit) {
//        mRobotTypeSettingDialog->setVisible(false);
//    }
//}

//void MainWindow::onClickNetworkConfigurationApply(QString address) {
//    mNetSettingDialog->setVisible(false);
//    emit onNetworkSettingChanged(address);
//}

//void MainWindow::onClickNetworkConfigurationCancel() {
//    if (mInit) {
//        mNetSettingDialog->setVisible(false);
//    }
//}

//void MainWindow::updateRobotStatus(RobotStatus* pRobotStatus) {
//    emit onUpdateRobotStatus(pRobotStatus);
//}
