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
  OLED_0in96_rgb_Init();
  Driver_Delay_ms(500); 
  OLED_0in96_rgb_Clear();
  
  //1.Create a new image size
  UBYTE *BlackImage;
  Serial.print("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, OLED_0in96_rgb_WIDTH, OLED_0in96_rgb_HEIGHT, 90, BLACK);  
  Paint_SetScale(65);

  #if 0

    Serial.print("Brush white\r\n");
    OLED_0in96_rgb_Clear_color(white);  
    Driver_Delay_ms(1000); 

    Serial.print("Brush red\r\n");
    OLED_0in96_rgb_Clear_color(red);  
    Driver_Delay_ms(1000); 

    Serial.print("Brush green\r\n");
    OLED_0in96_rgb_Clear_color(green);  
    Driver_Delay_ms(1000); 

    Serial.print("Brush blue\r\n");
    OLED_0in96_rgb_Clear_color(blue);  
    Driver_Delay_ms(1000); 

    Serial.print("Brush drawing\r\n");
    OLED_0in96_rgb_Display(gImage_0in96_rgb);
    Driver_Delay_ms(1000); 

    Serial.print("Brush black\r\n");
    OLED_0in96_rgb_Clear_color(black);  
    Driver_Delay_ms(1000); 

  #endif

  while(1) 
  {
    #if 0
      // 2.Drawing on the image		
      Serial.print("Drawing:page 1\r\n");
      Paint_DrawPoint(20, 10, BLUE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
      Paint_DrawPoint(30, 10, BRED, DOT_PIXEL_2X2, DOT_STYLE_DFT);
      Paint_DrawPoint(40, 10, GRED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
      Paint_DrawLine(10, 10, 10, 20, GBLUE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
      Paint_DrawLine(20, 20, 20, 30, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
      Paint_DrawLine(30, 30, 30, 40, MAGENTA, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
      Paint_DrawLine(40, 40, 40, 50, GREEN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
      Paint_DrawCircle(60, 30, 15, CYAN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);	
      Paint_DrawRectangle(50, 30, 60, 40, BROWN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
      Driver_Delay_ms(2000);	
      OLED_0in96_rgb_Clear_color(black);  		

      // Drawing on the image
      Serial.print("Drawing:page 2\r\n");			
      Paint_DrawString_EN(10, 0, "waveshare", &Font12, BLACK, BLUE);
      Paint_DrawString_EN(10, 17, "hello world", &Font8, BLACK, MAGENTA);
      Paint_DrawNum(10, 30, "123.456789", &Font8, 5, RED, BLACK);
      Paint_DrawNum(10, 43, "987654", &Font12, 4, YELLOW, BLACK);
      Driver_Delay_ms(2000);	
      OLED_0in96_rgb_Clear_color(black); 

    #else 

      // Drawing on the image
      Serial.print("Drawing:page 3\r\n");
      Paint_DrawString_CN(0, 0,"你好abc", &Font12CN, BLACK, BROWN);
      Paint_DrawString_CN(0, 20, "微雪电子", &Font24CN, BLACK, BRED);
      Driver_Delay_ms(1000);	
      OLED_0in96_rgb_Clear_color(black);  	

      Serial.print("Drawing:page 4\r\n");
      // Show image on page5
      OLED_0in96_rgb_Display(gImage_0in96_rgb);
      Driver_Delay_ms(1000);	

    #endif	
      
      OLED_0in96_rgb_Clear_color(black);  
      Driver_Delay_ms(1000); 
  }   
}

void loop() {

}
