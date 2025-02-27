/*****************************************************************************
* | File      	:   OLED_1in3_test.c
* | Author      :   Waveshare Team
* | Function    :   
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
* | Info        :
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
******************************************************************************/
#include "OLED_Test.h"
#include "OLED_0in49.h"
#include "GUI_Paint.h"
#include "ImageData.h"


int OLED_0in49_test(void)
{
    DEV_Delay_ms(100);
    
    if(DEV_Module_Init()!=0){
        while(1){
            printf("END\r\n");
        }
    }
    printf("OELD_test Demo\r\n");

    /* Init */
    OLED_0in49_Init();
    OLED_0in49_Clear();
    
    // 0.Create a new image cache
    UBYTE *BlackImage;
    UWORD Imagesize = ((OLED_0in49_WIDTH == 0) ? (OLED_0in49_WIDTH) : (OLED_0in49_WIDTH + 1)) * OLED_0in49_HEIGHT;
    if ((BlackImage = (UBYTE *)malloc(Imagesize / 8)) == NULL)
    { // No enough memory
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    Paint_NewImage(BlackImage, OLED_0in49_HEIGHT, OLED_0in49_WIDTH,270, BLACK);
    Paint_SetScale(2);
    printf("Drawing\r\n");
    // 1.Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(BLACK);
    DEV_Delay_ms(500);
    OLED_0in49_Display(BlackImage);
	
    while(1) {
        printf("Drawing:page 1\r\n");
        Paint_DrawPoint(10, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
        Paint_DrawPoint(25, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
        Paint_DrawPoint(40, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
        OLED_0in49_Display(BlackImage);
        Paint_DrawLine(2, 10, 2, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
        Paint_DrawLine(20, 10, 20, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
        Paint_DrawLine(30, 10, 30, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
        Paint_DrawLine(62, 10, 62, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
        OLED_0in49_Display(BlackImage);
        DEV_Delay_ms(2000);
        Paint_Clear(BLACK);
        
        printf("Drawing:page 2\r\n");
        Paint_DrawCircle(30, 16, 12, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
        OLED_0in49_Display(BlackImage);
        DEV_Delay_ms(2000);
        Paint_Clear(BLACK);

        printf("Drawing:page 3\r\n");
        Paint_DrawString_EN(0, 0, "waveshare", &Font12, BLACK, WHITE);
        OLED_0in49_Display(BlackImage);
        DEV_Delay_ms(2000);
        Paint_Clear(BLACK); 
        Paint_DrawNum(0, 10, 123.456, &Font12, 3, WHITE, BLACK);
        OLED_0in49_Display(BlackImage);
        DEV_Delay_ms(2000);
        Paint_Clear(BLACK);
        Paint_DrawString_CN(0, 5, "ÄãºÃ", &Font12CN, WHITE, BLACK);
        DEV_Delay_ms(20);
        OLED_0in49_Display(BlackImage);
        Paint_DrawString_EN(35, 10, "Pico", &Font8, WHITE, BLACK);
        OLED_0in49_Display(BlackImage);
        DEV_Delay_ms(2000);
        Paint_Clear(BLACK);
        // show the array image
        printf("Drawing:page 4\r\n");
        OLED_0in49_Display(gImage_0in49);
        DEV_Delay_ms(2000);
        OLED_0in49_Clear();
        DEV_Delay_ms(2000);
    }
    
    DEV_Module_Exit();
    return 0;
}
