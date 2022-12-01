// 程序来到main函数之前，启动文件：statup_ch32v20x.S已经调用SystemInit()函数把系统时钟初始化成72MHZ
// SystemInit()在system_ch32v10x.c中定义
// 如果用户想修改系统时钟，可自行编写程序修改,本实验主要介绍如何编写程序修改系统时钟以及通过PA8引脚输出相关时钟

#include "debug.h"
#include "clk.h"

#define HSI      0   //HSI
#define HSI_1_2  1   //HSI/2

#define PLL_Source   HSI
//#define PLL_Source   HSI_1_2



//  软件延时函数，使用不同的系统时钟，延时不一样
void Delay(__IO uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}


void MCO_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    // 开启GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 选择GPIO8引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;

    //设置为复用功能推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    //设置IO的翻转速率为50M
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化GPIOA8
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


void LED_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;                     //定义一个GPIO_InitTypeDef类型的结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     //使能与LED相关的GPIO端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;      //配置GPIO引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;          //设置GPIO模式为推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         //设置GPIO口输出速度
    GPIO_Init(GPIOA, &GPIO_InitStructure);                    //调用库函数，初始化GPIOA

    GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);                //设置引脚输出高电平

}

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{


    USART_Printf_Init(115200);
    MCO_GPIO_Init();
    LED_Init();

    printf("This is HSE&HSI example\r\n");

    // 重新设置系统时钟，根据需要修改，CH32V103最高可设置为80MH，但通常使用72M作为默认设置
    // SYSCLK = 8M * RCC_PLLMul_x, x:[2,3,...16]
    HSE_SetSysClock(RCC_PLLMul_2);
    //HSI_SetSysClock(RCC_PLLMul_9);

    // 设置MCO引脚输出时钟，用示波器即可在PA8测量到输出的时钟信号
    // MCO引脚输出可以是HSE,HSI,PLLCLK/2,SYSCLK
    //RCC_MCOConfig(RCC_MCO_HSE);             // 8M
    //RCC_MCOConfig(RCC_MCO_HSI);             // 8M
    //RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);     // 36M
    RCC_MCOConfig(RCC_MCO_SYSCLK);            // 72M

    while (1)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);        // 亮
        Delay(0x0FFFFF);
        GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);      // 灭
        Delay(0x0FFFFF);
    }
}

