#include "system_init.h"

static void gpio_init(void);

void system_init(void)
{   
	gpio_init();   

	uart_task_init();
	
	timer0_init();
}


static void gpio_init(void)
{       
    CLK_DIV = 0x00;       //系统时钟对主时钟不分频，主时钟来自外部晶振
    IAP_CONTR &= 0xBF;    //看门狗复位后，系统从用户程序区0000H处开始执行用户程序
    
	//设置P00、P01、P02口为推挽输出
	P0M1 = 0x00;
	P0M0 = 0x07;

	//设置P3口为准双向口
	P3M1 = 0x00;
	P3M0 = 0x00;

	//设置P4口为准双向口
	P4M1 = 0x00;
	P4M0 = 0x00;
		
	//设置P5口为准双向口
	P5M1 = 0x00;
	P5M0 = 0x00;
    
	//初始化设置
	bRS485_2_Ctrl = 0;//2#RS485发送禁止（处于接收状态）
   	bRS485_3_Ctrl = 0;//3#RS485发送禁止（处于接收状态）
	bRS485_4_Ctrl = 0;//4#RS485发送禁止（处于接收状态）
}