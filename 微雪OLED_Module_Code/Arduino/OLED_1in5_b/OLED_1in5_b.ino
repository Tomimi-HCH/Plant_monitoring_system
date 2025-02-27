#include <Arduino.h>
#include "DEV_Config.h"
#include "OLED_1in5_b.h"
#include "ImageData.h"
#include "GUI_paint.h"

void setup()
{
  System_Init();
  Serial.print(F("OLED_Init()...\r\n"));
  OLED_1in5_B_Init();
  Driver_Delay_ms(500);
  OLED_1in5_B_Clear();

  // 0.Create a new image cache
  UBYTE *BlackImage;
  UWORD Imagesize = ((DrawBuffer_width%8 == 0) ? (DrawBuffer_width/8) : (DrawBuffer_width/8 + 1)) * DrawBuffer_height;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL)
  { // No enough memory
    Serial.print("Failed to apply for black memory...\r\n");
    return -1;
  }
  Serial.println("apply success!");
  Serial.print("Paint_NewImage\r\n");

  Paint_NewImage(BlackImage, DrawBuffer_width, DrawBuffer_height, 0, BLACK);
  Paint_SetScale(2);

  // 1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(BLACK);
  Driver_Delay_ms(500);

  while (1)
  {
    Serial.print("Drawing:page 1\r\n");
    // OLED display test animation
    #if USE_SPI
        OLED_1in5_B_Display_Test();
    #endif
    Serial.print("Drawing:page 2\r\n");
    Paint_DrawPoint(10, 10, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(40, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(80, 10, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(90, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(110, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    OLED_1in5_B_Display_Part(BlackImage, 0, 0, 64, 64);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    Paint_DrawLine(10, 10, 10, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(20, 10, 20, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(30, 10, 30, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(40, 10, 40, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    OLED_1in5_B_Display_Part(BlackImage, 0, 0, 128, 64);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    Paint_DrawCircle(30, 16, 14, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(22, 8, 38, 24, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(80, 16, 14, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(72, 8, 88, 24, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    OLED_1in5_B_Display_Part(BlackImage, 0, 0, 128, 64);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    Paint_DrawRectangle(22, 8, 38, 24, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(72, 8, 88, 24, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(30, 16, 14, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(80, 16, 14, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(60, 30, 65, 40, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    OLED_1in5_B_Display_Part(BlackImage, 0, 0, 128, 64);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    // // Drawing on the image
    Serial.print("Drawing:page 3\r\n");
    Paint_DrawString_EN(0, 30, "waveshare", &Font16, WHITE, BLACK);
    OLED_1in5_B_Display_Part(BlackImage, 0, 0, 128, 64);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    Paint_DrawNum(0, 50, "123.456", &Font12, 3, WHITE, BLACK);
    OLED_1in5_B_Display_Part(BlackImage, 0, 0, 128, 64);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    Paint_DrawString_CN(10, 40, "你好", &Font12CN, WHITE, BLACK);
    Driver_Delay_ms(20);
    OLED_1in5_B_Display_Part(BlackImage, 0, 0, 128, 64);
    Paint_DrawString_EN(40, 45, "Arduino", &Font16, WHITE, BLACK);
    OLED_1in5_B_Display_Part(BlackImage, 0, 0, 128, 64);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    // show the array image
    Serial.print("Drawing:page 4\r\n");
    OLED_1in5_B_Display(IMAGE_1in5B);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}
