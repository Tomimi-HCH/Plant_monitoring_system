#ifndef _BH1750_H
#define _BH1750_H
#include "stm32f1xx_hal.h"

// BH1750命令定义
#define BH1750_CMD_POWER_ON 0x01
#define BH1750_CMD_CONTINUOUS_HIGH_RES_MODE 0x10
#define BH1750_CMD_ONE_TIME_HIGH_RES_MODE 0x20
#define BH1750_ADDR 0x23

// 函数声明
void BH1750_Init(void);
uint16_t BH1750_ReadLightLevel(void);

#endif // _BH1750_H