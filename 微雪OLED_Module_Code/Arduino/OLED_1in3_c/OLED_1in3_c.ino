#include "OLED_Driver.h"
#include "GUI_paint.h"
#include "DEV_Config.h"
#include "Debug.h"
#include "ImageData.h"

void setup() {
  System_Init();
  Serial.print(F("OLED_Init()...\r\n"));
  OLED_Init();
  Driver_Delay_ms(500); 
  //0.Create a new image cache
  UBYTE *BlackImage;
  UWORD Imagesize = ((OLED_WIDTH % 8 == 0)? (OLED_WIDTH / 8 ): (OLED_WIDTH / 8 + 1)) * OLED_HEIGHT;
  if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
      Serial.print(F("Failed to apply for black memory...\r\n"));
      return -1;
  }
  Paint_NewImage(BlackImage, OLED_WIDTH, OLED_HEIGHT, 180, BLACK);  

  //1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(BLACK);
  Driver_Delay_ms(500); 

  while(1) {
  //2.Draw on the Image
  Serial.print(F("Drawing:page 1\r\n"));
  Paint_DrawPoint(20, 10, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  Paint_DrawPoint(30, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  Paint_DrawPoint(40, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  Paint_DrawLine(10, 10, 10, 20, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawLine(20, 20, 20, 30, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawLine(30, 30, 30, 40, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawLine(40, 40, 40, 50, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawCircle(60, 30, 15, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(100, 40, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL); 
  Paint_DrawRectangle(50, 30, 60, 40, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(90, 30, 110, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //3.Show Image
  OLED_Display(BlackImage);
  Driver_Delay_ms(2000);    
  Paint_Clear(BLACK);

  //2.Draw on the Image
  Serial.print(F("Drawing:page 2\r\n"));  
  Paint_DrawString_EN(10, 5, "waveshare", &Font16, WHITE, WHITE);
  Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, WHITE);
  Paint_DrawNum(10, 35, "1234567", &Font8, 3, WHITE, WHITE);
  Paint_DrawNum(10, 50, "9876.54321", &Font12, 2, WHITE, WHITE);    
  //3.Show Image
  OLED_Display(BlackImage);
  Driver_Delay_ms(2000);  
  Paint_Clear(BLACK);

  //2.Draw on the Image
  Serial.print(F("Drawing:page 3\r\n")); 
  Paint_DrawString_CN(10, 0,"你好Abc", &Font12CN, WHITE, WHITE);
  Paint_DrawString_CN(0, 20, "微雪电子", &Font24CN, WHITE, WHITE);
  //3.Show Image
  OLED_Display(BlackImage);
  Driver_Delay_ms(2000);  
  Paint_Clear(BLACK);

  //2.Draw on the Image
  Serial.print(F("Drawing:page 4\r\n")); 
  OLED_Display_Array(gImage_1in3_c);
  Driver_Delay_ms(2000);  
  Paint_Clear(BLACK); 
  
  }   
}

void loop() {

}
