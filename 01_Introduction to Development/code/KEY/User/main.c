/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/*
 *@Note
 按键控制LED灯实验
 KEY控制LED灯亮灭，串口打印 i=0表示LED灯亮，i=1表示LED灯灭。
*/
#include "debug.h"
#include "led.h"
#include "key.h"

int main(void)
{
    u8 t=0;
    static u8 i=1;

    USART_Printf_Init(115200);
    Delay_Init();   //延时函数初始化
    LED_Init();     //LED初始化
    KEY_Init();     //按键初始化

    printf("SystemClk:%d\r\n",SystemCoreClock);

    while(1)
    {
        t=KEY_Scan(0);      //得到键值

        switch(t)
        {
            case KEY_PRESS:
                GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i==0) ? (i=Bit_SET):(i=Bit_RESET));
                printf("i=%d\n",i);
                break;
            default:
                Delay_Ms(10);
        }
    }
}

