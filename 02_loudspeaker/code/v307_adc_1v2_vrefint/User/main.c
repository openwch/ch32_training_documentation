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
单通道的ADC采集，采集内部1.2v参考电压, 推导VDDA供电电压

*/

#include "debug.h"


/* Global typedef */

/* Global define */

/* Global Variable */
volatile uint16_t vref_adc_data = 0;


void adc_init(void)
{
//    /* ADC 通道1 引脚初始化 */
//    GPIO_InitTypeDef GPIO_InitStructure = {0};
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ADC1 模块初始化 */
    ADC_InitTypeDef ADC_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(ADC1);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* 使能 ADC1 */
    ADC_Cmd(ADC1,ENABLE);

    /* 使能 ADC Buffer */
    ADC_BufferCmd(ADC1, ENABLE);


    /* 使能内部ADC通道 */
    ADC_TempSensorVrefintCmd(ENABLE);

    /* 开启ADC中断 */
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
    NVIC_SetPriority(ADC_IRQn, 0x00);
    NVIC_EnableIRQ(ADC_IRQn);

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
	ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 1, ADC_SampleTime_239Cycles5 );

	/* 软件触发转换  */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);


	while(1)
    {
	    Delay_Ms(500);
	    printf("adc_data = %d\r\n",vref_adc_data);
	    printf("vcc = %2.3f\r\n",1.2*4095/vref_adc_data );/* 1.2v/1vref_adc_data = VDDA / 4095 */
	}
}


__attribute__((interrupt("WCH-Interrupt-fast")))
void ADC1_2_IRQHandler(void)
{
    if( ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET )
    {
        /* 获取 ADC 采样值 */
        vref_adc_data = ADC_GetConversionValue(ADC1);
        ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
    }

}



