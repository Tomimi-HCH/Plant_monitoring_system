/*****************************************************************************
* | File      	:   OLED_1in5_b_test.c
* | Author      :   Waveshare team
* | Function    :   1.5inch OLED Module (B) Drive function
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2023-06-16
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "test.h"
#include "OLED_1in5_b.h"
#include "math.h"


int OLED_1in5_b_test(void)
{
    printf("1.5binch OLED test demo\n");
        if(DEV_ModuleInit() != 0) {
        return -1;
    }
    OLED_1in5_B_Init();
    DEV_Delay_ms(500);
    OLED_1in5_B_Clear();

    // 0.Create a new image cache
    UBYTE *BlackImage;
    UWORD Imagesize = ((OLED_1in5_B_WIDTH%8 == 0) ? (OLED_1in5_B_WIDTH/8) : (OLED_1in5_B_WIDTH/8 + 1)) * OLED_1in5_B_HEIGHT;
    if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL)
    { // No enough memory
        return -1;
        printf(" No enough memory\n");
    }
    Paint_NewImage(BlackImage, OLED_1in5_B_WIDTH, OLED_1in5_B_HEIGHT, 0, BLACK);
    Paint_SetScale(2);

    // 1.Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(BLACK);
    DEV_Delay_ms(500);

    // OLED display test animation
    printf("1.5bbinch OLED test");
    #if USE_SPI
        OLED_1in5_B_Display_Test();
    #endif	
    Paint_DrawPoint(10, 10, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(40, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(80, 10, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(90, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(110, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);

    printf("1.5binch OLED test demo1\n");
    Paint_DrawLine(10, 20, 10, 35, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(20, 20, 20, 35, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(30, 20, 30, 35, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(40, 20, 40, 35, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

    Paint_DrawCircle(30, 60, 15, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(22, 52, 38, 68, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(80, 60, 15, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(72, 52, 88, 68, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    Paint_DrawRectangle(22, 92, 38, 108, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(72, 92, 88, 108, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(30, 100, 15, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(80, 100, 15, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    OLED_1in5_B_Display(BlackImage);
    DEV_Delay_ms(2000);

    printf("1.5binch OLED test demo2\n");
    Paint_Clear(BLACK);
    Paint_DrawNum(5, 10, 123.456789, &Font8, 4, WHITE, BLACK);
    Paint_DrawNum(5, 20, 987654, &Font12, 5, WHITE, BLACK);
    Paint_DrawString_CN(5, 30, "ÄãºÃabc", &Font12CN, WHITE, WHITE);
    Paint_DrawString_EN(5, 50, "WaveShare", &Font16, WHITE, WHITE);  
    Paint_DrawString_EN(5, 65, "RaspberryPi", &Font16, WHITE, WHITE);
    Paint_DrawString_CN(0, 80, "Î¢Ñ©µç×Ó", &Font24CN,WHITE, WHITE);
    OLED_1in5_B_Display(BlackImage);
    DEV_Delay_ms(2000);

    printf("1.5binch OLED test demo3\n");
    GUI_ReadBmp("./pic/1in5b.bmp", 0, 0);
    OLED_1in5_B_Display(BlackImage);
    DEV_Delay_ms(2000);

    Paint_Clear(BLACK);
    OLED_1in5_B_Clear();
    DEV_Delay_ms(2000);
    return 0;

}

