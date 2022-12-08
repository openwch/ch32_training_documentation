/*
 * 录音喊话器 demo
 * version: v1.0
 * Copyright (c) 2022 Taoyukai
 * SPDX-License-Identifier: Apache-2.0
 */


#include "debug.h"
#include "adc.h"
#include "dac.h"
#include "opa.h"
#include "my_button.h"



/**
 * @brief 主函数
 * 
 * @return int 
 */
int main(void)
{
    Delay_Init();
    USART_Printf_Init(512000);
    printf("ch32v307 hello world\r\n");

	// 音频功放使能引脚
    GPIO_InitTypeDef GPIO_InitStructure={0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    GPIO_SetBits(GPIOA,GPIO_Pin_7);



    for(uint32_t i=0; i<FLASH_PAGE_SIZE/4; i++)
    {
        *((uint32_t*)adc_record_data_buffer+i) = *((uint32_t *)PAGE_WRITE_START_ADDR + i);
    }


    opa_init();

	adc_init();

	dac_init();

    my_button_init();

    while(1)
    {
        ;
    }
}
