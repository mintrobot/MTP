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

#ifndef THREADCONNECTIONHANDLER_H
#define THREADCONNECTIONHANDLER_H

#include <QThread>
#include <QTcpSocket>
#include <QMutex>

#include "ConfigureComm.h"
#include "BlockingTCPSocket.h"

class WorkerConnectionHandler : public QObject
{
    Q_OBJECT

public:
    explicit WorkerConnectionHandler(QObject *parent = nullptr);
    virtual ~WorkerConnectionHandler();

    void setSocket(BlockingTCPSocket* pSocketCommand, BlockingTCPSocket* pSocketStatus);
    void setSocketControlThread(QThread* pThreadSocketController);
    void receiveSocketFromSocketController();
    void tossSocketToSocketController();

    void changeIPAddress(QString IPAddress);
    void setActivation(bool activation);

private:
    // Connection
    QString __IPAddress = DEFAULT_TARGET_IP;
    BlockingTCPSocket* __pSocketCommand;
    BlockingTCPSocket* __pSocketStatus;
    QThread* __pThreadSocketController;
    void __resetConnection();

    // Connection handling variables
    int __connectionWaitTimeout = DEFAULT_CHECK_TIMEOUT_MS;
    bool __flagConnectionCommandServer = false;
    bool __flagConnectionStatusServer = false;
    bool __flagEstablishedConnection = false;
    bool __handShake();

    // Threading
    QMutex __mutexOperation;
    bool __flagAuthority = false;
    bool __flagOperation = true;
    bool __flagStop = false;


signals:
    void signalReadyToCommunicate();


private slots:
    void process();
    void slotResetConnection();

};

#endif // THREADCONNECTIONHANDLER_H
