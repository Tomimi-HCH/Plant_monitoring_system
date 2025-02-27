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
  OLED_1in5_rgb_Init();
  Driver_Delay_ms(500); 
  OLED_1in5_rgb_Clear();  
  
  //1.Create a new image size
  UBYTE *BlackImage;
  Serial.print("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, OLED_1in5_RGB_WIDTH, OLED_1in5_RGB_HEIGHT, 270, BLACK);  
  Paint_SetScale(65);

  while(1) {
    
    // 2.Write directly to memory through the GUI 
    Serial.print("Drawing:page 1\r\n");
    Paint_DrawPoint(20, 20, BLUE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(40, 20, BRED, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(60, 20, GRED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    
    Paint_DrawLine(10, 10, 10, 25, GBLUE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(30, 10, 30, 25, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(50, 10, 50, 25, MAGENTA, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(70, 10, 70, 25, GREEN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    
    Paint_DrawCircle(30, 90, 20, CYAN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(15, 75, 45, 105, BROWN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);   
    Paint_DrawCircle(80, 80, 25, BROWN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(65, 65, 95, 95, CYAN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Driver_Delay_ms(2000);      
    OLED_1in5_rgb_Clear(); 
    
    Serial.print("Drawing:page 2\r\n");
    for(UBYTE i=0; i<16; i++){
      Paint_DrawRectangle(0, i*8, 127, (i+1)*8, i*4095, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    }     
    Driver_Delay_ms(2000);
    OLED_1in5_rgb_Clear();  
    
    Serial.print("Drawing:page 3\r\n");     
    Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, BLUE);
    Paint_DrawNum(10, 30, "123.4567", &Font12, 2, RED, BLACK); 
    Paint_DrawString_CN(10, 50,"你好Ab", &Font12CN, BLACK, BROWN);
    Paint_DrawString_CN(0, 80,"微雪电子", &Font24CN, BLACK, BRED);
    Driver_Delay_ms(2000);    
    OLED_1in5_rgb_Clear();   
    
    Serial.print("Drawing:page 4\r\n");
    OLED_1in5_rgb_Display_Part(gImage_1in5_rgb, 0, 0, 60, 60);
    Driver_Delay_ms(2000);    
    OLED_1in5_rgb_Clear();  
  }   
}

void loop() {

}
