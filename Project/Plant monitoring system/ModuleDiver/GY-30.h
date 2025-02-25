/**
  ******************************************************************************
  * @file    bh1750.h
  * @brief   BH1750光照传感器驱动
  ******************************************************************************
  */

#ifndef __GY_30_H__
#define __GY_30_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "driver_i2c.h"

#define BH1750_ADDR     0x23    /* 7位地址 */

/* 测量模式 */
typedef enum {
    CONTINUOUS_HIGH = 0x10,
    ONE_TIME_HIGH = 0x20
} BH1750_Mode;

/* 函数原型 */
void BH1750_Init(void);
float BH1750_Read(BH1750_Mode mode);

#ifdef __cplusplus
}
#endif

#endif /* __BH1750_H__ */