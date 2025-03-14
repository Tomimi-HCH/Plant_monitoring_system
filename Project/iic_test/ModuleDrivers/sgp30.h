#ifndef __SGP30_H
#define __SGP30_H

#include "stm32f1xx_hal.h"


void SGP30_Init(void);
uint32_t SGP30_Read(void);
void SGP30_Write_cmd(uint8_t a, uint8_t b);

#endif 
