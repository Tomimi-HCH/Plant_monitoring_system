#ifndef __OLED_1IN3_C_H
#define __OLED_1IN3_C_H		

#include "DEV_Config.h"

/********************************************************************************
function:	
		Define the full screen height length of the display
********************************************************************************/
#define OLED_1in3_C_WIDTH  128//OLED width
#define OLED_1in3_C_HEIGHT 64 //OLED height

//function
void OLED_1in3_C_Init(void);
void OLED_1in3_C_Clear(void);
void OLED_1in3_C_Display(const UBYTE *Image);

#endif  
	 
