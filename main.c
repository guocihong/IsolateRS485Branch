#include "system_init.h"

void main(void)
{    
    //ϵͳ��ʼ��
    system_init();

    //�����ж�
    Enable_interrupt();

    //ʹ�ÿ��Ź�
    Wdt_enable();// 4.5s 

    while(1) {       
        //����uart���յ�����
        uart_task();
        
        //ι��
        Wdt_refresh();
    }
}