#ifndef HARDWARE_CLK_CLK_H_
#define HARDWARE_CLK_CLK_H_

#include "ch32v20x.h"

void HSE_SetSysClock(uint32_t pllmul);
void HSI_SetSysClock(uint32_t pllmul);

#endif /* HARDWARE_CLK_CLK_H_ */
