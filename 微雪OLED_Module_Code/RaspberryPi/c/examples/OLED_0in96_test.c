/*****************************************************************************
* | File        :   OLED_0in96_test.c
* | Author      :   Waveshare team
* | Function    :   OLED_0in96 OLED Module test demo
* | Info        :
*----------------
* | This version:   V2.0
* | Date        :   2020-08-14
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
#include "OLED_0in96.h"
#include<time.h>

int OLED_0in96_test(void)
{
    int i=0;
    printf("0.96inch OLED test demo\n");
    if(DEV_ModuleInit() != 0) {
        return -1;
    }
      
    printf("OLED Init...\r\n");
    OLED_0in96_Init();
    DEV_Delay_ms(500);  
    // 0.Create a new image cache
    UBYTE *BlackImage;

    UWORD Imagesize = ((OLED_0in96_WIDTH%8==0)? (OLED_0in96_WIDTH/8): (OLED_0in96_WIDTH/8+1)) * OLED_0in96_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
            printf("Failed to apply for black memory...\r\n");
            return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, OLED_0in96_WIDTH, OLED_0in96_HEIGHT, 90, BLACK);  

    printf("Drawing\r\n");
    //1.Select Image
    Paint_SelectImage(BlackImage);
    DEV_Delay_ms(500);
    Paint_Clear(BLACK);
    
    // 2.Drawing on the image       
    time_t t_now,t_b=time(0);
    struct tm *l_time;
    char str1[20],str2[10];
    while(1)
    {
        t_now=time(0);
        l_time=localtime(&t_now);
        sprintf(str1,"%04d,%02d,%02d",l_time->tm_year+1900,l_time->tm_mon+1,l_time->tm_mday);
        sprintf(str2,"%02d:%02d:%02d",l_time->tm_hour,l_time->tm_min,l_time->tm_sec);
        Paint_DrawString_EN(0, 0, str1, &Font16, WHITE, WHITE);
        Paint_DrawString_EN(0, 32, str2, &Font20, WHITE, WHITE);
        OLED_0in96_display(BlackImage);
        DEV_Delay_ms(1); 
        Paint_Clear(BLACK);
        if(t_now-t_b>5)
        {
            break;
        }
    }
    // Drawing on the image
    
    printf("Drawing:page 2\r\n");           
    Paint_DrawString_EN(10, 0, "Display", &Font16, WHITE, WHITE);
    Paint_DrawString_EN(10, 16, "hello world", &Font8, WHITE, WHITE);
    Paint_DrawNum(10, 24, 123.456789, &Font12, 4, WHITE, WHITE);
    Paint_DrawNum(10, 36, 987654, &Font16, 3, WHITE, WHITE);
    // Show image on page2
    //OLED_0in96_display(BlackImage);
    DEV_Delay_ms(3000); 
    Paint_Clear(BLACK);      
    
    // Drawing on the image
    printf("Drawing:page 3\r\n");
    Paint_DrawString_EN(0, 0, "waveshare", &Font16, WHITE, WHITE);
    Paint_DrawString_CN(0, 20, "Î¢Ñ©µç×Ó", &Font24CN, WHITE, WHITE);
    // Show image on page3
    //OLED_0in96_display(BlackImage);
    DEV_Delay_ms(1500);     
    Paint_Clear(BLACK);     

    // Drawing on the image
    printf("Drawing:page 4\r\n");
    GUI_ReadBmp("./pic/waveshare.bmp", 0, 0);
    // Show image on page4
    //OLED_0in96_display(BlackImage);
    DEV_Delay_ms(1500);
    Paint_Clear(BLACK);
    
    int x=1,y=1,_x=1,_y=1,t=time(NULL),_t=0,fps=0,_fps=0;
    srand((unsigned int)time(NULL));
    x=rand()%(128-9*7);
    y=(rand()%(48-12))+16;
    _x=2*rand()%2-1;
    _y=2*rand()%2-1;
    i=0;
    while(1)
    {
        Paint_DrawString_EN(x, y,"Waveshare", &Font12, WHITE, WHITE);
        Paint_DrawString_EN(0, 0,"FPS:", &Font12, WHITE, WHITE);
        Paint_DrawNum(48, 0, fps, &Font12, 0, WHITE, WHITE);
        //OLED_0in96_display(BlackImage);
        Paint_Clear(BLACK);
        if((_fps%5)==0)
        {
            x+=_x;
            y+=_y;
        }
        if(x>(128-9*7-1))
        {
            _x=-1;
        }
        if(x<1)
        {
            _x=1;
        }
        if(y<16)
        {
            _y=1;
        }
        if(y>(64-12-1))
        {
            _y=-1;
        }
        _t=time(NULL);
        if(t==_t)
        {
            _fps++;
        }
        else
        {
            fps=_fps;
            _fps=0;
            t=_t;
            i++;
        }
        if(i>10)
        {
            break;
        }
    }
    OLED_0in96_clear();
    return 0;
}

