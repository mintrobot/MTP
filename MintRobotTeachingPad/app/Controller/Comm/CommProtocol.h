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

#ifndef COMMPROTOCOL_H
#define COMMPROTOCOL_H

//--- COMMON VARIALABLE
#define START_PACKET                                   0x77
#define OPERATION_TYPE_IMMEDIATE_EXECUTION             0x01
#define OPERATION_TYPE_STOP                            0x06

//--- ROBOT COMMAND LIST
//--- COMMAND SERVER
#define COMMAND_MOVE_JOINT_ABS          0x01
#define COMMAND_MOVE_JOINT_REL          0x02
#define COMMAND_MOVE_TCP_LINEAR_ABS     0x03
#define COMMAND_MOVE_TCP_LINEAR_REL     0x04
#define COMMAND_JOG_JOINT               0x05
#define COMMAND_JOG_TCP                 0x06
#define COMMAND_START_DIRECT_TEACING    0x07
#define COMMAND_SET_DIGITAL_OUT         0x08
#define COMMAND_WAIT_DIGITAL_IN         0x09
#define COMMAND_SET_TCP_OFFSET          0x0A
#define COMMAND_SET_WORLD_COORDINATE    0x0B    // DO NOT USE
#define COMMAND_SET_TIME_UNIT           0x0C    // DO NOT USE
#define COMMAND_SERVO_ON_OFF            0x0D
#define COMMAND_BRAKE_ON_OFF            0x0E
#define COMMAND_ACIVATE_ROBOT           0x0F

//--- STATUS SERVER
#define COMMAND_REQUEST_STATUS_ALL      0x01


//--- PACKET STRUCTURES
//--- Command Server
// MOVE JOINT ABS
#pragma pack(push, 1)
typedef struct move_joint_abs {
    char cmd = COMMAND_MOVE_JOINT_ABS;
    double vecJoint[6] = {0,};
    double vMax = 0;
    double aMax = 0;
} MOVE_JOINT_ABS;
#pragma pack(pop)


// MOVE JOINT REL
#pragma pack(push, 1)
typedef struct move_joint_rel {
    char cmd = COMMAND_MOVE_JOINT_REL;
    double vecJoint[6] = {0,};
    double vMax = 0;
    double aMax = 0;
} MOVE_JOINT_REL;
#pragma pack(pop)


// MOVE TCP LINEAR ABS
#pragma pack(push, 1)
typedef struct move_tcp_linear_abs {
    char cmd = COMMAND_MOVE_TCP_LINEAR_ABS;
    double vecTCP[6] = {0,};
    double vMax = 0;
    double aMax = 0;
} MOVE_TCP_LINEAR_ABS;
#pragma pack(pop)


// MOVE TCP LINEAR REL
#pragma pack(push, 1)
typedef struct move_tcp_linear_rel {

    char cmd = COMMAND_MOVE_TCP_LINEAR_REL;
    double vecTCP[6] = {0,};
    double vMax = 0;
    double aMax = 0;
} MOVE_TCP_LINEAR_REL;
#pragma pack(pop)


// JOG JOINT
#pragma pack(push, 1)
typedef struct jog_joint {
    char cmd = COMMAND_JOG_JOINT;
    char index = 0;
    char direction = 0;
    double vMax = 0;
    double aMax = 0;
} JOG_JOINT;
#pragma pack(pop)


// JOG TCP
#pragma pack(push, 1)
typedef struct jog_tcp {
    char cmd = COMMAND_JOG_TCP;
    char type = 0;
    char axis = 0;
    char direction = 0;
    double vMax = 0;
    double aMax = 0;
} JOG_TCP;
#pragma pack(pop)


// START DIRECT TEACHING
#pragma pack(push, 1)
typedef struct start_direct_teaching {
    char cmd = COMMAND_START_DIRECT_TEACING;
} START_DIRECT_TEACHING;
#pragma pack(pop)


// SET DIGITAL OUT
#pragma pack(push, 1)
typedef struct set_digital_out {
    char cmd = COMMAND_SET_DIGITAL_OUT;
    char index = 0;
    char value = 0;
} SET_DIGITAL_OUT;
#pragma pack(pop)


// WAIT DIGITAL IN
#pragma pack(push, 1)
typedef struct wait_digital_in {
    char cmd = COMMAND_WAIT_DIGITAL_IN;
    char index = 0;
    char value = 0;
} WAIT_DIGITAL_IN;
#pragma pack(pop)


// SET TCP OFFSET
#pragma pack(push, 1)
typedef struct set_tcp_offset {
    char cmd = COMMAND_SET_TCP_OFFSET;
    double vecOffset[3];
    double vecCenter[3];
    double weight = 0;
} SET_TCP_OFFSET;
#pragma pack(pop)


// SERVO ON OFF
#pragma pack(push, 1)
typedef struct servo_on_off {
    char cmd = COMMAND_SERVO_ON_OFF;
    unsigned char flagStatus;    // 0 : 0ff, 1 : 0n
} SERVO_ON_OFF;
#pragma pack(pop)


// BRAKE ON OFF
#pragma pack(push, 1)
typedef struct brake_on_off {
    char cmd = COMMAND_BRAKE_ON_OFF;
    unsigned char flagStatus;    // 0 : 0ff, 1 : 0n
} BRAKE_ON_OFF;
#pragma pack(pop)


// ACTIVE ROBOT
#pragma pack(push, 1)
typedef struct activate_robot {
    char cmd = COMMAND_ACIVATE_ROBOT;
    unsigned char flagStatus;    // 0 : Deactivate, 1 : Activate
} ACTIVATE_ROBOT;
#pragma pack(pop)



//--- Status Server
// STATUS REQUEST
#pragma pack(push, 1)
typedef struct status_request_all {
    char cmd[2] = {0x01, COMMAND_REQUEST_STATUS_ALL};
} STATUS_REQUEST_ALL;
#pragma pack(pop)


// STATUS RECEIVE PACKET
#pragma pack(push, 1)
typedef struct status_receive_all {
    char statusCommandRunning;
    char indexUserCommand[2];
    char statusRobotRunning;
    char statusController;
    double vectorJoint[6];
    double vectorTCP[6];
    char digitalIn[8];
    char digitalOut[8];
    char statusError;
} STATUS_RECEIVE_ALL;
#pragma pack(pop)

#endif // COMMPROTOCOL_H
