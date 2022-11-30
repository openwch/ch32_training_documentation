
#include "clk.h"

/*
 * 使用HSE时，设置系统时钟的步骤
 * 1、开启HSE ，并等待 HSE 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源，和PLL的倍频因子，设置各种频率主要就是在这里设置
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/* 设置 系统时钟:SYSCLK, AHB总线时钟:HCLK, APB2总线时钟:PCLK2, APB1总线时钟:PCLK1
 * PCLK2 = HCLK = SYSCLK
 * PCLK1 = HCLK
 * 参数说明：pllmul是PLL的倍频因子，在调用的时候可以是：RCC_PLLMul_x , x:[2,3,...16]
 * 举例：User_SetSysClock(RCC_PLLMul_9);  则设置系统时钟为：8MHZ * 9 = 72MHZ
 * HSE作为时钟来源，经过PLL倍频作为系统时钟，这是通常的做法
 */

void HSE_SetSysClock(uint32_t pllmul)
{
    __IO uint32_t HSEStartUpStatus = 0;

  // 把RCC外设初始化成复位状态
  RCC_DeInit();

  //使能HSE，开启外部晶振，野火开发板用的是8M
  RCC_HSEConfig(RCC_HSE_ON);

  // 等待 HSE 启动稳定
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

    // 只有 HSE 稳定之后则继续往下执行
  if (HSEStartUpStatus == READY)
  {
    // AHB预分频因子设置为1分频，HCLK = SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    // APB2预分频因子设置为1分频，PCLK2 = HCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);

    // APB1预分频因子设置为1分频，PCLK1 = HCLK/2
    RCC_PCLK1Config(RCC_HCLK_Div2);

//-----------------设置各种频率主要就是在这里设置-------------------//
    // 设置PLL时钟来源为HSE，设置PLL倍频因子
    // PLLCLK = 8MHz * pllmul
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul);
//------------------------------------------------------------------//

    // 开启PLL
    RCC_PLLCmd(ENABLE);

    // 等待 PLL稳定
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    // 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    // 读取时钟切换状态位，确保PLLCLK被选为系统时钟
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  {
    // 如果HSE开启失败，那么程序就会来到这里，用户可在这里添加出错的代码处理
    // 当HSE开启失败或者故障的时候，单片机会自动把HSI设置为系统时钟，HSI是内部的高速时钟，8MHZ
    while (1)
    {
    }
  }
}
/*
 * 使用HSI时，设置系统时钟的步骤
 * 1、开启HSI ，并等待 HSI 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源，和PLL的倍频因子，设置各种频率主要就是在这里设置
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/* 设置 系统时钟:SYSCLK, AHB总线时钟:HCLK, APB2总线时钟:HCLK2, APB1总线时钟:PCLK1
 * PCLK2 = HCLK = SYSCLK
 * PCLK1 = HCLK
 * 参数说明：pllmul是PLL的倍频因子，在调用的时候可以是：RCC_PLLMul_x , x:[2,3,...16]
 *
 * HSI作为时钟来源，经过PLL倍频作为系统时钟，这是在HSE故障的时候才使用的方法
 * HSI会因为温度等原因会有漂移，不稳定，一般不会用HSI作为时钟来源，除非是迫不得已的情况
 * 如果HSI要作为PLL时钟的来源的话，可选择二分频或者不分频直接输入PLL。芯片可以在使用HSI时工作在72MHz主频
 * HSI作为PLL输入时钟，演示系统时钟为 24MHz、48MHz、72MHz。
 * HSI/2作为PLL输入时钟，演示系统时钟为 24MHz、48MHz
 */
void HSI_SetSysClock(uint32_t pllmul)
{

#if (PLL_Source == HSI)
  EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;  //HSI时钟作为PLL输入时钟
#endif

  __IO uint32_t HSIStartUpStatus = 0;

  // 把RCC外设初始化成复位状态
  RCC_DeInit();

  //使能HSI
  RCC_HSICmd(ENABLE);

  // 等待 HSI 就绪
  HSIStartUpStatus = RCC->CTLR & RCC_HSIRDY;

  // 只有 HSI就绪之后则继续往下执行
  if (HSIStartUpStatus == RCC_HSIRDY)
  {
   // AHB预分频因子设置为1分频，HCLK = SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    // APB2预分频因子设置为1分频，PCLK2 = HCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);

    // APB1预分频因子设置为1分频，PCLK1 = HCLK/2
    RCC_PCLK1Config(RCC_HCLK_Div2);

//-----------------设置各种频率主要就是在这里设置-------------------//
    // 若设置PLL时钟来源为HSI，设置PLL倍频因子
    // PLLCLK = 8MHz * pllmul
    // 若设置PLL时钟来源为HSI/2，设置PLL倍频因子
    // PLLCLK = 4MHz * pllmul
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, pllmul);
//------------------------------------------------------------------//

    // 开启PLL
    RCC_PLLCmd(ENABLE);

    // 等待 PLL稳定
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    // 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    // 读取时钟切换状态位，确保PLLCLK被选为系统时钟
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  {
    // 如果HSI开启失败，那么程序就会来到这里，用户可在这里添加出错的代码处理
    // 当HSE开启失败或者故障的时候，单片机会自动把HSI设置为系统时钟，HSI是内部的高速时钟，8MHZ
    while (1)
    {
    }
  }
}


