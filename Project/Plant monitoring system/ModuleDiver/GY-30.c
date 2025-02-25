/**
  ******************************************************************************
  * @file    bh1750.c
  * @brief   BH1750驱动实现
  ******************************************************************************
  */

//#include "bh1750.h"
#include "GY-30.h"

/**
  * @brief  初始化传感器
  */
void BH1750_Init(void)
{
    I2C_Start();
    I2C_WriteByte(BH1750_ADDR << 1);
    I2C_GetAck();
    I2C_WriteByte(0x01);  /* 上电 */
    I2C_GetAck();
    I2C_Stop();
}

/**
  * @brief  读取光照强度
  */
float BH1750_Read(BH1750_Mode mode)
{
    uint8_t high, low;
    
    /* 发送测量命令 */
    I2C_Start();
    I2C_WriteByte(BH1750_ADDR << 1);
    I2C_GetAck();
    I2C_WriteByte(mode);
    I2C_GetAck();
    I2C_Stop();
    
    HAL_Delay(mode == ONE_TIME_HIGH ? 180 : 120);  /* 等待测量 */
    
    /* 读取数据 */
    I2C_Start();
    I2C_WriteByte((BH1750_ADDR << 1) | 1);
    I2C_GetAck();
    high = I2C_ReadByte(0);
    low = I2C_ReadByte(1);
    I2C_Stop();
    
    return (high << 8 | low) / 1.2f;  /* 转换为lux */
}