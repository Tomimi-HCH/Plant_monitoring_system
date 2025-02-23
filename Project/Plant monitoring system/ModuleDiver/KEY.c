#include "KEY.h"
#include "main.h"

/*
 *  函数名：KEY1_Value
 *  功能描述：获取按键KEY1的状态，按下返回0，否则返回1
 *  输入参数：无
 *  输出参数：无
 *  返回值：按键KEY1的状态
*/
uint8_t K1_Value(void)
{
    if(K1 == 0)
    {
        HAL_Delay(20);
        if(K1 == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 1;
}

/*
 *  函数名：KEY1_Value
 *  功能描述：获取按键KEY1的状态，按下返回0，否则返回1
 *  输入参数：无
 *  输出参数：无
 *  返回值：按键KEY1的状态
*/
uint8_t K2_Value(void)
{
    if(K2 == 0)
    {
        HAL_Delay(20);
        if(K2 == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 1;
}
