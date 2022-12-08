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
多通道的ADC采集
外部通道1 --> PA1
内部通道17  -->  1.2V 内部参考电压

*/

#include "debug.h"


/* Global typedef */

/* Global define */
#define ADC_DATA_LENGTH  16
#define ADC_CHANNEL_NUM  2

/* Global Variable */
volatile uint16_t adc_data_buffer[ADC_DATA_LENGTH][ADC_CHANNEL_NUM] = {0};

void adc_dma_init(void)
{
    DMA_InitTypeDef DMA_InitStructure = {0};
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* 复位 DMA1_Channel1 */
    DMA_DeInit(DMA1_Channel1);

    /* 配置外设地址  */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->RDATAR;

    /* 配置存储器地址  */
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_data_buffer;

    /* 方向：外设到存储器  */
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;

    /* 传输长度  */
    DMA_InitStructure.DMA_BufferSize = ADC_DATA_LENGTH * ADC_CHANNEL_NUM;

    /* disable外设地址递增  */
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

    /* enable 存储器地址递增  */
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    /* 外设数据单位：半字 */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;

    /* 存储器数据单位：半字 */
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;

    /* DMA模式 ：单次 */
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;

    /* DMA优先级 */
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;

    /* disable 存储器到存储器传输 */
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    /* DMA中断配置  */
    DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 0xf0);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);

    DMA_Cmd(DMA1_Channel1, ENABLE);
}


void adc_init(void)
{
    /* ADC 通道1 引脚初始化 */
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ADC1 模块初始化 */
    ADC_InitTypeDef ADC_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(ADC1);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;  /* 开启通道扫描 */
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = ADC_CHANNEL_NUM;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1,ENABLE);

    /* 使能 ADC Buffer */
    ADC_BufferCmd(ADC1, ENABLE);

    /* 使能内部ADC通道 */
    ADC_TempSensorVrefintCmd(ENABLE);

    /* ADC DMA 初始化 */
    adc_dma_init();
    ADC_DMACmd(ADC1, ENABLE);
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

	adc_init();

	/* 配置ADC1 规则组 转换顺序和通道采样时间  */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 1, ADC_SampleTime_239Cycles5 ); /* ADC1 内部通道17，1.2V参考电压  */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_71Cycles5 ); /* ADC1 通道1  */

    /* 软件触发转换 */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	while(1)
    {
	    ;
	}
}



/* ADC DMA 中断服务函数 */
__attribute__((interrupt("WCH-Interrupt-fast")))
void DMA1_Channel1_IRQHandler(void)
{
    DMA_ClearITPendingBit(DMA1_IT_TC1);

    printf("adc dma transfer complete\r\n");
    for(uint16_t i=0; i<ADC_DATA_LENGTH; i++)
    {
        printf("adc_data_buffer[%d][0] = %d, adc_data_buffer[%d][1] = %d\r\n",i,adc_data_buffer[i][0],i,adc_data_buffer[i][1]);
    }
}




