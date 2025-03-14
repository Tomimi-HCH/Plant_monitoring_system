/**
  ******************************************************************************
  * @file    sgp30.h
  * @brief   SGP30气体传感器驱动
  ******************************************************************************
  */

#ifndef __SGP30_H__
#define __SGP30_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "driver_i2c.h"

#define SGP30_ADDR      0x58    /* 7位地址 */

typedef struct {
    uint16_t tvoc;
    uint16_t co2_eq;
} SGP30_Data;

/* 函数原型 */
uint8_t SGP30_Init(void);
uint8_t SGP30_Read(SGP30_Data *data);

#ifdef __cplusplus
}
#endif

#endif /* __SGP30_H__ */
