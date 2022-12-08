#ifndef _MY_BUTTON_H_
#define _MY_BUTTON_H_


#include "debug.h"

/* record ---> PA6 */
#define  BUTTON_RECORD_CLK   RCC_APB2Periph_GPIOA
#define  BUTTON_RECORD_PORT  GPIOA
#define  BUTTON_RECORD_PIN   GPIO_Pin_6
/* play ---> PB13  */
#define  BUTTON_PLAY_CLK   RCC_APB2Periph_GPIOB
#define  BUTTON_PLAY_PORT  GPIOB
#define  BUTTON_PLAY_PIN   GPIO_Pin_13

/* 按键ID */
typedef enum
{
     BUTTON_RECORD_ID = 0,
     BUTTON_PLAY_ID
}button_id_t;

/* 录音喊话器模式 */
typedef enum
{
    RECORE_MODE = 0,
    LOUD_SPEAKER_MODE
}speaker_loud_mode_t;

extern speaker_loud_mode_t speakerLoudMode;

void my_button_init(void);

#endif /* end of my_button.h*/
