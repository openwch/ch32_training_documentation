#include "key.h"
#include "debug.h"

//按键初始化函数
//PA2设置成输入
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTC时钟

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3; //按键GPIO引脚配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //设置成上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                //初始化GPIOA15

}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY_PRES，KEY按下
u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;//按键按松开标志
    if(mode)  key_up=1;  //支持连按
    if(key_up&&(KEY==0))
    {
        Delay_Ms(10);//去抖动
        key_up=0;
        if(KEY==0)      return KEY_PRESS;
    }else if(KEY==1)  key_up=1;
    return 0;// 无按键按下
}
