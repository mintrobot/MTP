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

#include "BlockingTCPSocket.h"

//--- Constructor
BlockingTCPSocket::BlockingTCPSocket(QObject* parent) : QTcpSocket(parent){

}

BlockingTCPSocket::~BlockingTCPSocket() {

}

//--- Public
int BlockingTCPSocket::blockingRead(char* buffer, const int length, unsigned long timeout) {
    int res = -1;
    unsigned long elasedTime = 0;
    try {
        while(bytesAvailable() < length) {
            waitForReadyRead(1);
            elasedTime += 10;
            if (elasedTime > timeout) {
                break;
            }
        }
        res = static_cast<int>(read(buffer, length));
    }
    catch (...) {

    }
    return res;
}

int BlockingTCPSocket::blockingWrite(char* buffer, int length, unsigned long timeout) {
    try {
        write(buffer, length);
        if (!waitForBytesWritten(static_cast<int>(timeout))) {
            qDebug() << this << "Socket Transmission error";
            return -1;
        }
        else {
            return length;
        }
    }
    catch(...) {

    }
    return -1;
}

int BlockingTCPSocket::slotBlockingWrite(char* buffer, int length) {
    qDebug() << "est";
    return blockingWrite(buffer, length);
}

int BlockingTCPSocket::slotBlockingRead(char* buffer, int length) {
    return blockingRead(buffer, length);
}
