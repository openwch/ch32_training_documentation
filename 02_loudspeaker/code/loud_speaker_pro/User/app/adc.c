#include "adc.h"
#include "my_button.h"

/* 用于存放录音时的数据 */
uint16_t adc_record_data_buffer[ADC_RECORD_DATA_LENGTH] = {0};

/* 存放ADC采集的数据，两个buffer循环存储 */
uint16_t adc_data_buffer_1[ADC_DATA_LENGTH] = {0};
uint16_t adc_data_buffer_2[ADC_DATA_LENGTH] = {0};


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

    // TIM_Cmd(TIM3,ENABLE);
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
    NVIC_SetPriority(DMA1_Channel1_IRQn, 0x00);
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
    timer3_init(125,144-1); //8KHz

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );

}

/* 实时喊话模式 */
void loud_speaker_real_time(void)
{
    static volatile uint8_t adc_buffer_flag = 0;

    DMA1_Channel1->CFGR &= (uint16_t)(~DMA_CFGR1_EN); //修改 MADDR/CNTR 时，要先 关闭 DMA CFGR EN位
    DMA2_Channel3->CFGR &= (uint16_t)(~DMA_CFGR1_EN);

    if(adc_buffer_flag == 0)
    {
        adc_buffer_flag = 1;
        DMA1_Channel1->MADDR = (uint32_t)adc_data_buffer_2;// adc_data_buffer_1采集完成，切换adc_data_buffer_2
        DMA2_Channel3->MADDR = (uint32_t)adc_data_buffer_1;//dac 输出，
    }
    else
    {
        adc_buffer_flag = 0;
        DMA1_Channel1->MADDR = (uint32_t)adc_data_buffer_1;  // adc_data_buffer_2采集完成，切换adc_data_buffer_1
        DMA2_Channel3->MADDR = (uint32_t)adc_data_buffer_2;  //dac 输出
    }

    DMA2_Channel3->CNTR = ADC_DATA_LENGTH; //更新 DMA传输长度
    DMA2_Channel3->CFGR |= DMA_CFGR1_EN;   //启动 DAC DMA

    DMA1_Channel1->CNTR = ADC_DATA_LENGTH; //更新 DMA传输长度
    DMA1_Channel1->CFGR |= DMA_CFGR1_EN;   //启动 ADC DMA
}



/**
 * @brief 讲录音的数据存储到 flash 中
 * 
 */
void flash_test(void)
{
    __disable_irq();
    FLASH_Unlock_Fast();
    FLASH_EraseBlock_64K_Fast(PAGE_WRITE_START_ADDR);

    for(uint8_t i=0; i<FLASH_PAGE_SIZE/256; i++)
    {
        FLASH_ProgramPage_Fast(PAGE_WRITE_START_ADDR + 256 * i, (uint32_t*)adc_record_data_buffer + 64*i );
    }

    FLASH_Lock_Fast();

    __enable_irq();
}

/* ADC DMA 中断服务函数 */
__attribute__((interrupt("WCH-Interrupt-fast")))
void DMA1_Channel1_IRQHandler(void)
{
    DMA_ClearITPendingBit(DMA1_IT_TC1);

    switch(speakerLoudMode)
    {
        case LOUD_SPEAKER_MODE:
            loud_speaker_real_time();
            break;
        
        case RECORE_MODE: 

            //录音内存已满，关闭指示灯
            GPIO_SetBits(GPIOA,GPIO_Pin_7);
            TIM_Cmd(TIM3, DISABLE); 
            printf("recore over\r\n");
            flash_test();

            break;

        default:
            break;
    }  
}