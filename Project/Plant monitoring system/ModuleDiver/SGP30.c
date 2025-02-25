/**
  ******************************************************************************
  * @file    sgp30.c
  * @brief   SGP30驱动实现
  ******************************************************************************
  */

#include "sgp30.h"
#include "main.h"
/**
  * @brief  CRC校验
  */
static uint8_t sgp30_crc(uint8_t *data, int len)
{
    uint8_t crc = 0xFF;
    for(int i=0; i<len; i++) {
        crc ^= data[i];
        for(int b=0; b<8; b++) {
            crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);
        }
    }
    return crc;
}

/**
  * @brief  初始化传感器
  */
uint8_t SGP30_Init(void)
{
    /* 发送初始化命令 */
    I2C_Start();
    I2C_WriteByte(SGP30_ADDR << 1);
    if(I2C_GetAck()) return 1;
    I2C_WriteByte(0x20);  // 0x2003高字节
    I2C_GetAck();
    I2C_WriteByte(0x03);  // 0x2003低字节
    I2C_GetAck();
    I2C_Stop();
    
    HAL_Delay(10);
    return 0;
}

/**
  * @brief  读取气体数据
  */
uint8_t SGP30_Read(SGP30_Data *data)
{
    uint8_t raw[6];
    
    /* 发送测量命令 */
    I2C_Start();
    I2C_WriteByte(SGP30_ADDR << 1);
    if(I2C_GetAck()) return 2;
    I2C_WriteByte(0x20);  // 0x2008高字节
    I2C_GetAck();
    I2C_WriteByte(0x08);  // 0x2008低字节
    I2C_GetAck();
    I2C_Stop();
    
    HAL_Delay(12);  /* 等待测量 */
    
    /* 读取数据 */
    I2C_Start();
    I2C_WriteByte((SGP30_ADDR << 1) | 1);
    if(I2C_GetAck()) return 3;
    
    for(int i=0; i<6; i++) {
        raw[i] = I2C_ReadByte(i==5 ? 1 : 0);
    }
    I2C_Stop();
    
    /* 校验并转换数据 */
    if(sgp30_crc(raw,2)!=raw[2] || sgp30_crc(raw+3,2)!=raw[5]) {
        return 4;
    }
    
    data->co2_eq = (raw[0] << 8) | raw[1];
    data->tvoc = (raw[3] << 8) | raw[4];
    
    return 0;
}