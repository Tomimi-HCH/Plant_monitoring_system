#include "OLED_Driver.h"
#include "GUI_paint.h"
#include "DEV_Config.h"
#include "Debug.h"
#include "ImageData.h"

void setup() {
  System_Init();

  if(USE_SPI_4W) {
    Serial.print("Only USE_IIC, Please revise DEV_Config.h !!!\r\n");
    return -1;
  }
 
  Serial.print(F("OLED_Init()...\r\n"));
  OLED_0in91_Init();
  Driver_Delay_ms(500); 
  OLED_0in91_Clear();  
  
  //0.Create a new image cache
  UBYTE *BlackImage;
  UWORD Imagesize = ((OLED_0in91_WIDTH%8==0)? (OLED_0in91_WIDTH/8): (OLED_0in91_WIDTH/8+1)) * OLED_0in91_HEIGHT;
  if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) { 
      Serial.print("Failed to apply for black memory...\r\n");
      return -1;
  }
  Serial.print("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, OLED_0in91_HEIGHT, OLED_0in91_WIDTH, 90, BLACK);  

  //1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(BLACK);
  Driver_Delay_ms(500); 

  while(1) {
    
    // 2.Drawing on the image   
    Serial.print("Drawing:page 1\r\n");
    Paint_DrawPoint(15, 10, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(35, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(10, 10, 10, 20, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(20, 10, 20, 20, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(30, 10, 30, 20, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(40, 10, 40, 20, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawCircle(70, 16, 15, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(110, 16, 15, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);      
    Paint_DrawRectangle(60, 6, 80, 26, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(100, 6, 120, 26, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);   
    // 3.Show image on page1
    OLED_0in91_Display(BlackImage);
    Driver_Delay_ms(2000);      
    Paint_Clear(BLACK);
    
    // Drawing on the image
    Serial.print("Drawing:page 2\r\n");     
    Paint_DrawString_EN(10, 0, "waveshare", &Font16, WHITE, WHITE);
    Paint_DrawNum(10, 18, "123.456789", &Font12, 4, WHITE, WHITE);
    // Show image on page2
    OLED_0in91_Display(BlackImage);
    Driver_Delay_ms(2000);  
    Paint_Clear(BLACK);   

    // Drawing on the image
    Serial.print("Drawing:page 3\r\n");     
    Paint_DrawString_CN(0, 0,"你好Aba", &Font12CN, WHITE, WHITE);
    // Show image on page3
    OLED_0in91_Display(BlackImage);
    Driver_Delay_ms(2000);  
    Paint_Clear(BLACK); 

    // Drawing on the image
    Serial.print("Drawing:page 4\r\n");     
    OLED_0in91_Display_Array(gImage_0in91);
    Driver_Delay_ms(2000);  
    Paint_Clear(BLACK);  

    OLED_0in91_Clear();  
  }   
}

void loop() {

}
