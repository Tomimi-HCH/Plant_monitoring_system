/**
  ******************************************************************************
  * @file    sht40.h
  * @brief   该文件包含SHT40温湿度传感器的所有函数原型
  ******************************************************************************
  */

/* 防止递归包含 -----------------------------------------------------------------*/
#ifndef __SHT40_H__
#define __SHT40_H__

#ifdef __cplusplus
extern "C" {
#endif

/* 包含头文件 ------------------------------------------------------------------*/
#include <stdint.h>
#include "driver_i2c.h"

/* 定义常量 --------------------------------------------------------------------*/
#define SHT40_ADDR_WRITE         0x88    /* 7位设备地址（写模式）：0x44左移1位后加写标志 */
#define SHT40_ADDR_READ          0x89    /* 7位设备地址（读模式）：0x44左移1位后加读标志 */

/* 测量命令定义 */
#define SHT40_MEAS_HIGH_PREC     0xFD    /* 高精度测量命令 */
#define SHT40_MEAS_MED_PREC      0xF6    /* 中精度测量命令 */
#define SHT40_MEAS_LOW_PREC      0xE0    /* 低精度测量命令 */
#define SHT40_SOFT_RESET         0x94    /* 软复位命令 */

/* 类型定义 --------------------------------------------------------------------*/
typedef struct {
    float temperature;  /* 温度值（摄氏度） */
    float humidity;     /* 湿度值（百分比RH） */
} SHT40_Data;

/* 函数原型声明 --------------------------------------------------------------*/
int SHT40_Init(void);
int SHT40_ReadData(SHT40_Data *data);
int SHT40_SoftReset(void);

#ifdef __cplusplus
}
#endif

#endif /* __SHT40_H__ */
