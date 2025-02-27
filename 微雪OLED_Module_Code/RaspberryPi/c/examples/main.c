#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "test.h"
#include <string.h>

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_ModuleExit();

    exit(0);
}

int main(int argc, char *argv[])
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    
    if (argc != 2){
        printf("please input OLED size and type! \r\n");
        printf("example: sudo ./main 1.3 or sudo ./main 1.3c \r\n");
        printf("If rgb: sudo ./main 1.5rgb \r\n");
        exit(1);
    }
    
    printf("%s OLED Moudule\r\n", argv[1]);
        
    if(strcmp(argv[1], "0.49") == 0)
        OLED_0in49_test();
    else if(strcmp(argv[1], "0.91") == 0)
        OLED_0in91_test();
    else if(strcmp(argv[1], "0.95rgb") == 0)
        OLED_0in95_rgb_test();
    else if(strcmp(argv[1], "0.96") == 0)
        OLED_0in96_test();
    else if(strcmp(argv[1], "0.96rgb") == 0)
        OLED_0in96_rgb_test();
    else if(strcmp(argv[1], "1.27rgb") == 0)
        OLED_1in27_rgb_test();
    else if(strcmp(argv[1], "1.3") == 0)
        OLED_1in3_test();
    else if(strcmp(argv[1], "1.3c") == 0)
        OLED_1in3_c_test();
    else if(strcmp(argv[1], "1.32") == 0)
        OLED_1in32_test();
    else if(strcmp(argv[1], "1.5") == 0)
        OLED_1in5_test();
    else if(strcmp(argv[1], "1.5b") == 0)
        OLED_1in5_b_test();
    else if(strcmp(argv[1], "1.5rgb") == 0)
        OLED_1in5_rgb_test();
    else if(strcmp(argv[1], "1.51") == 0)
        OLED_1in51_test();
    else if(strcmp(argv[1], "1.54") == 0)
        OLED_1in54_test();
    else if(strcmp(argv[1], "2.42") == 0)
        OLED_2in42_test();
    else
        printf("error: can not find the OLED\r\n");
    
    return 0;
    
}
