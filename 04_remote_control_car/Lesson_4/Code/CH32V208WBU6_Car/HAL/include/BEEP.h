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
#ifndef __BEEP_H
#define __BEEP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * CONSTANTS
 */


/*********************************************************************
 * TYPEDEFS
 */


/*********************************************************************
 * GLOBAL VARIABLES
 */

/**
 * @brief   Initializes GPIOC that control beep.
 */
void HAL_BeepInit(void);

/**
 * @brief   Beep voice control.
 */
void HAL_BeepState(uint8_t en);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
