#include "my_button.h"
#include "multi_button.h"
#include "adc.h"


/**
 * @brief 
 * 
 *      按键部分调用开源驱动 MultiButton：https://github.com/0x1abin/MultiButton 
 * 
 */

 Button buttonRecord;  /* 录音按钮 */
 Button buttonPlay;    /* 播放按钮 */


speaker_loud_mode_t speakerLoudMode = LOUD_SPEAKER_MODE;


static volatile uint8_t recorePlayFlag = 1;
static volatile uint8_t speakLoudFlag = 1;

void timer2_init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_ARRPreloadConfig(TIM2, ENABLE);

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    NVIC_SetPriority(TIM2_IRQn, 0x80);
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM_Cmd(TIM2,ENABLE);
}

void my_button_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    RCC_APB2PeriphClockCmd(BUTTON_RECORD_CLK|BUTTON_PLAY_CLK, ENABLE );
    GPIO_InitStructure.GPIO_Pin = BUTTON_RECORD_PIN;  /* button_record */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(BUTTON_RECORD_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BUTTON_PLAY_PIN;  /* button_play */
    GPIO_Init(BUTTON_PLAY_PORT, &GPIO_InitStructure);
}


uint8_t read_button_pin(uint8_t button_id)
{
    switch(button_id)
    {
        case BUTTON_RECORD_ID:
            return GPIO_ReadInputDataBit(BUTTON_RECORD_PORT,BUTTON_RECORD_PIN);
            break;

        case BUTTON_PLAY_ID:
            return GPIO_ReadInputDataBit(BUTTON_PLAY_PORT,BUTTON_PLAY_PIN);
            break;

        default:
        return 0;
            break;
    }
}

/* 长按RECORD 指示灯亮后开始录音 */
void button_record_long_press_start_handler(void* btn)
{
    speakerLoudMode = RECORE_MODE;
    /* 录音模式 */
    TIM_Cmd(TIM8, DISABLE);  // 关闭DAC 播放
    recorePlayFlag = 1;
    speakLoudFlag = 1;

    DMA1_Channel1->CFGR &= (uint16_t)(~DMA_CFGR1_EN); //修改 MADDR/CNTR 时，要先 关闭 DMA CFGR EN位
    DMA1_Channel1->MADDR = (uint32_t)adc_record_data_buffer;
    DMA1_Channel1->CNTR = ADC_RECORD_DATA_LENGTH; //更新 DMA传输长度
    DMA1_Channel1->CFGR |= DMA_CFGR1_EN;   //启动 ADC DMA

    GPIO_ResetBits(GPIOA,GPIO_Pin_7);
    TIM_Cmd(TIM3, ENABLE); 

    printf("record long press start \r\n");
}


/* 点击play按钮 播放/暂停 录音 */
void button_play_single_click_handler(void* btn)
{
    printf("play single click\r\n");
    speakLoudFlag = 1;

    if(recorePlayFlag)
    {
        recorePlayFlag = 0;
        TIM_Cmd(TIM3, DISABLE); 

        DMA2_Channel3->CFGR &= (uint16_t)(~DMA_CFGR1_EN); //修改 MADDR/CNTR 时，要先 关闭 DMA CFGR EN位
       /*DMA2_Channel3 切换为循环模式 */
        DMA2_Channel3->CFGR |= DMA_CFGR1_CIRC;

        DMA2_Channel3->MADDR = (uint32_t)adc_record_data_buffer;
        DMA2_Channel3->CNTR = ADC_RECORD_DATA_LENGTH; //更新 DMA传输长度
        DMA2_Channel3->CFGR |= DMA_CFGR1_EN;   //启动 ADC DMA

        TIM_Cmd(TIM8, ENABLE);
    }
    else
    {
        recorePlayFlag = 1;

        DMA2_Channel3->CFGR &= (uint16_t)(~DMA_CFGR1_EN); //修改 MADDR/CNTR 时，要先 关闭 DMA CFGR EN位
          /* 关闭 DMA2_Channel3 循环模式 */
        DMA2_Channel3->CFGR &= (uint16_t)(~DMA_CFGR1_CIRC);
        TIM_Cmd(TIM8, DISABLE);
    }
}

/* 双击 play 按键 启动/暂停 喊话模式 */
void button_play_double_click_handler(void* btn)
{
    printf("play double click\r\n");

    recorePlayFlag = 1;

    speakerLoudMode = LOUD_SPEAKER_MODE;

    if(speakLoudFlag)
    {
        speakLoudFlag = 0;
        
        /* 关闭 DMA2_Channel3 循环模式 */
        DMA2_Channel3->CFGR &= (uint16_t)(~DMA_CFGR1_EN); //修改 MADDR/CNTR 时，要先 关闭 DMA CFGR EN位
        DMA2_Channel3->CFGR &= (uint16_t)(~DMA_CFGR1_CIRC);


        /* 启动ADC 录音 */
        DMA1_Channel1->CFGR &= (uint16_t)(~DMA_CFGR1_EN); //修改 MADDR/CNTR 时，要先 关闭 DMA CFGR EN位
        DMA1_Channel1->MADDR = (uint32_t)adc_data_buffer_1;
        DMA1_Channel1->CNTR = ADC_DATA_LENGTH; //更新 DMA传输长度
        DMA1_Channel1->CFGR |= DMA_CFGR1_EN;   //启动 ADC DMA


        TIM_Cmd(TIM3, ENABLE);
        TIM_Cmd(TIM8, ENABLE);
    }
    else 
    {
        speakLoudFlag = 1;
        TIM_Cmd(TIM3, DISABLE);
        TIM_Cmd(TIM8, DISABLE);
    }

}

void my_button_init(void)
{
    my_button_gpio_init();

    /* 初始化按键对象 */
    button_init(&buttonRecord, read_button_pin, 0, BUTTON_RECORD_ID);
    button_attach(&buttonRecord, LONG_PRESS_START, button_record_long_press_start_handler);


    /* 启动按键 */
    button_start(&buttonRecord);

    button_init(&buttonPlay, read_button_pin, 0, BUTTON_PLAY_ID);
    button_attach(&buttonPlay, SINGLE_CLICK, button_play_single_click_handler);
    button_attach(&buttonPlay, DOUBLE_CLICK, button_play_double_click_handler);
    button_start(&buttonPlay);

    /* 启动定时器2，5ms中断一次，用于按键检测 */
    timer2_init(5000,144-1); /* 200hz */
}


/**
 * @brief timer2 中断服务函数
 * 
 *       5ms调用一次，用于检测按键
 */
__attribute__((interrupt("WCH-Interrupt-fast")))
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查TIM2中断是否发生
    {
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
        
        /* 按键检测事件 */
        button_ticks();
    }
  
}
