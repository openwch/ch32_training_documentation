/********************************** (C) COPYRIGHT *******************************
 * File Name          : SERVO.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2022/11/22
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include "HAL.h"

/**************************************************************************************************
 *                                        GLOBAL VARIABLES
 **************************************************************************************************/


/**************************************************************************************************
 *                                        FUNCTIONS - Local
 **************************************************************************************************/


/**************************************************************************************************
 * @fn      HAL_TIM2Init
 *
 * @brief   Initializes TIM2 output PWM.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 **************************************************************************************************/
void HAL_TIM2Init(u16 arr, u16 psc, u16 ccp)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //GPIO Init
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                       //PA0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                 //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //TIM2 Init
    TIM_TimeBaseInitStructure.TIM_Period = arr;                     //自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  //预分频系数, 计数器的时钟频率=APB1/(psc+1), APB1=120MHz
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //该应用中未使用到
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStructure);            //定时器2初始化

    //Channel1 Init
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //向上计数时, TIMx_CNT < TIMx_CH1CVR 输出有效电平，否则输出无效电平
    TIM_OCInitStructure.TIM_Pulse = ccp;                            //设置待装入捕获比较寄存器的比较值 TIMx_CH1CVR
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //高电平有效
    TIM_OC1Init( TIM2, &TIM_OCInitStructure );                      //通道1初始化

    TIM_OC1PreloadConfig( TIM2, TIM_OCPreload_Disable );            //比较捕获寄存器1预装载失能,即写入比较捕获寄存器中的值会立即起作用
    TIM_ARRPreloadConfig( TIM2, ENABLE );                           //自动重装载使能
    TIM_Cmd( TIM2, ENABLE );                                        //计数器使能
}

/**************************************************************************************************
 * @fn      HAL_ServoInit
 *
 * @brief   Servo PWM Init.
 *
 * @param   none
 *
 * @return  none
 **************************************************************************************************/
void HAL_ServoInit(void)
{
    HAL_TIM2Init(SERVO_CONTROL_PWM_PERIOD, SERVO_CONTROL_TIM_PRESCALER, 0); //定时器周期：0.01ms,默认小车处于休眠模式,定时器持续输出低电平
    PRINT("Servo init success\n");
}

/**************************************************************************************************
 * @fn      HAL_ServoState
 *
 * @brief   Servo PWM Output State.
 *
 * @param   en - Enable/Disable
 *
 * @return  none
 **************************************************************************************************/
void HAL_ServoState(uint8_t en)
{
    if(en == ENABLE)
    {
        TIM_SetCompare1(TIM2, SERVO_DIRECTION_DUTY_CYCLE_FORWARD); //舵机向正前
    }
    else
    {
        TIM_SetCompare1(TIM2, 0); //释放舵机，定时器持续输出低电平
    }
}

/*********************************************************************
 * @fn      HAL_ServoDirectionTurnForward
 *
 * @brief   Servo turn forward.
 *
 * @param   none
 *
 * @return  none
 **************************************************************************************************/
void HAL_ServoDirectionTurnForward(void)
{
    TIM_SetCompare1(TIM2, SERVO_DIRECTION_DUTY_CYCLE_FORWARD); //舵机向正前
}

/*********************************************************************
 * @fn      HAL_ServoDirectionControl
 *
 * @brief   Change servo direction.
 *
 * @param   dir - turn left or turn right, 0: left, 1: right
 *          per - direction change percentage, 0~100
 *
 * @return  none
 **************************************************************************************************/
void HAL_ServoDirectionControl(uint8_t dir, uint8_t per)
{
    uint16_t duty_cycle;

    if(per > 100) //百分比大于100
    {
        return;
    }

    if(dir == SERVO_DIRECTION_TURN_LEFT) //左转
    {
        duty_cycle = SERVO_DIRECTION_DUTY_CYCLE_FORWARD - (SERVO_DIRECTION_DUTY_CYCLE_FORWARD - SERVO_DIRECTION_DUTY_CYCLE_MAX_LEFT) * per / 100;
    }
    else //右转
    {
        duty_cycle = SERVO_DIRECTION_DUTY_CYCLE_FORWARD + (SERVO_DIRECTION_DUTY_CYCLE_MAX_RIGHT - SERVO_DIRECTION_DUTY_CYCLE_FORWARD) * per / 100;
    }

    PRINT("Servo dir:%d | per:%d | duty_cycle:%d\n", dir, per, duty_cycle);
    TIM_SetCompare1(TIM2, duty_cycle); //设置定时2通道1的比较值
}

/******************************** endfile @ servo ******************************/
