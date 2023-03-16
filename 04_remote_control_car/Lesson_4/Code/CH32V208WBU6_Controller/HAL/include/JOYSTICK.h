/********************************** (C) COPYRIGHT *******************************
 * File Name          : MOTOR.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2022/11/22
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * CONSTANTS
 */


/*********************************************************************
 * TYPEDEFS
 */

#define SERVO_DIRECTION_TURN_LEFT                   0       //舵机左转标志
#define SERVO_DIRECTION_TURN_RIGHT                  1       //舵机右转标志

#define MOTOR_ROTATE_FORWARD                        0       //小车前进
#define MOTOR_ROTATE_BACKWARD                       1       //小车后退

#define LEFT_JOYSTICK_LEFT_MAX                      4093    //左手柄水平方向上处于最左边
#define LEFT_JOYSTICK_MIDDLE                        2041    //左手柄水平方向上处于中间
#define LEFT_JOYSTICK_RIGHT_MAX                     2       //左手柄水平方向上处于最右边

#define RIGHT_JOYSTICK_FRONT_MAX                    2       //右手柄垂直方向上处于最前边
#define RIGHT_JOYSTICK_MIDDLE                       2035    //右手柄垂直方向上处于中间
#define RIGHT_JOYSTICK_BEHIND_MAX                   4093    //右手柄垂直方向上处于最后边

typedef struct
{
    uint8_t dir;        //左/右，上/下
    uint8_t per;        //变化比例
} JoystickPressPercentage_t;

typedef struct
{
    JoystickPressPercentage_t LeftJoystickState;
    JoystickPressPercentage_t RightJoystickState;
} JoystickState_t;

extern JoystickState_t JoystickState;      //手柄状态

/*********************************************************************
 * GLOBAL VARIABLES
 */

/**
 * @brief   Initializes ADC peripheral.
 */
void HAL_ADC1Init(void);

/**
 * @brief   Get Conversion Value.
 */
u16 HAL_ADCCalibrattion(s16 val);

/**
 * @brief   Get ADC1 value.
 */
u16 HAL_GetADC1Value(u8 ch);

/**
 * @brief   Get ADC1 average value.
 */
u16 HAL_GetADC1Average(u8 ch, u8 times);

/**
 * @brief   Initializes joysticks.
 */
void HAL_JoystickInit(void);

/**
 * @brief   Start/Stop collecting Joystick ADC.
 */
void HAL_JoystickPressPercentageGet(void);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
