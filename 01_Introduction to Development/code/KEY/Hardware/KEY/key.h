#ifndef __KEY_H
#define __KEY_H

#include "ch32v20x_conf.h"

#define KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)  //读取按键0

#define KEY_PRESS   1       //KEY


void KEY_Init(void);    //按键IO初始化
u8 KEY_Scan(u8 mode);   //按键扫描函数

#endif
