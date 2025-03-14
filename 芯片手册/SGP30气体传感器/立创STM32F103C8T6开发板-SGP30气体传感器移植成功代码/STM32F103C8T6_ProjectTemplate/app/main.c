/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 立创论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-01     LCKFB-LP    first version
 */
#include "stm32f10x.h"
#include "board.h"
#include "bsp_uart.h"
#include "stdio.h"
#include "bsp_sgp30.h"

int main(void)
{
    uint32_t CO2Data, TVOCData;  //定义CO2浓度变量与TVOC浓度变量
    uint32_t sgp30_dat;          //定义SGP30读取到的数据
        
    board_init();
    
    uart1_init(115200U);

    SGP30_Init();
    delay_ms(100);
        
    while (1)
    {
        SGP30_Write_cmd(0x20,0x08);
        sgp30_dat = SGP30_Read();                  //读取SGP30的值
        CO2Data = (sgp30_dat & 0xffff0000) >> 16;  //获取CO2的值
        TVOCData = sgp30_dat & 0x0000ffff;         //获取TVOC的值
        printf("CO2 : %0.2d\r\nTVOC : %0.2d\r\n",CO2Data,TVOCData);
        delay_ms(1000);
    }
        

}
