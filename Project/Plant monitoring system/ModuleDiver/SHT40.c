/**
  ******************************************************************************
  * @file    sht40.c
  * @brief   该文件提供SHT40温湿度传感器的驱动代码
  ******************************************************************************
  */

/* 包含头文件 ------------------------------------------------------------------*/
#include "sht40.h"
#include "main.h"
#include <math.h>

/* 私有宏定义 ------------------------------------------------------------------*/
#define SHT40_CRC8_POLYNOMIAL    0x31    /* SHT40使用的CRC8多项式 */
#define SHT40_CRC8_INIT          0xFF    /* CRC8初始值 */

/**
  * @brief  计算SHT40数据的CRC8校验和
  * @param  data --> 数据缓冲区指针
  * @param  len  --> 数据长度
  * @retval 计算得到的CRC8值
  */
static uint8_t SHT40_CRC8(uint8_t *data, uint8_t len)
{
    uint8_t crc = SHT40_CRC8_INIT;
    
    for(uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for(uint8_t bit = 0; bit < 8; bit++) {
            if(crc & 0x80) {
                crc = (crc << 1) ^ SHT40_CRC8_POLYNOMIAL;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

/**
  * @brief  初始化SHT40传感器
  * @param  无
  * @retval 0: 成功, -1: 失败
  */
int SHT40_Init(void)
{
    /* 执行软件复位 */
    return SHT40_SoftReset();
}

/**
  * @brief  从SHT40读取温湿度数据
  * @param  data --> 数据存储结构体指针
  * @retval 0: 成功, -1: 失败
  */
int SHT40_ReadData(SHT40_Data *data)
{
    uint8_t rawData[6];
    uint8_t cmd = SHT40_MEAS_HIGH_PREC;
    
    /* 发送测量命令 */
    I2C_Start();
    I2C_WriteByte(SHT40_ADDR_WRITE);
    if(I2C_GetAck() != 0) {
        I2C_Stop();
        return -1;
    }
    
    I2C_WriteByte(cmd);
    if(I2C_GetAck() != 0) {
        I2C_Stop();
        return -1;
    }
    I2C_Stop();
    
    /* 等待测量完成（高精度模式需等待10ms） */
    HAL_Delay(10);  // 需要根据实际测量时间调整延时
    
    /* 读取测量结果 */
    I2C_Start();
    I2C_WriteByte(SHT40_ADDR_READ);
    if(I2C_GetAck() != 0) {
        I2C_Stop();
        return -1;
    }
    
    /* 读取6字节数据：温度高、低字节，温度CRC，湿度高、低字节，湿度CRC */
    for(int i = 0; i < 6; i++) {
        rawData[i] = I2C_ReadByte((i == 5) ? 1 : 0);
    }
    I2C_Stop();
    
    /* 校验CRC */
    if(SHT40_CRC8(rawData, 2) != rawData[2] || 
       SHT40_CRC8(rawData+3, 2) != rawData[5]) {
        return -1;
    }
    
    /* 转换原始数据为实际值 */
    uint16_t tempRaw = (rawData[0] << 8) | rawData[1];
    uint16_t humiRaw = (rawData[3] << 8) | rawData[4];
    
    /* 计算温度（摄氏度） */
    data->temperature = -45.0f + 175.0f * (tempRaw / 65535.0f);
    
    /* 计算相对湿度（%RH） */
    data->humidity = -6.0f + 125.0f * (humiRaw / 65535.0f);
    
    return 0;
}

/**
  * @brief  执行软件复位
  * @param  无
  * @retval 0: 成功, -1: 失败
  */
int SHT40_SoftReset(void)
{
    I2C_Start();
    I2C_WriteByte(SHT40_ADDR_WRITE);
    if(I2C_GetAck() != 0) {
        I2C_Stop();
        return -1;
    }
    
    I2C_WriteByte(SHT40_SOFT_RESET);
    if(I2C_GetAck() != 0) {
        I2C_Stop();
        return -1;
    }
    I2C_Stop();
    
    /* 等待复位完成（手册要求至少1ms） */
    HAL_Delay(2);
    
    return 0;
}
