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

   ADC采集 OPA放大的麦克风信号，通过DAC输出。

   ADC采用 timer3 触发采样（ 8KHz），通过DMA1_Channel1 搬运

       通过printf打印采集的声音信号

*/

#include "debug.h"


/* Global typedef */

/* Global define */
#define ADC_DATA_LENGTH  256


/* Global Variable */
uint16_t adc_data_buffer_1[ADC_DATA_LENGTH] = {0};
uint16_t adc_data_buffer_2[ADC_DATA_LENGTH] = {0};


volatile uint8_t adc_buffer_flag = 0; // ADC DAM 采集完成中断，切换buffer标志
volatile uint8_t adc_dam_finish_flag = 0; // ADC DAM 采集完成中断标志

/***************************OPA**************/
/* OPA 初始化  */
void opa_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    OPA_InitTypeDef  OPA_InitStructure={0};

    /* opa4 初始化 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    OPA_InitStructure.OPA_NUM=OPA4;
    OPA_InitStructure.PSEL=CHP1;
    OPA_InitStructure.NSEL=CHN1;
    OPA_InitStructure.Mode=OUT_IO_OUT0;
    OPA_Init(&OPA_InitStructure);
    OPA_Cmd(OPA4,ENABLE);

    /* opa1 初始化 */

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    OPA_InitStructure.OPA_NUM=OPA1;
    OPA_InitStructure.PSEL=CHP0;
    OPA_InitStructure.NSEL=CHN0;
    OPA_InitStructure.Mode=OUT_IO_OUT0;
    OPA_Init(&OPA_InitStructure);
    OPA_Cmd(OPA1,ENABLE);
}

/*************ADC****************/
void timer3_init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    TIM_ARRPreloadConfig(TIM3, ENABLE);

    TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);

    TIM_Cmd(TIM3,ENABLE);
}


void adc_dma_init(void)
{

    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->RDATAR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_data_buffer_1;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = ADC_DATA_LENGTH;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);


    DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 0xf0);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);

    DMA_Cmd(DMA1_Channel1,ENABLE);

}


void adc_init(void)
{
    /* ADC 通道1 引脚初始化 */
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ADC1 模块初始化 */
    ADC_InitTypeDef ADC_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(ADC1);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;  //触发模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1,ENABLE);
    ADC_BufferCmd(ADC1, ENABLE);   //enable buffer

    /* ADC DMA 初始化 */
    adc_dma_init();
    ADC_DMACmd(ADC1, ENABLE);

    /* 使能外部触发模式 */
    ADC_ExternalTrigConvCmd(ADC1, ENABLE);

    /* timer3 初始化 */
    timer3_init(125,72-1); //8KHz
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
    USART_Printf_Init(256000);
    printf("SystemClk:%d\r\n",SystemCoreClock);

    opa_init();

    adc_init();


    /* 配置ADC1 规则组 转换顺序和通道采样时间  */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_71Cycles5 );       /* ADC1 通道1  */

    while(1)
    {
        if(adc_dam_finish_flag)
        {
            adc_dam_finish_flag = 0;
            if(adc_buffer_flag)
            {
                for(uint16_t i=0; i<ADC_DATA_LENGTH; i++)
                {
                    printf("adc_data = %d\r\n",adc_data_buffer_1[i]);
                }
            }
            else
            {
                for(uint16_t i=0; i<ADC_DATA_LENGTH; i++)
                {
                    printf("adc_data = %d\r\n",adc_data_buffer_2[i]);
                }
            }
        }
    }
}

/* ADC DMA 中断服务函数 */
__attribute__((interrupt("WCH-Interrupt-fast")))
void DMA1_Channel1_IRQHandler(void)
{
    DMA_ClearITPendingBit(DMA1_IT_TC1);
    adc_dam_finish_flag = 1;

    DMA1_Channel1->CFGR &= (uint16_t)(~DMA_CFGR1_EN); //修改 MADDR/CNTR 时，要先 关闭 DMA CFGR EN位

    if(adc_buffer_flag == 0)
    {
        adc_buffer_flag = 1;
        DMA1_Channel1->MADDR = (uint32_t)adc_data_buffer_2; // adc_data_buffer_1采集完成，切换adc_data_buffer_2
    }
    else
    {
        adc_buffer_flag = 0;
        DMA1_Channel1->MADDR = (uint32_t)adc_data_buffer_1; // adc_data_buffer_2采集完成，切换adc_data_buffer_1
    }

    DMA1_Channel1->CNTR = ADC_DATA_LENGTH; //更新 DMA传输长度
    DMA1_Channel1->CFGR |= DMA_CFGR1_EN;   //启动ADC DMA
}




