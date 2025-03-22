/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_usart.h
 * 摘要：
 *  
 * 修改历史     版本号        Author       修改内容
 *--------------------------------------------------
 * 2021.8.21      v01         百问科技      创建文件
 *--------------------------------------------------
*/

#ifndef __DRIVER_USART_H
#define __DRIVER_USART_H

#include "stm32f1xx_hal.h"


/*
 *  函数名：DebugPrint
 *  功能描述：输出一串字符
 *  输入参数：str --> 指向要输出数据的首地址
 *  输出参数：无
 *  返回值：无
*/
extern void DebugPrint(const char *str);

/*
 *  函数名：DebugGet
 *  功能描述：接收指定长度的数据
 *  输入参数：str --> 指向将接收到的数据保存到内存中的首地址
 *            len --> 要接收数据的个数
 *  输出参数：无
 *  返回值：无
*/
extern void DebugGet(char *str, uint16_t len);
#endif /* __DRIVER_USART_H */

