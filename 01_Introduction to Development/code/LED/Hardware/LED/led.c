
#include "led.h"

void LED_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStructure;                //定义一个GPIO_InitTypeDef类型的结构体

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能与LED相关的GPIO端口时钟

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //配置GPIO引脚
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //设置GPIO模式为推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置GPIO口输出速度
 GPIO_Init(GPIOA, &GPIO_InitStructure);               //调用库函数，初始化GPIOA

 GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);           //设置引脚输出高电平

}

