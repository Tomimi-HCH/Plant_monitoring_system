#ifndef __OLED_H
#define __OLED_H

#include "stm32f1xx_hal.h"

extern void OLED_W_RES(uint8_t BitValue);
extern void OLED_W_DC(uint8_t BitValue);
extern void OLED_W_CS(uint8_t BitValue);
	
extern void OLED_WriteCommand(uint8_t Command);
extern void OLED_WriteData(uint8_t *Data, uint8_t Count);





#endif 