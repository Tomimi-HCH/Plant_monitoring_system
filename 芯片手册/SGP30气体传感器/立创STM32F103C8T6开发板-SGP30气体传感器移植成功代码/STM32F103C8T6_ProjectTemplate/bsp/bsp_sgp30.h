
#ifndef _BSP_SGP30_H_
#define _BSP_SGP30_H_

#include "stm32f10x.h"


//端口移植
#define RCC_SGP30       RCC_APB2Periph_GPIOB
#define PORT_SGP30      GPIOB

#define GPIO_SDA        GPIO_Pin_9
#define GPIO_SCL        GPIO_Pin_8

//设置SDA输出模式
#define SDA_OUT()   {        \
                        GPIO_InitTypeDef  GPIO_InitStructure; \
                        GPIO_InitStructure.GPIO_Pin = GPIO_SDA; \
                        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; \
                        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; \
                        GPIO_Init(PORT_SGP30, &GPIO_InitStructure); \
                     }
//设置SDA输入模式
#define SDA_IN()    {        \
                        GPIO_InitTypeDef  GPIO_InitStructure; \
                        GPIO_InitStructure.GPIO_Pin = GPIO_SDA; \
                        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; \
                        GPIO_Init(PORT_SGP30, &GPIO_InitStructure); \
                    }
//获取SDA引脚的电平变化
#define SDA_GET()       GPIO_ReadInputDataBit(PORT_SGP30, GPIO_SDA)
//SDA与SCL输出
#define SDA(x)          GPIO_WriteBit(PORT_SGP30, GPIO_SDA, (x?Bit_SET:Bit_RESET) )
#define SCL(x)          GPIO_WriteBit(PORT_SGP30, GPIO_SCL, (x?Bit_SET:Bit_RESET) )

void SGP30_Init(void);
uint32_t SGP30_Read(void);
void SGP30_Write_cmd(uint8_t a, uint8_t b);

#endif
