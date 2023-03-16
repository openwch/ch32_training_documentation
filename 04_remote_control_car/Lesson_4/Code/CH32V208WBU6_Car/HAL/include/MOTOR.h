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
#ifndef __MOTOR_H
#define __MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * CONSTANTS
 */
#define MOTOR_CONTROL_TIM_CLOCK                     2500000                                             //电机控制定时器1时钟2500KHz
#define MOTOR_CONTROL_TIM_PRESCALER                 (SystemCoreClock / MOTOR_CONTROL_TIM_CLOCK - 1)     //定时器1的时钟分频系数,频率为2500K,周期为0.04us
#define MOTOR_CONTROL_PWM_PERIOD                    (40 * MOTOR_CONTROL_TIM_CLOCK / 1000000)            //电机控制的PWM周期固定为40us

#define MOTOR_SPEED_DUTY_CYCLE_FASTEST              100     //电机转速最快占空比计数
#define MOTOR_SPEED_DUTY_CYCLE_SLOWEST              0       //电机转速最慢占空比计数

#define MOTOR_ROTATE_FORWARD                        0       //小车前进
#define MOTOR_ROTATE_BACKWARD                       1       //小车后退
#define MOTOR_ROTATE_STOP                           2       //小车停止

/*********************************************************************
 * TYPEDEFS
 */
typedef struct
{
    uint8_t dir;            //小车运行方向
    uint8_t speed;          //小车运行速度，即占空比比例
} MotorStatus_t;


/*********************************************************************
 * GLOBAL VARIABLES
 */

/**
 * @brief   Initializes motor status structure.
 */
void HAL_MotorStatusInit(void);

/**
 * @brief   Initializes TIM1 output PWM.
 */
void HAL_TIM1Init(u16 arr, u16 psc, u16 ccp);

/**
 * @brief   Initializes Motor control IO.
 */
void HAL_MotorInit(void);

/**
 * @brief   Motor stop working.
 */
void HAL_MotorStop(void);

/**
 * @brief   Control motor working mode.
 */
void HAL_MotorSpeedControl(uint8_t dir, uint8_t per);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
