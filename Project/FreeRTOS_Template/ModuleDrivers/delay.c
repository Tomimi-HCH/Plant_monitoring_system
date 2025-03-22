#include "delay.h"
		   
static uint8_t  fac_us=0;							//us延时倍乘数			   
//static uint8_t  fac_ms=0;							//ms延时倍乘数			   
	
//初始化延迟函数, 在SystemClock_Config()后初始化，否则SystemCoreClock不正确
void delay_init()
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);	//SysTick频率为HCLK
															// 用SYSTICK_CLKSOURCE_HCLK_DIV8的话会使 HAL_Delay()变慢为8倍 HAL_Delay(1)实际会为8ms
	fac_us=SystemCoreClock/1000000;							//72M/1M=72 数72次为 1us
//	fac_ms=fac_us*1000;
}								    

// 延时nus
// nus为要延时的us数.
// 对 SysTick 寄存器进行了操作，可能会对其他使用了 SysTick 的定时造成影响？如 HAL_Delay() ?
//void delay_us(uint32_t nus)
//{		
//	uint32_t temp;	    	 
//	SysTick->LOAD=nus*fac_us; 					//时间加载	  		 
//	SysTick->VAL=0x00;        					//清空计数器
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
//	do
//	{
//		temp=SysTick->CTRL;
//	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
//	SysTick->VAL =0X00;      					 //清空计数器	 
//}

// 延时nus
// nus为要延时的us数
// 没有对 SysTick 进行改动，相对安全。但精准度可能会轻微降低？？
void delay_us(uint32_t nus)
{		
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
	ticks=nus*fac_us; 						//需要的节拍数 
	told=SysTick->VAL;        				//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	};
}

//延时nms
//nms:要延时的ms数
void delay_ms(uint16_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
}

