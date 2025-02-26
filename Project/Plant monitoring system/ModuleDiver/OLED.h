#ifndef __OLED_H
#define __OLED_H

#include "main.h"
#include "spi.h"
#include "stdlib.h"


// 显存定义（128x64像素）
#define OLED_WIDTH   128
#define OLED_HEIGHT  64
#define OLED_PAGES   (OLED_HEIGHT/8)

// 引脚定义
#define OLED_CS_GPIO_Port     GPIOA
#define OLED_CS_Pin      GPIO_PIN_4
#define OLED_DC_GPIO_Port     GPIOA
#define OLED_DC_Pin      GPIO_PIN_6
#define OLED_RES_GPIO_Port    GPIOA
#define OLED_RES_Pin     GPIO_PIN_3

// SPI实例选择（根据CubeMX配置修改）
#define OLED_SPI_HANDLE  hspi1

// 函数声明
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Refresh(void);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_PrintChar(char ch);
void OLED_PrintString(char* str);
void OLED_PrintNumber(int32_t num);
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color);
void OLED_DrawBitmap(const uint8_t *bitmap, uint8_t x, uint8_t y, uint8_t w, uint8_t h);

// 控制宏
#define OLED_CS_LOW()    HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_RESET)
#define OLED_CS_HIGH()   HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_SET)
#define OLED_DC_CMD()    HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET)
#define OLED_DC_DATA()   HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET)

#endif