#include "driver_usart.h"
#include "usart.h"

#include <string.h>
#include <stdio.h>


/*
 *  函数名：DebugPrint
 *  功能描述：输出一串字符
 *  输入参数：str --> 指向要输出数据的首地址
 *  输出参数：无
 *  返回值：无
*/
void DebugPrint(const char *str)
{
    uint16_t len = strlen(str);
    
    HAL_UART_Transmit(&huart1, (uint8_t*)str, len, 3000);
}

/*
 *  函数名：DebugGet
 *  功能描述：接收指定长度的数据
 *  输入参数：str --> 指向将接收到的数据保存到内存中的首地址
 *            len --> 要接收数据的个数
 *  输出参数：无
 *  返回值：无
*/
void DebugGet(char *str, uint16_t len)
{
    while(HAL_UART_Receive(&huart1, (uint8_t*)str, len, 3000) != HAL_OK );
}

/*
 *  函数名：fputc
 *  功能描述：printf/putchar 标准输出函数的底层输出函数
 *  输入参数：ch --> 要输出的数据
 *  输出参数：无
 *  返回值：无
*/
int fputc(int ch, FILE *f)
{
    while(HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 3000) != HAL_OK);
}

/*
 *  函数名：fgetc
 *  功能描述：scanf/getchar 标准输出函数的底层输出函数
 *  输入参数：
 *  输出参数：无
 *  返回值：接收到的数据
*/
int fgetc(FILE *f)
{
    volatile char c = 0;
    while(HAL_UART_Receive(&huart1, (uint8_t*)&c, 1, 3000) != HAL_OK );
    
    return c;
}
