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

#ifndef WORKERPROJECT_H
#define WORKERPROJECT_H

#include <QThread>
#include <QMutex>
#include "app/model/nodes/ModelNode.h"
#include "app/model/project/ModelProject.h"
#include "app/model/interface/InterfaceNodeStatusNotifier.h"


class ThreadProjectPlayer : public QThread
{
    Q_OBJECT

public:
    explicit ThreadProjectPlayer();
    virtual ~ThreadProjectPlayer() override;

    void setProject(ModelProject* pModelProject);
    void setNotifier(InterfaceNodeStatusNotifier* pNotifier);

private:
    ModelProject* __pModelProject = nullptr;
    InterfaceNodeStatusNotifier* __pNotifier = nullptr;
    QMutex __mutexFlags;
    bool __flagStop = false;
    bool __flagPause = false;

    virtual void run() override;

signals:
    void signalRunningNode(QUuid nodeID);
    void signalFinishedNode(QUuid nodeID);
    void signalErrorOnNode(QUuid nodeID);
    void signalFinishedPlayingProject();

private slots:
    void slotPlayProject();
    void slotPauseProject();
    void slotResumeProject();
    void slotStopProject();

};

#endif // WORKERPROJECT_H
