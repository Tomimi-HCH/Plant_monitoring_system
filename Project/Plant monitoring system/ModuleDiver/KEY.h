#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h"

/*********************
 * 函数宏定义
**********************/
#define K1      HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin)
#define K2      HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin)

extern uint8_t K1_Value(void);
extern uint8_t K2_Value(void);

#endif /* __DRIVER_KEY_H */
