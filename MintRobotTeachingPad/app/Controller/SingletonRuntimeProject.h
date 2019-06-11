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

#ifndef SINGLETONRUNTIMEPROJECT_H
#define SINGLETONRUNTIMEPROJECT_H

#include <QThread>

#include "app/model/project/ModelProject.h"
#include "app/model/interface/InterfaceNodeStatusNotifier.h"
#include "app/controller/runtime/ThreadProjectPlayer.h"

#include "SingletonComm.h"

class SingletonRuntimeProject : public QObject
{
    Q_OBJECT

public:
    explicit SingletonRuntimeProject();
    virtual ~SingletonRuntimeProject();

    static SingletonRuntimeProject &GetInstance() {
        static SingletonRuntimeProject instance;
        return instance;
    }

    void setProjectModel(ModelProject* pModelProject);
    ModelProject* getProjectModel();
    void setNotifier(InterfaceNodeStatusNotifier* pNotifier);

    void playProject();
    void pauseProject();
    void resumeProject();
    void stopProject();

private:
    ModelProject* __pModelProject;
    InterfaceNodeStatusNotifier* __pInterfaceNodeStatusNotifier;
    ThreadProjectPlayer* __pWorkerThread;

signals:
    void signalRunningNode(QUuid nodeID);
    void signalFinishedNode(QUuid nodeID);
    void signalErrorOnNode(QUuid nodeID);

    void signalPlayProject();
    void signalPauseProject();
    void signalResumeProject();
    void signalStopProject();

};

#endif // SINGLETONRUNTIMEPROJECT_H
