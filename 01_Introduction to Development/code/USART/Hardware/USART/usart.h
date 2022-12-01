#ifndef HARDWARE_USART_USART_H_
#define HARDWARE_USART_USART_H_

#include "ch32v20x_conf.h"

void USARTx_CFG(void);
void USARTx_SendByte(USART_TypeDef* pUSARTx,uint8_t data);
void USARTx_SendStr(USART_TypeDef* pUSARTx,char *str);
void USART2_IRQHandler(void);

#endif /* HARDWARE_USART_USART_H_ */
