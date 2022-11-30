/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/11/16
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/*
 *@Note
本实验为跑马灯实验
PA0接LED1 PA1接LED2

*/

#include"debug.h"
#include "led.h"


/* Global typedef */

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
        u8 i=0;
        u8 j=0;

        Delay_Init();   //延时函数初始化
        LED_Init();     //LED初始化
        while(1)
        {
            Delay_Ms(250); //延时250ms
            GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i==0) ? (i=Bit_SET):(i=Bit_RESET)); //设置PA0引脚状态为低电平
            Delay_Ms(250); //延时250ms
            GPIO_WriteBit(GPIOA, GPIO_Pin_1, (j==0) ? (j=Bit_SET):(j=Bit_RESET)); //设置PA1引脚状态为低电平
        }
}
