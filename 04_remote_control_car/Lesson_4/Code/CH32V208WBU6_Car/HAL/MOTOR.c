/********************************** (C) COPYRIGHT *******************************
 * File Name          : MOTOR.c
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
MotorStatus_t MotorStatus;      //记录电机状态

/**************************************************************************************************
 *                                        FUNCTIONS - Local
 **************************************************************************************************/
/*********************************************************************
 * @fn      HAL_MotorStatusInit
 *
 * @brief   Initializes motor status structure.
 *
 * @param   none
 *
 * @return  none
 **************************************************************************************************/
void HAL_MotorStatusInit(void)
{
    MotorStatus.dir = MOTOR_ROTATE_STOP;
    MotorStatus.speed = 0;
}

/*********************************************************************
 * @fn      HAL_TIM1Init
 *
 * @brief   Initializes TIM1 output PWM.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 **************************************************************************************************/
void HAL_TIM1Init(u16 arr, u16 psc, u16 ccp)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE );

    //GPIO Init
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;          //PA8-IN1, PA9-IN3
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                 //复用推挽输出
    GPIO_Init( GPIOA, &GPIO_InitStructure );

    //TIM1 Init
    TIM_TimeBaseInitStructure.TIM_Period = arr;                     //自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  //预分频系数,计数器的时钟频率=APB2/(psc+1), APB2=120MHz
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //该应用中未使用
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);            //定时器1初始化

    //Channel1 Init
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //向上计数时,TIMx_CNT < TIMx_CH1CVR 输出有效电平，否则输出无效电平
    TIM_OCInitStructure.TIM_Pulse = ccp;                            //设置待装入捕获比较寄存器的比较值 TIMx_CH1CVR
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //输出极性，高电平有效
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;    //空闲状态时，OC1输出低电平
    TIM_OC1Init( TIM1, &TIM_OCInitStructure );                      //通道1初始化

    //Channel2 Init
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //向上计数时，TIMx_CNT < TIMx_CH2CVR 输出有效电平，否则输出无效电平
    TIM_OCInitStructure.TIM_Pulse = ccp;                            //设置待装入捕获比较寄存器的比较值 TIMx_CH2CVR
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //输出极性，高电平有效
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;    //空闲状态时，OC2输出低电平
    TIM_OC2Init( TIM1, &TIM_OCInitStructure );                      //通道2初始化

    TIM_CtrlPWMOutputs(TIM1, DISABLE );                             //主输出失能，PWM输出引脚为低电平，电机不转
    TIM_OC1PreloadConfig( TIM1, TIM_OCPreload_Disable );            //比较捕获寄存器1预装载失能,写入比较捕获寄存器中的值会立即起作用
    TIM_OC2PreloadConfig( TIM1, TIM_OCPreload_Disable );            //比较捕获寄存器2预装载失能,写入比较捕获寄存器中的值会立即起作用
    TIM_ARRPreloadConfig( TIM1, ENABLE );                           //自动重装载使能
    TIM_Cmd( TIM1, ENABLE );                                        //计数器使能
}

/*********************************************************************
 * @fn      HAL_MotorInit
 *
 * @brief   Initializes Motor control IO.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 **************************************************************************************************/
void HAL_MotorInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12;    //PA10-IN2, PA12-IN4
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //推挽输出，作为通用IO使用
    GPIO_Init( GPIOA, &GPIO_InitStructure );
    GPIO_ResetBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_12);           //默认电平为低电平

    HAL_TIM1Init(MOTOR_CONTROL_PWM_PERIOD, MOTOR_CONTROL_TIM_PRESCALER, MOTOR_SPEED_DUTY_CYCLE_SLOWEST); //定时器初始化

    HAL_MotorStatusInit(); //初始化电机状态
    PRINT("Motor init success\n");
}

/*********************************************************************
 * @fn      HAL_MotorStop
 *
 * @brief   Motor stop working.
 *
 * @param   none
 *
 * @return  none
 **************************************************************************************************/
void HAL_MotorStop(void)
{
    TIM_CtrlPWMOutputs(TIM1, DISABLE );                 //定时器1输出失能，进入Idle状态
    GPIO_ResetBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_12);   //IO输出低电平
    MotorStatus.dir = MOTOR_ROTATE_STOP;                //更新电机状态
    MotorStatus.speed = 0;
}

/*********************************************************************
 * @fn      HAL_MotorSpeedControl
 *
 * @brief   Control motor working mode.
 *
 * @param   dir - car move direction.
 *          per - speed change percentage, 0~100.
 *
 * @return  none
 **************************************************************************************************/
void HAL_MotorSpeedControl(uint8_t dir, uint8_t per)
{
    if(per > 100)   //比值大于100
    {
        return;
    }

    PRINT("motor dir:%d per:%d\n", dir, per);
    if(dir == MOTOR_ROTATE_FORWARD)
    {
        if(MotorStatus.dir == MOTOR_ROTATE_FORWARD)
        {
            if(per == MotorStatus.speed)
            {
                return;
            }
            else
            {
                TIM_CtrlPWMOutputs(TIM1, DISABLE );                 //定时器1输出失能，进入Idle状态
                TIM_SetCompare1(TIM1, (MOTOR_SPEED_DUTY_CYCLE_FASTEST - MOTOR_SPEED_DUTY_CYCLE_SLOWEST) * per / 100); //设置定时器1通道1比较值
                TIM_SetCompare2(TIM1, (MOTOR_SPEED_DUTY_CYCLE_FASTEST - MOTOR_SPEED_DUTY_CYCLE_SLOWEST) * per / 100); //设置定时器1通道2比较值
                TIM_CtrlPWMOutputs(TIM1, ENABLE );                  //定时器1输出使能
                MotorStatus.speed = per;                            //更新电机状态
            }
        }
        else
        {
            HAL_MotorStop();
            TIM_SetCompare1(TIM1, (MOTOR_SPEED_DUTY_CYCLE_FASTEST - MOTOR_SPEED_DUTY_CYCLE_SLOWEST) * per / 100); //设置定时器1通道1比较值
            TIM_SetCompare2(TIM1, (MOTOR_SPEED_DUTY_CYCLE_FASTEST - MOTOR_SPEED_DUTY_CYCLE_SLOWEST) * per / 100); //设置定时器1通道2比较值
            TIM_OC1PolarityConfig(TIM1, TIM_OCPolarity_High);   //设置定时器1通道1输出极性，高电平有效
            TIM_OC2PolarityConfig(TIM1, TIM_OCPolarity_High);   //设置定时器1通道2输出极性，高电平有效
            TIM_CtrlPWMOutputs(TIM1, ENABLE );                  //定时器1输出使能
            GPIO_ResetBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_12);   //IO输出低电平
            MotorStatus.dir = MOTOR_ROTATE_FORWARD;             //更新电机状态
            MotorStatus.speed = per;
        }
    }
    else
    {
        if(MotorStatus.dir == MOTOR_ROTATE_BACKWARD)
        {
            if(per == MotorStatus.speed)
            {
                return;
            }
            else
            {
                TIM_CtrlPWMOutputs(TIM1, DISABLE );                 //定时器1输出失能，进入Idle状态
                TIM_SetCompare1(TIM1, (MOTOR_SPEED_DUTY_CYCLE_FASTEST - MOTOR_SPEED_DUTY_CYCLE_SLOWEST) * per / 100); //设置定时器1通道1比较值
                TIM_SetCompare2(TIM1, (MOTOR_SPEED_DUTY_CYCLE_FASTEST - MOTOR_SPEED_DUTY_CYCLE_SLOWEST) * per / 100); //设置定时器1通道2比较值
                TIM_CtrlPWMOutputs(TIM1, ENABLE );                  //定时器1输出使能
                MotorStatus.speed = per;                            //更新电机状态
            }
        }
        else
        {
            HAL_MotorStop();
            TIM_SetCompare1(TIM1, (MOTOR_SPEED_DUTY_CYCLE_FASTEST - MOTOR_SPEED_DUTY_CYCLE_SLOWEST) * per / 100); //设置定时器1通道1比较值
            TIM_SetCompare2(TIM1, (MOTOR_SPEED_DUTY_CYCLE_FASTEST - MOTOR_SPEED_DUTY_CYCLE_SLOWEST) * per / 100); //设置定时器1通道1比较值
            TIM_OC1PolarityConfig(TIM1, TIM_OCPolarity_Low);    //设置定时器1通道1输出极性，低电平有效
            TIM_OC2PolarityConfig(TIM1, TIM_OCPolarity_Low);    //设置定时器1通道2输出极性，低电平有效
            TIM_CtrlPWMOutputs(TIM1, ENABLE );                  //定时器1输出使能
            GPIO_SetBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_12);     //IO输出高电平
            MotorStatus.dir = MOTOR_ROTATE_BACKWARD;            //更新电机状态
            MotorStatus.speed = per;
        }
    }
}

/******************************** endfile @ motor ******************************/
