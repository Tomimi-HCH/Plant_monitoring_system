#include "driver_i2c.h"
#include "stdio.h"
#include "delay.h"

/*
 *  函数名：I2C_GPIO_ReInit
 *  功能描述：将模拟I2C的SCL和SDA引脚进行重新初始化
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
void I2C_GPIO_ReInit(void)
{
    /* 1. 使用结构体定义硬件GPIO对象 */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /* 2. 将SCL和SDA的GPIO寄存器的值恢复为复位上电值 */
    HAL_GPIO_DeInit(SCL_PORT, SCL_PIN);
    HAL_GPIO_DeInit(SDA_PORT, SDA_PIN);
    
    /* 3. 使能SCL和SDA的GPIO的时钟，因为他们都是GPIOB组的，所以这里只使能GPIOB的时钟 */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    /* 4. 设置GPIO的模式为开漏输出模式，响应速度设置为快速响应 */
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        
    /* 5. 选择要设置的GPIO引脚 */
    GPIO_InitStruct.Pin = SCL_PIN;
    
    /* 6. 调用init函数初始化GPIO */
    HAL_GPIO_Init(SCL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = SDA_PIN;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);
}

/*
 *  函数名：I2C_Start
 *  功能描述：模拟发出I2C的开始信号-->在SCL的高电平下，SDA的电平由高到低变化
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
void I2C_Start(void)
{
    SCL_H;
    SDA_H;
    delay_us(5);
    SDA_L;
    delay_us(5);
	SCL_L;
	delay_us(5);
}

/*
 *  函数名：I2C_Stop
 *  功能描述：模拟发出I2C的停止信号-->在SCL的高电平下，SDA的电平由低到高变化
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
void I2C_Stop(void)
{
	SCL_L;
    SDA_L;
	
    SCL_H;
    delay_us(5);
    SDA_H;
    delay_us(5);
}

/*
 *  函数名：I2C_GetAck
 *  功能描述：模拟I2C获取从设备的响应信号-->在SCL的高电平下，从设备将SDA拉低
 *  输入参数：无
 *  输出参数：无
 *  返回值：0有应答  1超时无应答
*/
int I2C_GetAck(void)
{

	char ack = 0;
	unsigned char ack_flag = 10;
	SCL_L;
	SDA_H;
	delay_us(5);
	SCL_H;
	delay_us(5);
	while( (SDA_IN==1) && ( ack_flag ) )
	{
		ack_flag--;
		delay_us(5);
	}

	if( ack_flag <= 0 )
	{
		I2C_Stop();
		return 1;
	}
    else
	{
		SCL_L;
	}
	return ack;
}

/*
 *  函数名：I2C_ACK
 *  功能描述：模拟I2C发出一个应答信号，在第九个时钟将SDA拉低
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
void I2C_ACK(void)
{
    SCL_L;
    SDA_L;
    delay_us(5);
	SDA_L;
	SCL_H;
	delay_us(5);
	SCL_L;
    SDA_H;

}

/*
 *  函数名：I2C_NACK
 *  功能描述：模拟I2C发出一个非应答信号，在第九个时钟将SDA拉高
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
void I2C_NACK(void)
{
    SCL_L;
    SDA_L;
    delay_us(5);
	SDA_H;
	SCL_H;
	delay_us(5);
	SCL_L;
    SDA_H;
}

/*
 *  函数名：I2C_WriteByte
 *  功能描述：模拟I2C发出一个字节的数据
 *  输入参数：data-->要发送出去的数据，范围0~255
 *  输出参数：无
 *  返回值：无
*/
void I2C_WriteByte(uint8_t data)
{
    uint8_t i = 0;
	//printf("I2C_WriteByte( %02X ) begain \r\n",data);
    for(i=0; i<8; i++)
    {
        SCL_L;
        if(data & 0x80)
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }
		SCL_H;
		delay_us(5);
        data <<= 1; // 发出1bit数据后，要更新数据，将data的次高位移位到最高位
        
    }
    if(I2C_GetAck() == -1){
	//printf("I2C_WriteByte failed \r\n");
	};
}

/*
 *  函数名：I2C_ReadByte
 *  返回值：返回读取到的数据
 *  输入参数：ack-->根据此参数判断在读到一个字节之后是否发出应答信号
 *  输出参数：无
*/
uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t i = 0;
    uint8_t data = 0;
    
    SDA_H;
    for(i=0; i<8; i++)
    {
        SCL_L;
        delay_us(5);
        SCL_H;
        delay_us(5);
        data <<= 1; // 更新数据前，要将上一次数据左移1位用来保存接下来的这一位数据
        if(SDA_IN == 1)    
        {                 
            data++;
        }
        else
        {
            data = data;
        }
    }
    
    // 根据ack决定是否发出应答
    if(ack == 0)
    {
        I2C_ACK();
    }
    else if(ack == 1)
    {
        I2C_NACK();
    }
    
    return data;
}

