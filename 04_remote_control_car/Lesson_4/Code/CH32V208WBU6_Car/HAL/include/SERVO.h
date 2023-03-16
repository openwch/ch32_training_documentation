/********************************** (C) COPYRIGHT *******************************
 * File Name          : SERVO.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2022/11/22
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
#ifndef __SERVO_H
#define __SERVO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */
#define SERVO_CONTROL_TIM_CLOCK                     100000                                              //舵机控制定时器2时钟100KHz
#define SERVO_CONTROL_TIM_PRESCALER                 (SystemCoreClock / SERVO_CONTROL_TIM_CLOCK - 1)     //定时器2的时钟分频系数,频率为100K,周期为0.01ms
#define SERVO_CONTROL_PWM_PERIOD                    (20 * SERVO_CONTROL_TIM_CLOCK / 1000)               //舵机控制的PWM周期固定为20ms

#define SERVO_DIRECTION_DUTY_CYCLE_MAX_LEFT         80     //舵机左满舵占空比计数(实测值)
#define SERVO_DIRECTION_DUTY_CYCLE_FORWARD          140     //舵机向正前方占空比计数（实测值）
#define SERVO_DIRECTION_DUTY_CYCLE_MAX_RIGHT        180      //舵机右满舵占空比计数（实测值）

#define SERVO_DIRECTION_TURN_LEFT                   0       //舵机左转标志
#define SERVO_DIRECTION_TURN_RIGHT                  1       //舵机右转标志

typedef struct
{
    uint8_t dir;        //运行方向
    uint8_t per;        //变化比例
} ControlCommand_t;

/*********************************************************************
 * GLOBAL VARIABLES
 */

/**
 * @brief   Initializes TIM2 output PWM.
 */
void HAL_TIM2Init(u16 arr, u16 psc, u16 ccp);

/**
 * @brief   Servo PWM Init.
 */
void HAL_ServoInit(void);

/**
 * @brief   Servo PWM Output State.
 */
void HAL_ServoState(uint8_t en);

/**
 * @brief   Servo turn forward.
 */
void HAL_ServoDirectionTurnForward(void);

/**
 * @brief   Change servo direction.
 */
void HAL_ServoDirectionControl(uint8_t dir, uint8_t per);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
