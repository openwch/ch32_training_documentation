#ifndef _ADC_H_
#define _ADC_H_

#include "debug.h"


#define PAGE_WRITE_START_ADDR            ((uint32_t)0x08010000) /* Start from 64K */
#define FLASH_PAGE_SIZE                  (ADC_RECORD_DATA_LENGTH*2) /* uint16_t 的音频数据，所以这里要将音频数组的长度*2*/

/* 录音时的数据存储 */
#define ADC_RECORD_DATA_LENGTH 1024*24
extern uint16_t adc_record_data_buffer[ADC_RECORD_DATA_LENGTH];

/* 实时喊话存放数据的每个 buffer 的数据长度 */
#define ADC_DATA_LENGTH  256 
/* 存放喊话时ADC采集的数据，两个buffer循环存储 */
extern uint16_t adc_data_buffer_1[ADC_DATA_LENGTH];
extern uint16_t adc_data_buffer_2[ADC_DATA_LENGTH];



extern void adc_init(void);

#endif /* end of adc.h */
