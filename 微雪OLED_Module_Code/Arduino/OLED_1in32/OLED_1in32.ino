#include "OLED_Driver.h"
#include "GUI_paint.h"
#include "DEV_Config.h"
#include "Debug.h"
#include "ImageData.h"

void setup() {
  System_Init();
  Serial.print(F("OLED_Init()...\r\n"));
  OLED_1in32_Init();
  Driver_Delay_ms(500); 
  OLED_1in32_Clear(0);  
  
  //0.Create a new image cache
  UBYTE *BlackImage;
  UWORD Imagesize = ((OLED_1in32_WIDTH%2==0)? (OLED_1in32_WIDTH/2): (OLED_1in32_WIDTH/2+1)) * OLED_1in32_HEIGHT;
  if((BlackImage = (UBYTE *)malloc(Imagesize/8)) == NULL) { //No enough memory
      Serial.print("Failed to apply for black memory...\r\n");
      return -1;
  }
  Serial.print("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, OLED_1in32_WIDTH/4, OLED_1in32_HEIGHT/2, 270, BLACK);  // 32*48
  Paint_SetScale(16);

  //1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(BLACK);
  Driver_Delay_ms(500); 

  while(1) {
    Paint_SetRotate(0);
    // 2.Drawing on the image   
    Serial.print("Drawing:page 1\r\n");
    Paint_DrawPoint(10, 10, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 20, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 30, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    OLED_1in32_Display_Part(BlackImage, 0, 0, 32, 48);   
    Paint_Clear(BLACK);
    Paint_DrawLine(10, 10, 25, 10, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(10, 20, 25, 20, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(10, 30, 25, 30, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(10, 40, 25, 40, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    OLED_1in32_Display_Part(BlackImage, 0, 48, 32, 96); 
    Paint_Clear(BLACK);
    Paint_DrawCircle(16, 16, 14, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(8, 8, 24, 24, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    OLED_1in32_Display_Part(BlackImage, 32, 0, 64, 48); 
    Paint_Clear(BLACK);      
    Paint_DrawCircle(16, 16, 14, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(8, 8, 24, 24, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    OLED_1in32_Display_Part(BlackImage, 32, 48, 64, 96);      
    Paint_Clear(BLACK);               
    OLED_1in32_Display_Part(BlackImage, 64, 0, 96, 48);
    OLED_1in32_Display_Part(BlackImage, 96, 0, 128, 48);
    OLED_1in32_Display_Part(BlackImage, 64, 48, 96, 96);
    OLED_1in32_Display_Part(BlackImage, 96, 48, 128, 96);
    Driver_Delay_ms(2000);      
    Paint_Clear(BLACK);
    

    Paint_SetRotate(270);
    // Drawing on the image
    Serial.print("Drawing:page 2\r\n");
    for(UBYTE i=0; i<16; i++){
      Paint_DrawRectangle(0, 8*(i%4)+1, 47, 8*(i%4+1), i, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      if(i%4==3) {
        OLED_1in32_Display_Part(BlackImage, 32*(i/4), 0, 32*(i/4+1), 48);
        OLED_1in32_Display_Part(BlackImage, 32*(i/4), 48, 32*(i/4+1), 96);
        Paint_Clear(BLACK); 
      }
    }     
    Driver_Delay_ms(2000);  
    
    // Drawing on the image
    Serial.print("Drawing:page 3\r\n");     
    Paint_DrawString_EN(20, 10, "wave", &Font12, WHITE, WHITE);
    OLED_1in32_Display_Part(BlackImage, 0, 48, 32, 96); 
    Paint_Clear(BLACK);
    Paint_DrawString_EN(0, 10, "share", &Font12, WHITE, WHITE);
    OLED_1in32_Display_Part(BlackImage, 0, 0, 32, 48); 
    Paint_Clear(BLACK);
    Paint_DrawNum(2, 10, "12.3", &Font12, 2, WHITE, WHITE);
    OLED_1in32_Display_Part(BlackImage, 32, 0, 64, 48); 
    Paint_Clear(BLACK);   
    Paint_DrawNum(2, 10, "0.220", &Font12, 2, WHITE, WHITE);
    OLED_1in32_Display_Part(BlackImage, 32, 48, 64, 96); 
    Paint_Clear(BLACK);   
    Paint_DrawString_CN(2, 10,"你好", &Font12CN, WHITE, WHITE);
    OLED_1in32_Display_Part(BlackImage, 64, 0, 96, 48);
    Paint_Clear(BLACK);   
    Paint_DrawString_CN(2, 10,"Abc", &Font12CN, WHITE, WHITE);
    OLED_1in32_Display_Part(BlackImage, 96, 0, 128, 48); 
    Paint_Clear(BLACK);   
    Driver_Delay_ms(2000);    
    
    // show the array image
    Serial.print("Drawing:page 4\r\n");
    OLED_1in32_Display(gImage_1in32);
    Driver_Delay_ms(2000);    
    Paint_Clear(BLACK);      
  }   
}

void loop() {

}
