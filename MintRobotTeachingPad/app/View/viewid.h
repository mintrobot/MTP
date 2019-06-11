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

#ifndef VIEWID_H
#define VIEWID_H

//==================================================
//======= HOME
//==================================================
#define VIEW_ID_MAIN_ITEM_RUN_PROGRAM     0
#define VIEW_ID_MAIN_ITEM_NEW_PROJECT     1
#define VIEW_ID_MAIN_ITEM_OPEN_PROJECT    2
#define VIEW_ID_MAIN_ITEM_ROBOT_SETTING   3
#define VIEW_ID_MAIN_ITEM_LOG             4
#define VIEW_ID_MAIN_ITEM_NET_SETTING     5
#define VIEW_ID_MAIN_ITEM_EXIT            6



//==================================================
//======= PROJECT EDITOR
//==================================================
#define PROJECT_EDITOR_MENU_SAVE_PROJECT           11
#define PROJECT_EDITOR_MENU_LOAD_PROJECT           12
#define PROJECT_EDITOR_MENU_PLAY_PROJECT           13

#define PROJECT_EDITOR_BUTTON_ADD_NEW_VARIABLE      0
#define PROJECT_EDITOR_BUTTON_ADD_NEW_POSITION      1
#define PROJECT_EDITOR_BUTTON_MOVE_ROBOT_JOINT      2
#define PROJECT_EDITOR_BUTTON_MOVE_ROBOT_TCP        3
#define PROJECT_EDITOR_BUTTON_IF                    4
#define PROJECT_EDITOR_BUTTON_ELSEIF                5
#define PROJECT_EDITOR_BUTTON_ELSE                  6
#define PROJECT_EDITOR_BUTTON_LOOP                  7
#define PROJECT_EDITOR_BUTTON_DELAY                 8
#define PROJECT_EDITOR_BUTTON_SET_DIGITAL_OUT       9
#define PROJECT_DEITOR_BUTTON_WAIT_DIGITAL_IN       10


#define PROJECT_EDITOR_DIALOG_ASSIGN_VARIABLE       1
#define PROJECT_EDITOR_DIALOG_ASSIGN_POSITION       2
#define PROJECT_EDITOR_DIALOG_MOVE_ROBOT      3
#define PROJECT_EDITOR_DIALOG_MOVE_ROBOT_TCP        4
#define PROJECT_EDITOR_DIALOG_CONDITIONAL           5
#define PROJECT_EDITOR_DIALOG_DELAY                 6
#define PROJECT_EDITOR_DIALOG_DIGITAL_INOUT         7

//==================================================
//======= Project Editor Menu IDs
//==================================================
#define VIEW_ID_MAIN_MENU_SYSTEM         11
#define VIEW_ID_MAIN_MENU_PROJECT        12
#define VIEW_ID_MAIN_MENU_POSITION        13
#define VIEW_ID_MAIN_MENU_ROBOT           14
#define VIEW_ID_MAIN_MENU_FLOWCONTROL     15
#define VIEW_ID_MAIN_MENU_IO              16

//==================================================
//======= Edit_Menu_Title
//==================================================
#define VIEW_ID_MAIN_MENU_PROJECT_CLOSE_EDITOR         200
#define VIEW_ID_MAIN_MENU_PROJECT_RUN           201
#define VIEW_ID_MAIN_MENU_PROJECT_PAUSE          202
#define VIEW_ID_MAIN_MENU_PROJECT_RESUME         203
#define VIEW_ID_MAIN_MENU_PROJECT_STOP           204
#define VIEW_ID_MAIN_MENU_PROJECT_SAVE           205
#define VIEW_ID_MAIN_MENU_PROJECT_DELETE         206

//==================================================
//======= Edit_Node
//==================================================
#define VIEW_ID_MAIN_MENU_ITEM_DE_VARIABLE      301
#define VIEW_ID_MAIN_MENU_ITEM_SET_VARIABLE     302
#define VIEW_ID_MAIN_MENU_ITEM_POSITION         303
#define VIEW_ID_MAIN_MENU_ITEM_MOVEJ_ABS        304
#define VIEW_ID_MAIN_MENU_ITEM_MOVEL_ABS        305
#define VIEW_ID_MAIN_MENU_ITEM_MOVEJ_REL        306
#define VIEW_ID_MAIN_MENU_ITEM_MOVEL_REL        307
#define VIEW_ID_MAIN_MENU_ITEM_WAIT             308
#define VIEW_ID_MAIN_MENU_ITEM_IF               309
#define VIEW_ID_MAIN_MENU_ITEM_ELSE_IF          310
#define VIEW_ID_MAIN_MENU_ITEM_ELSE             311
#define VIEW_ID_MAIN_MENU_ITEM_WHILE            312
#define VIEW_ID_MAIN_MENU_ITEM_SET_VALUE        313
#define VEIW_ID_MAIN_MENU_ITEM_SET_DIGITAL_OUT       314
#define VIEW_ID_MAIN_MENU_ITEM_GET_INPUT        315
#define VIEW_ID_MAIN_MENU_ITEM_WAIT_DGITAL_IN   316

//==================================================
//======= KeyPad/Keyboard
//==================================================
#define VIEW_ID_KEYPAD_PLUS             28
#define VIEW_ID_KEYPAD_MINUS            29
#define VIEW_ID_KEYPAD_CLEAR            30
#define VIEW_ID_KEYPAD_NUM_DOT          31
#define VIEW_ID_KEYPAD_NUM_0            32
#define VIEW_ID_KEYPAD_NUM_1            33
#define VIEW_ID_KEYPAD_NUM_2            34
#define VIEW_ID_KEYPAD_NUM_3            35
#define VIEW_ID_KEYPAD_NUM_4            36
#define VIEW_ID_KEYPAD_NUM_5            37
#define VIEW_ID_KEYPAD_NUM_6            38
#define VIEW_ID_KEYPAD_NUM_7            39
#define VIEW_ID_KEYPAD_NUM_8            40
#define VIEW_ID_KEYPAD_NUM_9            41

#define VIEW_ID_KEYBOARD_KEY_A          42
#define VIEW_ID_KEYBOARD_KEY_B          43
#define VIEW_ID_KEYBOARD_KEY_C          44
#define VIEW_ID_KEYBOARD_KEY_D          45
#define VIEW_ID_KEYBOARD_KEY_E          46
#define VIEW_ID_KEYBOARD_KEY_F          47
#define VIEW_ID_KEYBOARD_KEY_G          48

#define VIEW_ID_KEYBOARD_KEY_H          49
#define VIEW_ID_KEYBOARD_KEY_I          50
#define VIEW_ID_KEYBOARD_KEY_J          51
#define VIEW_ID_KEYBOARD_KEY_K          52
#define VIEW_ID_KEYBOARD_KEY_L          53
#define VIEW_ID_KEYBOARD_KEY_M          54
#define VIEW_ID_KEYBOARD_KEY_N          55

#define VIEW_ID_KEYBOARD_KEY_O          56
#define VIEW_ID_KEYBOARD_KEY_P          57
#define VIEW_ID_KEYBOARD_KEY_Q          58
#define VIEW_ID_KEYBOARD_KEY_R          59
#define VIEW_ID_KEYBOARD_KEY_S          60
#define VIEW_ID_KEYBOARD_KEY_T          61
#define VIEW_ID_KEYBOARD_KEY_U          62

#define VIEW_ID_KEYBOARD_KEY_V          63
#define VIEW_ID_KEYBOARD_KEY_W          64
#define VIEW_ID_KEYBOARD_KEY_X          65
#define VIEW_ID_KEYBOARD_KEY_Y          66
#define VIEW_ID_KEYBOARD_KEY_Z          67

#define VIEW_ID_KEYBOARD_CAPSLOCK       68
#define VIEW_ID_KEYBOARD_BACKSPACE      69
#define VIEW_ID_KEYBOARD_SIGN_1         70
#define VIEW_ID_KEYBOARD_SIGN_2         71
#define VIEW_ID_KEYBOARD_SIGN_3         72
#define VIEW_ID_KEYBOARD_SIGN_4         73
#define VIEW_ID_KEYBOARD_SIGN_5         74
#define VIEW_ID_KEYBOARD_SIGN_6         75

#define VIEW_ID_KEYBOARD_OPERATOR_1     76
#define VIEW_ID_KEYBOARD_OPERATOR_2     77
#define VIEW_ID_KEYBOARD_OPERATOR_3     78
#define VIEW_ID_KEYBOARD_OPERATOR_4     79
#define VIEW_ID_KEYBOARD_OPERATOR_5     80

#define VIEW_ID_KEYBOARD_DOT            81
#define VIEW_ID_KEYBOARD_BRACET_OPEN    82
#define VIEW_ID_KEYBOARD_BRACET_CLOSE   83
#define VIEW_ID_KEYBOARD_UNDERBAR       84
#define VIEW_ID_KEYBOARD_BAR            85
#define VIEW_ID_KEYBOARD_SPACE          86

//==================================================
//======= Controller
//==================================================
#define VIEW_ID_MOVEJ_3_1               100
#define VEIW_ID_MOVEJ_3_2               101
#define VIEW_ID_MOVEJ_3_3               102

#define VIEW_ID_OK                      200
#define VIEW_ID_CANCEL                  201
#define VIEW_ID_DELETE                  202

#define VIEW_ID_CONTROLLER              300
#define VIEW_ID_MOVETOOL_X_PLUS         0b00000010
#define VIEW_ID_MOVETOOL_X_MINUS        0b00000011
#define VIEW_ID_MOVETOOL_Y_PLUS         0b00000100
#define VIEW_ID_MOVETOOL_Y_MINUS        0b00000101
#define VIEW_ID_MOVETOOL_Z_PLUS         0b00001000
#define VIEW_ID_MOVETOOL_Z_MINUS        0b00001001

#define VIEW_ID_MOVETOOL_ROLL_PLUS      307
#define VIEW_ID_MOVETOOL_ROLL_MINUS     308
#define VIEW_ID_MOVETOOL_YAW_PLUS       309
#define VIEW_ID_MOVETOOL_YAW_MINUS      310
#define VIEW_ID_MOVETOOL_PITCH_PLUS     311
#define VIEW_ID_MOVETOOL_PITCH_MINUS    312
#define VIEW_ID_MOVETOOL_ROLL_PLUS_TCP  313
#define VIEW_ID_MOVETOOL_ROLL_MINUS_TCP 314
#define VIEW_ID_MOVETOOL_YAW_PLUS_TCP   315
#define VIEW_ID_MOVETOOL_YAW_MINUS_TCP  316
#define VIEW_ID_MOVETOOL_PITCH_PLUS_TCP 317
#define VIEW_ID_MOVETOOL_PITCH_MINUS_TCP 318
//==================================================
#define VIEW_ID_IO_CONTROLLER          400

#define VIEW_ID_IO_IN_O_PIN             401
#define VIEW_ID_IO_IN_1_PIN             402
#define VIEW_ID_IO_IN_2_PIN             403
#define VIEW_ID_IO_IN_3_PIN             404
#define VIEW_ID_IO_IN_4_PIN             405
#define VIEW_ID_IO_IN_5_PIN             406
#define VIEW_ID_IO_IN_6_PIN             407
#define VIEW_ID_IO_IN_7_PIN             408

#define VIEW_ID_IO_OUT_O_PIN            409
#define VIEW_ID_IO_OUT_1_PIN            410
#define VIEW_ID_IO_OUT_2_PIN            411
#define VIEW_ID_IO_OUT_3_PIN            412
#define VIEW_ID_IO_OUT_4_PIN            413
#define VIEW_ID_IO_OUT_5_PIN            414
#define VIEW_ID_IO_OUT_6_PIN            415
#define VIEW_ID_IO_OUT_7_PIN            416





#endif // VIEWID_H
