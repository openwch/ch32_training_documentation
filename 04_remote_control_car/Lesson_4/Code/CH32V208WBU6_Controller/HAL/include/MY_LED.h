/********************************** (C) COPYRIGHT *******************************
 * File Name          : BEEP.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2022/11/22
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
#ifndef __MY_LED_H
#define __MY_LED_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * CONSTANTS
 */


/*********************************************************************
 * TYPEDEFS
 */
#define MY_LED_POWER_STATE_PIN          GPIO_Pin_0
#define MY_LED_LINK_STATE_PIN           GPIO_Pin_1

/*********************************************************************
 * GLOBAL VARIABLES
 */

/**
 * @brief   Initializes GPIOC that control LED.
 */
void HAL_MyLEDInit(void);

/**
 * @brief   Control LED turn on/off.
 */
void HAL_MyLEDState(uint16_t pin, uint8_t en);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
