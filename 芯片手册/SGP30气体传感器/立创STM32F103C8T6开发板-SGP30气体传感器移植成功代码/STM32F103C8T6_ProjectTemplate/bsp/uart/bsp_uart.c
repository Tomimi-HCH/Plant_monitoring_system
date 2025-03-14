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
 
#include "bsp_uart.h" 
#include "stdio.h"

uint8_t  u1_recv_buff[USART1_RECEIVE_LENGTH]; // 接收缓冲区
uint16_t u1_recv_length;                      // 接收数据长度
uint8_t  u1_recv_flag;                        // 接收完成标志位

void uart1_init(uint32_t __Baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);	
	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin           = GPIO_Pin_9;//TX引脚
	GPIO_InitStructure.GPIO_Mode          = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed         = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin           = GPIO_Pin_10;//RX引脚
	GPIO_InitStructure.GPIO_Mode          = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	USART_InitTypeDef USART_InitStructure;//定义配置串口的结构体变量

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//开启串口1的时钟

	USART_DeInit(USART1);//大概意思是解除此串口的其他配置

	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate              = __Baud;//设置波特率
	USART_InitStructure.USART_WordLength            = USART_WordLength_8b;//字节长度为8bit
	USART_InitStructure.USART_StopBits              = USART_StopBits_1;//1个停止位
	USART_InitStructure.USART_Parity                = USART_Parity_No ;//没有校验位
	USART_InitStructure.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;//将串口配置为收发模式
	USART_InitStructure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None; //不提供流控 
	USART_Init(USART1,&USART_InitStructure);//将相关参数初始化给串口1
	
	USART_ClearFlag(USART1,USART_FLAG_RXNE);//初始配置时清除接收置位
	USART_ClearFlag(USART1,USART_FLAG_IDLE);//初始配置时清除空闲置位

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//初始配置接收中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//初始配置空闲中断

	USART_Cmd(USART1,ENABLE);//开启串口1
	
	NVIC_InitTypeDef NVIC_InitStructure;//中断控制结构体变量定义

	NVIC_InitStructure.NVIC_IRQChannel                    = USART1_IRQn;//中断通道指定为USART1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;//主优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;//次优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;//确定使能
	NVIC_Init(&NVIC_InitStructure);//初始化配置此中断通道
		
}

#if !defined(__MICROLIB)
//不使用微库的话就需要添加下面的函数
#if (__ARMCLIB_VERSION <= 6000000)
//如果编译器是AC5  就定义下面这个结构体
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
#endif

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);
	
	while( RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE) ){}
	
    return ch;
}

/************************************************
函数名称 ： uart1_receive_clear
功    能 ： 
参    数 ： 无
返 回 值 ： 无
作    者 ： LC
*************************************************/
void uart1_receive_clear(void)
{
	u1_recv_length = 0;
	u1_recv_flag = 0;
}

/************************************************
函数名称 ： uart1_get_data
功    能 ： 判断数据是否收到。收到则返回数组首地址
参    数 ： 无
返 回 值 ： 接收缓存数据首地址
作    者 ： LC
*************************************************/
uint8_t *uart1_get_data(void)
{
	if( u1_recv_flag == 1 )
	{
		uart1_receive_clear();
		return u1_recv_buff;
	}	
	
	return NULL;
}


/******** 串口1 中断服务函数 ***********/
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//判断是不是真的有接收中断发生
	{
		u1_recv_buff[u1_recv_length++] = USART_ReceiveData(USART1); // 把接收到的数据放到缓冲区中
		
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //已经处理就清楚标志位 
	}
	if(USART_GetITStatus(USART1, USART_IT_IDLE) == SET)//判断是不是真的有空闲中断发生
	{
		volatile uint32_t temp;
		temp = USART1->SR; // 读取状态寄存器以清除IDLE标志
		temp = USART1->DR; // 读取数据寄存器以清除IDLE标志
		
		u1_recv_buff[u1_recv_length] = '\0';
		u1_recv_flag = 1;
		
		// 下面整个清除函数没有任何用！！！
		// USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}


