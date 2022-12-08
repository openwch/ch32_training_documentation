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
#define DAC_DMA_LENGTH 64

/* Global Variable */
uint16_t DACDataBuffer[DAC_DMA_LENGTH]={2048,2248,2447,2642,2831,3013,3185,3347,3496,3631,3750,3854,3940,4007,4056,4086,
                         4095,4086,4056,4007,3940,3854,3750,3631,3496,3347,3185,3013,2831,2642,2447,2248,
                         2048,1847,1648,1453,1264,1082,910 ,748 ,599 ,464 ,345 ,241 ,155 ,88  ,39  ,9   ,
                         0   ,9   ,39  ,88  ,155 ,241 ,345 ,464 ,599 ,748 ,910 ,1082,1264,1453,1648,1847};



void timer8_init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM8, ENABLE );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter =  0x00;
    TIM_TimeBaseInit( TIM8, &TIM_TimeBaseInitStructure);

    TIM_SelectOutputTrigger(TIM8, TIM_TRGOSource_Update);
    TIM_Cmd(TIM8, ENABLE);
}

void dac_dma_init(void)
{
    DMA_InitTypeDef DMA_InitStructure={0};
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    DMA_StructInit( &DMA_InitStructure);
    /* Note:DAC1--->DMA2.CH3   DAC2--->DMA2.CH4 */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(DAC->R12BDHR1);
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&DACDataBuffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = DAC_DMA_LENGTH;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    DMA_Init(DMA2_Channel3, &DMA_InitStructure);
    DMA_Cmd(DMA2_Channel3, ENABLE);
}

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

    /* timer8 触发 */
    DAC_InitType.DAC_Trigger = DAC_Trigger_T8_TRGO;

    /* 不使用三角波或伪噪声 */
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;

    /* 设置三角波幅值 */
//    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;

    /* 使能输出Buffer，减少输出阻抗  */
    DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Enable;

    DAC_Init(DAC_Channel_1, &DAC_InitType);
    DAC_Cmd(DAC_Channel_1, ENABLE);

    /* 使能DAC DMA */
    dac_dma_init();
    DAC_DMACmd(DAC_Channel_1, ENABLE);

    /* 定时器8初始化 */
    timer8_init(10,720-1);  // 10K
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

	}
}





