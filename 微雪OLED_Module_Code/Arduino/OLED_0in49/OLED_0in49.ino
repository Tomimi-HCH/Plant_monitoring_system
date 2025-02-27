#include <Arduino.h>
#include "DEV_Config.h"
#include "OLED_0in49.h"
#include "ImageData.h"
#include "GUI_paint.h"

void setup()
{
  System_Init();
  Serial.print(F("OLED_Init()...\r\n"));
  OLED_0in49_Init();
  Driver_Delay_ms(500);
  OLED_0in49_Clear();

  // 0.Create a new image cache
  UBYTE *BlackImage;
  UWORD Imagesize = ((OLED_0in49_WIDTH == 0) ? (OLED_0in49_WIDTH) : (OLED_0in49_WIDTH + 1)) * OLED_0in49_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize / 8)) == NULL)
  { // No enough memory
    Serial.print("Failed to apply for black memory...\r\n");
    return;
  }
  Serial.println("apply success!");
  Serial.print("Paint_NewImage\r\n");

  Paint_NewImage(BlackImage, OLED_0in49_HEIGHT, OLED_0in49_WIDTH,270, BLACK);
  Paint_SetScale(2);

  // 1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(BLACK);
  Driver_Delay_ms(500);

  while (1)
  {
    Serial.print("Drawing:page 1\r\n");
    Paint_DrawPoint(10, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(40, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    OLED_0in49_Display_RAM(BlackImage);
    Paint_DrawLine(2, 10, 2, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(20, 10, 20, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(30, 10, 30, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(62, 10, 62, 25, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    OLED_0in49_Display_RAM(BlackImage);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    
    Serial.print("Drawing:page 2\r\n");
    Paint_DrawCircle(30, 16, 12, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    OLED_0in49_Display_RAM(BlackImage);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);

    Serial.print("Drawing:page 3\r\n");
    Paint_DrawString_EN(0, 0, "waveshare", &Font12, BLACK, WHITE);
    OLED_0in49_Display_RAM(BlackImage);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    Paint_DrawNum(0, 10, "123.456", &Font12, 3, WHITE, BLACK);
    OLED_0in49_Display_RAM(BlackImage);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    Paint_DrawString_CN(0, 5, "你好", &Font12CN, WHITE, BLACK);
    Driver_Delay_ms(20);
    OLED_0in49_Display_RAM(BlackImage);
    Paint_DrawString_EN(35, 10, "Arduino", &Font8, WHITE, BLACK);
    OLED_0in49_Display_RAM(BlackImage);
    Driver_Delay_ms(2000);
    Paint_Clear(BLACK);
    // show the array image
    Serial.print("Drawing:page 4\r\n");
    OLED_0in49_Display(gImage_0in49);
    Driver_Delay_ms(2000);
    OLED_0in49_Clear();
    Driver_Delay_ms(2000);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}
