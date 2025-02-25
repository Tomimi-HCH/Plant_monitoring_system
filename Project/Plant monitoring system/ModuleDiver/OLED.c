#include "OLED.h"
#include "spi.h"
#include "ascii_font.c"

 /**
  * 函    数：OLED写RES高低电平
  * 参    数：要写入RES的电平值，范围：0/1
  * 返 回 值：无
  * 说    明：当上层函数需要写RES时，此函数会被调用
  *           用户需要根据参数传入的值，将RES置为高电平或者低电平
  *           当参数传入0时，置RES为低电平，当参数传入1时，置RES为高电平
  */
void OLED_W_RES(uint8_t BitValue)
{
	/*根据BitValue的值，将RES置高电平或者低电平*/
	HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, (GPIO_PinState)BitValue);
}
 
/**
  * 函    数：OLED写DC高低电平
  * 参    数：要写入DC的电平值，范围：0/1
  * 返 回 值：无
  * 说    明：当上层函数需要写DC时，此函数会被调用
  *           用户需要根据参数传入的值，将DC置为高电平或者低电平
  *           当参数传入0时，置DC为低电平，当参数传入1时，置DC为高电平
  */
void OLED_W_DC(uint8_t BitValue)
{
	/*根据BitValue的值，将DC置高电平或者低电平*/
	HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, (GPIO_PinState)BitValue);
}
 
/**
  * 函    数：OLED写CS高低电平
  * 参    数：要写入CS的电平值，范围：0/1
  * 返 回 值：无
  * 说    明：当上层函数需要写CS时，此函数会被调用
  *           用户需要根据参数传入的值，将CS置为高电平或者低电平
  *           当参数传入0时，置CS为低电平，当参数传入1时，置CS为高电平
  */
void OLED_W_CS(uint8_t BitValue)
{
	/*根据BitValue的值，将CS置高电平或者低电平*/
	HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, (GPIO_PinState)BitValue);
}

/**
  * 函    数：OLED写命令
  * 参    数：Command 要写入的命令值，范围：0x00~0xFF
  * 返 回 值：无
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_W_CS(0);					//拉低CS，开始通信
	OLED_W_DC(0);					//拉低DC，表示即将发送命令
	HAL_SPI_Transmit(&hspi1, &Command, sizeof(Command), 0xFF);		//写入指定命令
	OLED_W_CS(1);					//拉高CS，结束通信
}
 
/**
  * 函    数：OLED写数据
  * 参    数：Data 要写入数据的起始地址
  * 参    数：Count 要写入数据的数量
  * 返 回 值：无
  */
void OLED_WriteData(uint8_t *Data, uint8_t Count)
{	
	OLED_W_CS(0);					//拉低CS，开始通信
	OLED_W_DC(1);					//拉高DC，表示即将发送数据
	HAL_SPI_Transmit(&hspi1, Data, Count, 0xFF);		//写入指定命令
	OLED_W_CS(1);					//拉高CS，结束通信
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WriteCommand (0xb0+i);    //设置页地址（0~7）
		OLED_WriteCommand (0x02);      //设置显示位置—列低地址
		OLED_WriteCommand (0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)	OLED_WriteData(0,8); 
	} //更新显示
}



//初始化SSD1306					    
void OLED_Init(void)
{ 	
	//OLED_RST_Set();
	HAL_Delay(100);
	OLED_RST_Clr();
	HAL_Delay(100);
	OLED_RST_Set(); 
					  
	OLED_WriteCommand(0xAE);//--turn off oled panel
	OLED_WriteCommand(0x02);//---set low column address
	OLED_WriteCommand(0x10);//---set high column address
	OLED_WriteCommand(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WriteCommand(0x81);//--set contrast control register
	OLED_WriteCommand(0xCF); // Set SEG Output Current Brightness
	OLED_WriteCommand(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WriteCommand(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WriteCommand(0xA6);//--set normal display
	OLED_WriteCommand(0xA8);//--set multiplex ratio(1 to 64)
	OLED_WriteCommand(0x3f);//--1/64 duty
	OLED_WriteCommand(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WriteCommand(0x00);//-not offset
	OLED_WriteCommand(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WriteCommand(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WriteCommand(0xD9);//--set pre-charge period
	OLED_WriteCommand(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WriteCommand(0xDA);//--set com pins hardware configuration
	OLED_WriteCommand(0x12);
	OLED_WriteCommand(0xDB);//--set vcomh
	OLED_WriteCommand(0x40);//Set VCOM Deselect Level
	OLED_WriteCommand(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WriteCommand(0x02);//
	OLED_WriteCommand(0x8D);//--set Charge Pump enable/disable
	OLED_WriteCommand(0x14);//--set(0x10) disable
	OLED_WriteCommand(0xA4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WriteCommand(0xA6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WriteCommand(0xAF);//--turn on oled panel
	
	OLED_WriteCommand(0xAF); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}  
