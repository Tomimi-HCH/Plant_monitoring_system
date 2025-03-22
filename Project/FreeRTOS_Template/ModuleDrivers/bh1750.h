#ifndef __BH1750_H
#define __BH1750_H

#include "stm32f1xx_hal.h"

#define   SlaveAddress   0x46 //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0x46，接电源时地址为0xB8

float bh1750_Read(void);
char bh1750_Write(uint8_t REG_Address);
void bh1750_Init(void);


#endif 
