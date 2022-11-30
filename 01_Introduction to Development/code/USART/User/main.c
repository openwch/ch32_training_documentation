#include "debug.h"
#include "usart.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    USARTx_CFG();
    USARTx_SendStr(USART2, "This is a test data.\n");

    while(1);


}
