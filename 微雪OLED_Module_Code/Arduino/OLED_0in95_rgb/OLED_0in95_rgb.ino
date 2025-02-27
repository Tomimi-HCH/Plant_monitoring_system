#include "OLED_Driver.h"
#include "GUI_paint.h"
#include "DEV_Config.h"
#include "Debug.h"
#include "ImageData.h"

void setup() {
  System_Init();
  if(USE_IIC) {
    Serial.print("Only USE_SPI_4W, Please revise DEV_config.h !!!");
    return 0;
  }
  
  Serial.print(F("OLED_Init()...\r\n"));
  OLED_0in95_rgb_Init();
  Driver_Delay_ms(500); 
  OLED_0in95_rgb_Clear();  
  
  //1.Create a new image size
  UBYTE *BlackImage;
  Serial.print("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, OLED_0in95_RGB_WIDTH, OLED_0in95_RGB_HEIGHT, 0, BLACK);  
  Paint_SetScale(65);

  while(1) {
    
    // 2.Write directly to memory through the GUI 
    Serial.print("Drawing:page 1\r\n");
    Paint_DrawPoint(20, 10, BLUE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(40, 10, BRED, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(60, 10, GRED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    
    Paint_DrawLine(10, 10, 10, 20, GBLUE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(30, 10, 30, 20, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(50, 10, 50, 20, MAGENTA, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(70, 10, 70, 20, GREEN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

    Paint_DrawCircle(40, 45, 15, CYAN, DOT_PIXEL_1X1, DRAW_FILL_FULL); 
    Paint_DrawRectangle(30, 35, 50, 55, BROWN, DOT_PIXEL_1X1, DRAW_FILL_FULL);    
    Paint_DrawCircle(80, 45, 15, BROWN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY); 
    Paint_DrawRectangle(70, 35, 90, 55, CYAN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Driver_Delay_ms(2000);      
    OLED_0in95_rgb_Clear(); 
    
    Serial.print("Drawing:page 2\r\n");
    for(UBYTE i=0; i<16; i++){
      Paint_DrawRectangle(0, 4*i, 95, 4*(i+1), i*4095, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    }     
    Driver_Delay_ms(2000);
    OLED_0in95_rgb_Clear();  
    
    Serial.print("Drawing:page 3\r\n");     
    Paint_DrawString_EN(10, 0, "waveshare", &Font12, BLACK, BLUE);
    Paint_DrawString_EN(10, 17, "hello world", &Font8, BLACK, MAGENTA);
    Paint_DrawNum(10, 30, "123.456789", &Font8, 5, RED, BLACK);
    Paint_DrawNum(10, 43, "987654", &Font12, 4, YELLOW, BLACK);
    Driver_Delay_ms(2000);    
    OLED_0in95_rgb_Clear();   

    Serial.print("Drawing:page 4\r\n");     
    Paint_DrawString_CN(20, 0,"你好Abc", &Font12CN, BLACK, BROWN);
    Paint_DrawString_CN(20, 20, "微雪", &Font24CN, BLACK, BRED);
    Driver_Delay_ms(2000);    
    OLED_0in95_rgb_Clear();  

    Serial.print("Drawing:page 5\r\n");     
    Paint_DrawString_CN(20, 20, "电子", &Font24CN, BLACK, BRED);
    Driver_Delay_ms(2000);    
    OLED_0in95_rgb_Clear();  
        
    Serial.print("Drawing:page 6\r\n");
    OLED_0in95_rgb_Display(gImage_0in95_rgb);
    Driver_Delay_ms(2000);    
    OLED_0in95_rgb_Clear();  
  }   
}

void loop() {

}
