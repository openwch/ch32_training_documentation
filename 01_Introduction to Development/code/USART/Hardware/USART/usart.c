#include "usart.h"

void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*******************************************************************************
* Function Name  : USARTx_CFG
* Description    : 初始化 USART2
* Input          : None
* Return         : None
*******************************************************************************/
void USARTx_CFG(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //使能串口2时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟

  USART_DeInit(USART2);

  /* USART2 TX-->PA.2   RX-->PA.3 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //设置PA2为复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //设置PA3为浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;                 //设置串口波特率为115200
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //字长为8位数据格式
  USART_InitStructure.USART_StopBits = USART_StopBits_1;       //1个停止位
  USART_InitStructure.USART_Parity = USART_Parity_No;          //无奇偶校验位
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //发送和接收模式
  USART_Init(USART2, &USART_InitStructure);                    //初始化串口

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;      //抢占优先级为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;           //子优先级为1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);                              //中断优先级初始化

  USART_Cmd(USART2, ENABLE);                                   //使能串口
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);               //开启中断
}
/*******************************************************************************
* Function Name  : USARTx_SendByte
* Description    : 发送字符函数
* Input          : None
* Return         : None
*******************************************************************************/
void USARTx_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
    USART_SendData(pUSARTx, data);
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}
/*******************************************************************************
* Function Name  : USARTx_SendStr
* Description    : 发送字符串函数
* Input          : None
* Return         : None
*******************************************************************************/
void USARTx_SendStr(USART_TypeDef* pUSARTx, char *str)
{
    uint8_t i = 0;
    do
    {
       USARTx_SendByte(pUSARTx, *(str+i));
       i++;
    }while(*(str+i) != '\0');
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : USART2 中断函数
* Input          : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{
    uint8_t ucTemp;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //中断产生
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);    //清除中断标志
        ucTemp = USART_ReceiveData(USART2);               //接收数据
        USART_SendData(USART2, ucTemp);                   //发送数据
    }
}
