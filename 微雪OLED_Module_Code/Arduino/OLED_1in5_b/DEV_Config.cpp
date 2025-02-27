/******************************************************************************
**************************Hardware interface layer*****************************
  | file        : DEV_Config.cpp
  | version     : V1.0
  | date        : 2020-06-16
  | function    : Provide the hardware underlying interface
******************************************************************************/
#include "DEV_Config.h"

/********************************************************************************
  function: System Init and exit
  note:
  Initialize the communication method
********************************************************************************/
uint8_t System_Init(void)
{
  //set pin
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_RST, OUTPUT);
  pinMode(OLED_DC, OUTPUT);

  //set Serial
  Serial.begin(115200);

#if USE_SPI
  Serial.println("USE_SPI");
  //set OLED SPI
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

#elif USE_IIC
  //set OLED I2C
  Serial.println("USE_I2C");
  OLED_DC_1;// DC = 1 ,Hardware setting 0x3d or 0x3c
  OLED_CS_0;
  Wire.setClock(4000000);
  Wire.begin();
#endif
  return 0;
}

/********************************************************************************
  function: Hardware interface
  note:
  SPI4W_Write_Byte(value) :
    hardware SPI
  I2C_Write_Byte(value, cmd):
    hardware I2C
********************************************************************************/
void DEV_SPI_WriteByte(uint8_t DATA)
{
  SPI.transfer(DATA);
}

void I2C_Write_Byte(uint8_t value, uint8_t Cmd)
{
  uint8_t Addr = IIC_ADR;
  Wire.beginTransmission(Addr);
  Wire.write(Cmd);
  Wire.write(value);
  Wire.endTransmission();
}

/********************************************************************************
  function: Delay function
  note:
  Driver_Delay_ms(xms) : Delay x ms
  Driver_Delay_us(xus) : Delay x us
********************************************************************************/
void Driver_Delay_ms(unsigned long xms)
{
  delay(xms);
}

void Driver_Delay_us(int xus)
{
  for (int j = xus; j > 0; j--);
}