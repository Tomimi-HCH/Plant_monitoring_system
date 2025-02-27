/*****************************************************************************
* | File      	:   Readme_EN.txt
* | Author      :   Waveshare team
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :    07/01/2020
* | Info        :   Here is an English version of the documentation for your quick use.
* | Configuration	oled_demo.ioc
* | STM32CubeMX 	5.6.1
* | MCU		STM32F103RBTx
******************************************************************************/

PERIPHERALS		MODES				FUNCTIONS	PINS
I2C1			I2C				I2C1_SCL		PB8
I2C1			I2C				I2C1_SDA		PB9
RCC			Crystal/Ceramic Resonator		RCC_OSC_IN	PD0-OSC_IN
RCC			Crystal/Ceramic Resonator		RCC_OSC_OUT	PD1-OSC_OUT
SPI1			Full-Duplex Master			SPI1_MISO	PA6
SPI1			Full-Duplex Master			SPI1_MOSI	PA7
SPI1			Full-Duplex Master			SPI1_SCK		PA5
SYS			Serial Wire			SYS_JTCK-SWCLK	PA14
SYS			Serial Wire			SYS_JTMS-SWDIO	PA13
SYS			SysTick				SYS_VS_Systick	VP_SYS_VS_Systick
USART2			Asynchronous			USART2_RX	PA3
USART2			Asynchronous			USART2_TX	PA2


Pin Nb		PINs		FUNCTIONs	LABELs
5		PD0-OSC_IN	RCC_OSC_IN	
6		PD1-OSC_OUT	RCC_OSC_OUT	
16		PA2		USART2_TX	
17		PA3		USART2_RX	
21		PA5		SPI1_SCK		SPI1_SCK
22		PA6		SPI1_MISO	SPI1_MISO
23		PA7		SPI1_MOSI	SPI1_MOSI
37		PC6		GPIO_Output	IIC_SCL_SOFT
39		PC8		GPIO_Output	IIC_SDA_SOFT
41		PA8		GPIO_Output	OLED_DC
42		PA9		GPIO_Output	OLED_RST
46		PA13		SYS_JTMS-SWDIO	
49		PA14		SYS_JTCK-SWCLK	
58		PB6		GPIO_Output	OLED_CS
61		PB8		I2C1_SCL		I2C1_SCL
62		PB9		I2C1_SDA		I2C1_SDA



SOFTWARE PROJECT
Project Settings : 
Project Name : oled_demo	
Project Folder : E:\project\1.3inch OLED Module (C)\1.3inch_OLED_Module(C)_code\STM32
Toolchain / IDE : MDK-ARM V5.27
Firmware Package Name and Version : STM32Cube FW_F1 V1.8.0


Code Generation Settings : 
STM32Cube MCU packages and embedded software packs : Copy all used libraries into the project folder
Generate peripheral initialization as a pair of '.c/.h' files per peripheral : Yes
Backup previously generated files when re-generating : No
Delete previously generated files when not re-generated : Yes
Set all free pins as analog (to optimize the power consumption) : No


Toolchains Settings : 
Compiler Optimizations : 






