#ifndef __DELAY_H_
#define __DELAY_H_ 			   
#include "stm32f1xx_hal.h"
	 
void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);

#endif
