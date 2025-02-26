#include "OLED.h"


// 显存（128x8字节）
static uint8_t oled_buffer[OLED_PAGES][OLED_WIDTH];

// 发送命令
static void OLED_WriteCmd(uint8_t cmd)
{
    OLED_DC_CMD();
    OLED_CS_LOW();
    HAL_SPI_Transmit(&OLED_SPI_HANDLE, &cmd, 1, HAL_MAX_DELAY);
    OLED_CS_HIGH();
}

// 发送数据
static void OLED_WriteData(uint8_t data)
{
    OLED_DC_DATA();
    OLED_CS_LOW();
    HAL_SPI_Transmit(&OLED_SPI_HANDLE, &data, 1, HAL_MAX_DELAY);
    OLED_CS_HIGH();
}




// 初始化序列
void OLED_Init(void)
{
    // 硬件复位
    HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, GPIO_PIN_SET);
    HAL_Delay(100);

    // 初始化命令序列
    OLED_WriteCmd(0xAE); // 关闭显示
    OLED_WriteCmd(0xD5); // 设置时钟分频
    OLED_WriteCmd(0x80);
    OLED_WriteCmd(0xA8); // 复用比率
    OLED_WriteCmd(0x3F); // 1/64
    OLED_WriteCmd(0xD3); // 显示偏移
    OLED_WriteCmd(0x00);
    OLED_WriteCmd(0x40); // 起始行
    OLED_WriteCmd(0xA1); // 段重定向
    OLED_WriteCmd(0xC8); // 扫描方向
    OLED_WriteCmd(0xDA); // 硬件配置
    OLED_WriteCmd(0x12);
    OLED_WriteCmd(0x81); // 对比度
    OLED_WriteCmd(0xCF);
    OLED_WriteCmd(0xD9); // 预充电周期
    OLED_WriteCmd(0xF1);
    OLED_WriteCmd(0xDB); // VCOMH电平
    OLED_WriteCmd(0x40);
    OLED_WriteCmd(0xA4); // 正常显示
    OLED_WriteCmd(0xA6); // 正常极性
    OLED_WriteCmd(0xAF); // 开启显示
    
    OLED_Clear();
    OLED_Refresh();
}

// 清空显存
void OLED_Clear(void)
{
    memset(oled_buffer, 0, sizeof(oled_buffer));
}

// 刷新显示
void OLED_Refresh(void)
{
    for(uint8_t page=0; page<OLED_PAGES; page++){
        OLED_WriteCmd(0xB0 + page); // 设置页地址
        OLED_WriteCmd(0x00);        // 列低地址
        OLED_WriteCmd(0x10);        // 列高地址
        
        for(uint8_t col=0; col<OLED_WIDTH; col++){
            OLED_WriteData(oled_buffer[page][col]);
        }
    }
}

// 设置光标位置
void OLED_SetCursor(uint8_t x, uint8_t y)
{
    static uint8_t curr_x = 0, curr_y = 0;
    if(x < OLED_WIDTH) curr_x = x;
    if(y < OLED_PAGES) curr_y = y;
    OLED_WriteCmd(0xB0 + curr_y);
    OLED_WriteCmd(((curr_x & 0xF0) >> 4) | 0x10);
    OLED_WriteCmd((curr_x & 0x0F) | 0x00);
}


/**
// 显示字符
void OLED_PrintChar(char ch)
{
    if(ch < 32 || ch > 127) return; // 只支持ASCII 32-127
    
    const uint8_t *font = &Font_7x10[(ch - 32) * 10];
    
    for(uint8_t i=0; i<10; i++){
        oled_buffer[0][i] = font[i];
    }
    OLED_Refresh();
}



// 显示字符串
void OLED_PrintString(char* str)
{
    while(*str){
        OLED_PrintChar(*str++);
        // 简单换行处理
        if((curr_x += 8) >= OLED_WIDTH){
            curr_x = 0;
            if(++curr_y >= OLED_PAGES) curr_y = 0;
        }
    }
}
**/

// 绘制像素点
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color)
{
    if(x >= OLED_WIDTH || y >= OLED_HEIGHT) return;
    
    uint8_t page = y / 8;
    uint8_t bit = y % 8;
    
    if(color)
        oled_buffer[page][x] |= (1 << bit);
    else
        oled_buffer[page][x] &= ~(1 << bit);
}