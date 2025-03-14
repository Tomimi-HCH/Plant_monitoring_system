#include "driver_i2c.h"
#include "sgp30.h"
#include "stdio.h"


/******************************************************************
 * 函 数 名 称：SGP30_Write
 * 函 数 说 明：SGP30写命令
 * 函 数 形 参：regaddr_H命令高8位   regaddr_L命令低8位
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void SGP30_Write_cmd(uint8_t regaddr_H, uint8_t regaddr_L)
{
  I2C_Start();
  I2C_WriteByte(0xB0); //发送器件地址+写指令

  I2C_WriteByte(regaddr_H);           //发送控制地址
  I2C_WriteByte(regaddr_L);    //发送数据

  I2C_Stop();
	HAL_Delay(100);
}

/******************************************************************
 * 函 数 名 称：
 * 函 数 说 明：
 * 函 数 形 参：
 * 函 数 返 回：
 * 作       者：LC
 * 备       注：SGP30获取的数据格式为：2位CO2数据+1位CO2的CRC校验+2位TVOC数据+1位TVOC的CRC校验。
                模块上电需要15s左右初始化，在初始化阶段读取的CO2浓度为400ppm，TVOC为0ppd且恒定不变。
                因此上电后一直读，直到TVOC不为0并且CO2不为400，SGP30模块才初始化完成。
                初始化完成后刚开始读出数据会波动比较大，属于正常现象，一段时间后会逐渐趋于稳定。
                气体类传感器比较容易受环境影响，测量数据出现波动是正常的，可以添加滤波函数进行滤波。
******************************************************************/
uint32_t SGP30_Read(void)
{
  uint32_t dat;
  uint8_t crc;

  I2C_Start();
  I2C_WriteByte(0xB1); //发送器件地址+读指令

  dat = I2C_ReadByte(0);//CO2数据高8位
  dat <<= 8;
	
  dat += I2C_ReadByte(0);//CO2数据低8位
	
  crc = I2C_ReadByte(0); //CO2的CRC校验
  crc = crc;
	
  dat <<= 8;
  dat += I2C_ReadByte(0);//TVOC数据高8位
  dat <<= 8;
  dat += I2C_ReadByte(1);//TVOC数据低8位

  I2C_Stop();
  return(dat);
}

/******************************************************************
 * 函 数 名 称：SGP30_Init
 * 函 数 说 明：SGP30初始化
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void SGP30_Init(void)
{
    SGP30_Write_cmd(0x20, 0x03);
}