/********************************** (C) COPYRIGHT *******************************
 * File Name          : central.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/11/12
 * Description        : 观察应用主函数及任务系统初始化
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef CENTRAL_H
#define CENTRAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

// Simple BLE Observer Task Events
#define START_DEVICE_EVT                    0x0001
#define START_DISCOVERY_EVT                 0x0002
#define START_SCAN_EVT                      0x0004
#define START_SVC_DISCOVERY_EVT             0x0008
#define START_PARAM_UPDATE_EVT              0x0010
#define START_PHY_UPDATE_EVT                0x0020
#define START_READ_OR_WRITE_EVT             0x0040
#define START_WRITE_CCCD_EVT                0x0080
#define START_READ_RSSI_EVT                 0x0100
#define ESTABLISH_LINK_TIMEOUT_EVT          0x0200
#define START_WRITE_CHAR1_EVT               0x0400
#define START_WRITE_CHAR3_EVT               0x0800

//控制命令的帧长度
#define CEN_COMMAND_BASIC_FRAME_LEN         0x08
#define CEN_COMMAND_SLEEP_FRAME_LEN         0x09
#define CEN_COMMAND_CONTROL_FRAME_LEN       0x0A

//控制命令的帧头/帧尾
#define CEN_COMMAND_FRAME_START             0x55
#define CEN_COMMAND_FRAME_END               0xAA

//控制命令类型
#define CEN_COMMAND_TYPE_REQUEST            0x00
#define CEN_COMMAND_TYPE_RESPONSE           0x80

//控制命令定义
#define CEN_COMMAND_SLEEP_ENABLE            0x01
#define CEN_COMMAND_DRIVE_CONTROL           0x02


extern uint8_t centralTaskId; // Task ID for internal task/event processing

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the BLE Application
 */
extern void Central_Init(void);

/*
 * Task Event Processor for the BLE Application
 */
extern uint16_t Central_ProcessEvent(uint8_t task_id, uint16_t events);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
