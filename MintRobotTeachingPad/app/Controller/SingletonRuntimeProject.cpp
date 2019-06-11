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

#include "SingletonRuntimeProject.h"

SingletonRuntimeProject::SingletonRuntimeProject() : QObject() {

    __pWorkerThread = new ThreadProjectPlayer();
    connect(this, SIGNAL(signalPlayProject()), __pWorkerThread, SLOT(slotPlayProject()));
    connect(this, SIGNAL(signalPauseProject()), __pWorkerThread, SLOT(slotPauseProject()));
    connect(this, SIGNAL(signalResumeProject()), __pWorkerThread, SLOT(slotResumeProject()));
    connect(this, SIGNAL(signalStopProject()), __pWorkerThread, SLOT(slotStopProject()));
}

SingletonRuntimeProject::~SingletonRuntimeProject() {

}

// Public
void SingletonRuntimeProject::setProjectModel(ModelProject* pModelProject) {
    __pModelProject = pModelProject;


}

ModelProject* SingletonRuntimeProject::getProjectModel() {
    return __pModelProject;
}

void SingletonRuntimeProject::setNotifier(InterfaceNodeStatusNotifier* pNotifier) {
    __pInterfaceNodeStatusNotifier = pNotifier;
}

void SingletonRuntimeProject::playProject() {

    // Map command interface before play
    QHash<QUuid, ModelNode*>::const_iterator iterator;
    ModelNode* pNode = nullptr;
    for (iterator = __pModelProject->getHashNode()->constBegin(); iterator != __pModelProject->getHashNode()->constEnd(); ++iterator) {
        pNode = iterator.value();
        pNode->setRobotCommandInterface(&SingletonComm::GetInstance());
    }

    __pWorkerThread->setProject(__pModelProject);
    __pWorkerThread->setNotifier(__pInterfaceNodeStatusNotifier);
    emit signalPlayProject();
}

void SingletonRuntimeProject::pauseProject() {
    emit signalPauseProject();
}

void SingletonRuntimeProject::resumeProject() {
    emit signalResumeProject();
}

void SingletonRuntimeProject::stopProject() {
    emit signalStopProject();
}
