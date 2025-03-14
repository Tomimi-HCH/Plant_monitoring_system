/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 立创论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-26     LCKFB-LP    first version
 */
#include "board.h"

static uint32_t systick_us = 0;
//static uint32_t systick_ms = 0;

void board_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟
	systick_us=SystemCoreClock/8000000;	      				//为系统时钟的1/8
//	systick_ms=(uint32_t)systick_us*1000;					//每毫秒SysTick的VAL减的数目  	
}

void delay_us(uint32_t us)
{
	uint32_t systickCount;	
	uint32_t count = us * systick_us;
	
	if(us == 1)
	{
		SysTick->LOAD=count - 8;
	}
	else
	{
		SysTick->LOAD=count -10; 	//时间加载
	}	
	
	SysTick->VAL=0x00;        	//清空计数器	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //开始计数	  
	
	do
	{
		systickCount=SysTick->CTRL;
	}while((systickCount&0x01)&&!(systickCount&(1<<16))); //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //关闭计数器
	SysTick->VAL =0X00;       //清空计数器		
	
}

void delay_ms(uint32_t ms){ delay_us(ms * 1000); }

void delay_1us(uint32_t us){ delay_us(us); }

void delay_1ms(uint32_t ms){ delay_us(ms * 1000); }

