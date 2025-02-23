#include "LED.h"
#include "main.h"

/*
 *  函数名：LedOn
 *  功能描述：PC13输出高电平，点亮蓝色LED
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
void LedOn(void)
{
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, (GPIO_PinState)1);
}

/*
 *  函数名：LedOff
 *  功能描述：PC13输出低电平，熄灭蓝色LED
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
void LedOff(void)
{
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, (GPIO_PinState)0);
}

/*
 *  函数名：BlueShine
 *  功能描述：使用HAL_GPIO_TogglePin函数改变PC13的电平，闪烁蓝色LED
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
void BlueShine(void)
{
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    HAL_Delay(500);
}
