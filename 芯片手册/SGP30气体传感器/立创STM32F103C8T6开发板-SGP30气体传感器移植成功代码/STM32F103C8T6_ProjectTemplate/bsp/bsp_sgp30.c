#include "bsp_sgp30.h"
#include "stdio.h"
#include "board.h"


void SGP30_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_SGP30, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_SDA|GPIO_SCL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_SGP30, &GPIO_InitStructure);
	
	GPIO_SetBits(PORT_SGP30, GPIO_SDA|GPIO_SCL);
}


/******************************************************************
 * 函 数 名 称：IIC_Start
 * 函 数 说 明：IIC起始时序
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Start(void)
{
        SDA_OUT();
        
		SCL(0);
		delay_us(1);
        
        SDA(1);
        SCL(1); 
        delay_us(5);
        
        SDA(0);
        delay_us(5);
        SCL(0);
        delay_us(5);
                       
}
/******************************************************************
 * 函 数 名 称：IIC_Stop
 * 函 数 说 明：IIC停止信号
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Stop(void)
{
        SDA_OUT();
        
        SCL(0);
        SDA(0);
        
        SCL(1);
        delay_us(5);
        SDA(1);
        delay_us(5);
        
}

/******************************************************************
 * 函 数 名 称：IIC_Send_Ack
 * 函 数 说 明：主机发送应答或者非应答信号
 * 函 数 形 参：0发送应答  1发送非应答
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Send_Ack(unsigned char ack)
{
        SDA_OUT();
        SCL(0);
        SDA(0);
        delay_us(5);
        if(!ack) SDA(0);
        else     SDA(1);
        SCL(1);
        delay_us(5);
        SCL(0);
        SDA(1);
}


/******************************************************************
 * 函 数 名 称：I2C_WaitAck
 * 函 数 说 明：等待从机应答
 * 函 数 形 参：无
 * 函 数 返 回：0有应答  1超时无应答
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned char I2C_WaitAck(void)
{
        
        char ack = 0;
        unsigned char ack_flag = 10;
        SCL(0);
        SDA(1);
        SDA_IN();
        delay_us(5);
        SCL(1);
        delay_us(5);

        while( (SDA_GET()==1) && ( ack_flag ) )
        {
                ack_flag--;
                delay_us(5);
        }

        if( ack_flag <= 0 )
        {
                IIC_Stop();
                return 1;
        }
        else
        {
                SCL(0);
                SDA_OUT();
        }
        return ack;
}

/******************************************************************
 * 函 数 名 称：Send_Byte
 * 函 数 说 明：写入一个字节
 * 函 数 形 参：dat要写人的数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void Send_Byte(uint8_t dat)
{
        int i = 0;
        SDA_OUT();
        SCL(0);//拉低时钟开始数据传输
        
        for( i = 0; i < 8; i++ )
        {
                SDA( (dat & 0x80) >> 7 );
                delay_us(1);
                SCL(1);
                delay_us(5);
                SCL(0);
                delay_us(5);
                dat<<=1;
        }        
}

/******************************************************************
 * 函 数 名 称：Read_Byte
 * 函 数 说 明：IIC读时序
 * 函 数 形 参：无
 * 函 数 返 回：读到的数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned char Read_Byte(void)
{
        unsigned char i,receive=0;
        SDA_IN();//SDA设置为输入
        for(i=0;i<8;i++ )
        {
                SCL(0);
                delay_us(5);
                SCL(1);
                delay_us(5);
                receive<<=1;
                if( SDA_GET() )
                {        
                        receive|=1;   
                }
                delay_us(5); 
        }                                         
        SCL(0); 
  return receive;
}

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
  IIC_Start();
  Send_Byte(0XB0); //发送器件地址+写指令
  I2C_WaitAck();
  Send_Byte(regaddr_H);           //发送控制地址
  I2C_WaitAck();
  Send_Byte(regaddr_L);    //发送数据
  I2C_WaitAck();
  IIC_Stop();
  delay_ms(100);
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
    
  IIC_Start();
  Send_Byte(0XB1); //发送器件地址+读指令
  I2C_WaitAck();
    
  dat = Read_Byte();//CO2数据高8位
  IIC_Send_Ack(0);
  dat <<= 8;
    
  dat += Read_Byte();//CO2数据低8位
  IIC_Send_Ack(0);
    
  crc = Read_Byte(); //CO2的CRC校验
  IIC_Send_Ack(0);
  crc = crc;
    

  dat <<= 8;
  dat += Read_Byte();//TVOC数据高8位
  IIC_Send_Ack(0);
  
  dat <<= 8;
  dat += Read_Byte();//TVOC数据低8位
  IIC_Send_Ack(1);
  
  IIC_Stop();
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
    SGP30_GPIO_Init();
    SGP30_Write_cmd(0x20, 0x03);
}
