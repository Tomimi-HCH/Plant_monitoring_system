#include "bh1750.h"
#include "driver_i2c.h"

// BH1750初始化函数
void BH1750_Init(void)
{
    // 发送启动信号
    I2C_Start();

    // 发送设备地址和写指令
    I2C_WriteByte(BH1750_ADDR << 1);

    // 发送上电命令
    I2C_WriteByte(BH1750_CMD_POWER_ON);

    // 发送连续高分辨率测量模式命令
    I2C_WriteByte(BH1750_CMD_CONTINUOUS_HIGH_RES_MODE);

    // 发送停止信号
    I2C_Stop();
}

// 读取光照强度函数
uint16_t BH1750_ReadLightLevel(void)
{
    uint8_t dataH, dataL;
    uint16_t lightLevel;

    // 发送启动信号
    I2C_Start();

    // 发送设备地址和写指令
    I2C_WriteByte(BH1750_ADDR << 1);

    // 发送读取数据命令
    I2C_WriteByte(BH1750_CMD_CONTINUOUS_HIGH_RES_MODE);

    // 发送停止信号
    I2C_Stop();

    // 等待测量完成，根据数据手册一般需要一定时间延迟
    // 这里假设延迟200毫秒，实际可根据情况调整
    HAL_Delay(200);

    // 发送启动信号
    I2C_Start();

    // 发送设备地址和读指令
    I2C_WriteByte((BH1750_ADDR << 1) | 1);

    // 读取高8位数据
    dataH = I2C_ReadByte(1);

    // 读取低8位数据
    dataL = I2C_ReadByte(0);

    // 发送停止信号
    I2C_Stop();

    // 组合数据并计算光照强度
    lightLevel = (dataH << 8) | dataL;

    return lightLevel;
}