/********************************** (C) COPYRIGHT *******************************
 * File Name          : MOTOR.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2022/11/22
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include "HAL.h"
#include "string.h"

/**************************************************************************************************
 *                                        GLOBAL VARIABLES
 **************************************************************************************************/
s16 Calibrattion_Val = 0;           //ADC校准值
JoystickState_t JoystickState;      //手柄状态

/**************************************************************************************************
 *                                        FUNCTIONS - Local
 **************************************************************************************************/

/*********************************************************************
 * @fn      HAL_ADC1Init
 *
 * @brief   Initializes ADC peripheral.
 *
 * @return  none
 **************************************************************************************************/
void HAL_ADC1Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    ADC_InitTypeDef  ADC_InitStructure = {0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE );
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                       //ADC最大时间不能超过14M,设置ADC分频因子6，60M/6=10M,

    //GPIO Init
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3;    //PA1-Channel1-left, PA3-Channel3-right
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;           //模拟输入
    GPIO_Init( GPIOA, &GPIO_InitStructure );

    ADC_DeInit(ADC1);                                       //复位ADC1,将外设 ADC1的全部寄存器重设为缺省值

    //ADC1 Init
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                      //ADC1工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                           //扫描模式关闭
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                     //连续转换模式关闭
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;     //转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                  //ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;                                 //规则转换的ADC通道的数目
    ADC_Init(ADC1, &ADC_InitStructure);                                     //ADC1初始化

    //Enable ADC1
    ADC_Cmd(ADC1, ENABLE);                                  //使能ADC1

    ADC_BufferCmd(ADC1, DISABLE);                           //使能校准前要关闭Buffer
    ADC_ResetCalibration(ADC1);                             //使能复位校准
    while(ADC_GetResetCalibrationStatus(ADC1));             //等待复位校准结束
    ADC_StartCalibration(ADC1);                             //开启AD校准
    while(ADC_GetCalibrationStatus(ADC1));                  //等待校准结束
    Calibrattion_Val = Get_CalibrationValue(ADC1);          //获取ADC1校准值
    ADC_BufferCmd(ADC1, ENABLE);                            //打开Buffer
}

/*********************************************************************
 * @fn      HAL_ADCCalibrattion
 *
 * @brief   Get Conversion Value.
 *
 * @param   val - Sampling value
 *
 * @return  val+Calibrattion_Val - Conversion Value.
 */
u16 HAL_ADCCalibrattion(s16 val)
{
    if((val + Calibrattion_Val) < 0)
        return 0;
    if((Calibrattion_Val + val) > 4095||val==4095)
        return 4095;
    return (val + Calibrattion_Val);
}

/*********************************************************************
 * @fn      HAL_GetADC1Value
 *
 * @brief   Get ADC1 value.
 *
 * @param   ch - ADC channel.
 *
 * @return  Conversion Value.
 */
u16 HAL_GetADC1Value(u8 ch)
{
    u16 temp;

    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_71Cycles5 );   //设置指定ADC的规则组通道，一个序列，采样时间为71.5个周期
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);                             //使能指定的ADC1的软件转换启动功能
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));                     //等待转换结束
    temp = ADC_GetConversionValue(ADC1);                                //ADC1规则组的转换结果
    temp = HAL_ADCCalibrattion((s16)temp);                              //数值校准

    return temp;
}

/*********************************************************************
 * @fn      HAL_GetADC1Average
 *
 * @brief   Get ADC1 average value.
 *
 * @param   ch - ADC channel.
 *          times - Get ADC value times.
 *
 * @return  Conversion Value.
 */
u16 HAL_GetADC1Average(u8 ch, u8 times)
{
    u32 temp_val=0;
    u8 t;

    for( t = 0; t < times; t++)
    {
        temp_val += HAL_GetADC1Value(ch);
    }

    return (temp_val / times);
}

/*********************************************************************
 * @fn      HAL_JoystickInit
 *
 * @brief   Initializes joysticks.
 *
 * @param   none
 *
 * @return  none
 */
void HAL_JoystickInit(void)
{
    HAL_ADC1Init();

    JoystickState.LeftJoystickState.dir = SERVO_DIRECTION_TURN_LEFT;
    JoystickState.LeftJoystickState.per = 0;
    JoystickState.RightJoystickState.dir = MOTOR_ROTATE_FORWARD;
    JoystickState.RightJoystickState.per = 0;
}

/*********************************************************************
 * @fn      HAL_JoystickState
 *
 * @brief   Start/Stop collecting Joystick ADC.
 *
 * @param   en - ENABLE/DISABLE
 *
 * @return  none
 */
void HAL_JoystickPressPercentageGet(void)
{
    uint16_t temp;

    temp = HAL_GetADC1Average(ADC_Channel_1, 8);
    if (temp < LEFT_JOYSTICK_MIDDLE)
    {
        JoystickState.LeftJoystickState.dir = SERVO_DIRECTION_TURN_RIGHT;
        JoystickState.LeftJoystickState.per = ((1000 * (LEFT_JOYSTICK_MIDDLE - temp) / (LEFT_JOYSTICK_MIDDLE - LEFT_JOYSTICK_RIGHT_MAX)) + 5) / 10;
    }
    else
    {
        JoystickState.LeftJoystickState.dir = SERVO_DIRECTION_TURN_LEFT;
        JoystickState.LeftJoystickState.per = ((1000 * (temp - LEFT_JOYSTICK_MIDDLE) / (LEFT_JOYSTICK_LEFT_MAX - LEFT_JOYSTICK_MIDDLE)) + 5) / 10;
    }

    temp = HAL_GetADC1Average(ADC_Channel_3, 8);
    if (temp > RIGHT_JOYSTICK_MIDDLE)
    {
        JoystickState.RightJoystickState.dir = MOTOR_ROTATE_BACKWARD;
        JoystickState.RightJoystickState.per = ((1000 * (temp - RIGHT_JOYSTICK_MIDDLE) / (RIGHT_JOYSTICK_BEHIND_MAX - RIGHT_JOYSTICK_MIDDLE)) + 5) / 10;
    }
    else
    {
        JoystickState.RightJoystickState.dir = MOTOR_ROTATE_FORWARD;
        JoystickState.RightJoystickState.per = ((1000 * (RIGHT_JOYSTICK_MIDDLE - temp) / (RIGHT_JOYSTICK_MIDDLE - RIGHT_JOYSTICK_FRONT_MAX)) + 5) / 10;
    }

    PRINT("Left dir:%d  per:%d\n", JoystickState.LeftJoystickState.dir, JoystickState.LeftJoystickState.per);
    PRINT("Right dir:%d  per:%d\n", JoystickState.RightJoystickState.dir, JoystickState.RightJoystickState.per);
}

/******************************** endfile @ motor ******************************/
