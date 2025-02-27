/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   07/01/2020
* | Info        :   在这里提供一个中文版本的使用文档，以便你的快速使用
* | 配置文件		oled_demo.ioc
* | STM32CubeMX 版本	5.6.1
* | MCU			STM32F103RBTx
******************************************************************************/

PERIPHERALS		MODES				FUNCTIONS	PINS
（外设）			（模式）				（功能）		（引脚名）
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
（引脚数）	（引脚名）	（功能）		（标签）
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
Project Name : oled_demo							（工程名）
Project Folder : E:\project\1.3inch OLED Module (C)\1.3inch_OLED_Module(C)_code\STM32	（工程文件夹位置）
Toolchain / IDE : MDK-ARM V5.27						（编译器名称与版本）
Firmware Package Name and Version : STM32Cube FW_F1 V1.8.0			（使用固件库与版本）


Code Generation Settings : 
STM32Cube MCU packages and embedded software packs : Copy all used libraries into the project folder	（拷贝所有库，放入工程文件夹）
Generate peripheral initialization as a pair of '.c/.h' files per peripheral : Yes				（生成单独的’.c/.h’文件存放外设初始化程序）
Backup previously generated files when re-generating : No						（在重新生成时备份以前生成的文件）
Delete previously generated files when not re-generated : Yes						（删除以前生成的文件时，不重新生成）
Set all free pins as analog (to optimize the power consumption) : No					（将所有空闲引脚设置为模拟模式，降低功耗）


Toolchains Settings : 
Compiler Optimizations : 									（编译器优化水平）

