#include "system_init.h"

void main(void)
{    
    //系统初始化
    system_init();

    //打开总中断
    Enable_interrupt();

    //使用看门狗
    Wdt_enable();// 4.5s 

    while(1) {       
        //解析uart接收的命令
        uart_task();
        
        //喂狗
        Wdt_refresh();
    }
}