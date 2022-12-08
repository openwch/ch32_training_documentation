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
单通道的DAC输出三角波

*/

#include "debug.h"


/* Global typedef */

/* Global define */

/* Global Variable */

void dac_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    DAC_InitTypeDef  DAC_InitType = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; /* 模拟输入 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_4);

    /* 软件触发 */
    DAC_InitType.DAC_Trigger = DAC_Trigger_Software;

    /* 使用三角波发生器 */
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;

    /* 设置三角波幅值 */
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;

    /* 使能输出Buffer，减少输出阻抗  */
    DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Enable;

    DAC_Init(DAC_Channel_1, &DAC_InitType);
    DAC_Cmd(DAC_Channel_1, ENABLE);
}


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);

	dac_init();

	while(1)
    {
	    /* DAC_SWTR置位，启动软件触发，1个APB1时钟周期后，
	     *  将DAC_xDH寄存器的数据送入 DAC_DORx寄存器，DAC_SWTR将硬件清0
	     *  */
	    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
	    __asm volatile ("nop");
	}
}





