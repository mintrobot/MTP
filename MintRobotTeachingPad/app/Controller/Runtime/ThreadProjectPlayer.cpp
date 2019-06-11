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

#include "ThreadProjectPlayer.h"

// Constructor
ThreadProjectPlayer::ThreadProjectPlayer() : QThread () {

}

ThreadProjectPlayer::~ThreadProjectPlayer() {
    if (__pModelProject != nullptr) {
        delete __pModelProject;
    }
    if (__pNotifier != nullptr) {
        delete __pNotifier;
    }
}

// Public
void ThreadProjectPlayer::setProject(ModelProject* pModelProject) {
    __pModelProject = pModelProject;
}

void ThreadProjectPlayer::setNotifier(InterfaceNodeStatusNotifier* pNotifier) {
    __pNotifier = pNotifier;
    connect(this, SIGNAL(signalRunningNode(QUuid)), __pNotifier, SLOT(slotOnRunningNode(QUuid)));
    connect(this, SIGNAL(signalFinishedNode(QUuid)), __pNotifier, SLOT(slotOnFinishedNode(QUuid)));
    connect(this, SIGNAL(signalErrorOnNode(QUuid)), __pNotifier, SLOT(slotOnErrorNode(QUuid)));
    connect(this, SIGNAL(signalFinishedPlayingProject()), __pNotifier, SLOT(slotOnFinishedPlayingProject()));
}


// Private
void ThreadProjectPlayer::run() {
    ModelNode* pNode = __pModelProject->getFirstNode();
    QUuid nextNodeID = nullptr;

    while(!__flagStop) {
        emit signalRunningNode(pNode->getNodeID());
        try {
            nextNodeID = pNode->execute();
            if (__flagPause) {
                while(__flagPause) {
                    msleep(10);
                }
            }
            emit signalFinishedNode(pNode->getNodeID());
        }
        catch (...) {
            emit signalErrorOnNode(pNode->getNodeID());
        }
        if (nextNodeID == nullptr) {
            __flagStop = true;
        }
        else {
           pNode =  __pModelProject->getNode(nextNodeID);
           if (pNode == nullptr) {
               __flagStop = true;
           }
        }
    }
    emit signalFinishedPlayingProject();
}

// Slots
void ThreadProjectPlayer::slotPlayProject() {
    __mutexFlags.lock();
    __flagStop = false;
    __flagPause = false;
    __mutexFlags.unlock();
    this->start();
}

void ThreadProjectPlayer::slotPauseProject() {
    __mutexFlags.lock();
    __flagPause = true;
    __mutexFlags.unlock();
}

void ThreadProjectPlayer::slotResumeProject() {
    __mutexFlags.lock();
    __flagPause = false;
    __mutexFlags.unlock();
}

void ThreadProjectPlayer::slotStopProject() {
    __mutexFlags.lock();
    __flagStop = true;
    __mutexFlags.unlock();
}
