#include "opa.h"



void opa_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    OPA_InitTypeDef  OPA_InitStructure={0};

    /* opa4 初始化 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    OPA_InitStructure.OPA_NUM=OPA4;
    OPA_InitStructure.PSEL=CHP1;
    OPA_InitStructure.NSEL=CHN1;
    OPA_InitStructure.Mode=OUT_IO_OUT0;
    OPA_Init(&OPA_InitStructure);
    OPA_Cmd(OPA4,ENABLE);

    /* opa1 初始化 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    OPA_InitStructure.OPA_NUM=OPA1;
    OPA_InitStructure.PSEL=CHP0;
    OPA_InitStructure.NSEL=CHN0;
    OPA_InitStructure.Mode=OUT_IO_OUT0;
    OPA_Init(&OPA_InitStructure);
    OPA_Cmd(OPA1,ENABLE);
}