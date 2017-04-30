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
    CLK_DIV = 0x00;       //ϵͳʱ�Ӷ���ʱ�Ӳ���Ƶ����ʱ�������ⲿ����
    IAP_CONTR &= 0xBF;    //���Ź���λ��ϵͳ���û�������0000H����ʼִ���û�����
    
	//����P00��P01��P02��Ϊ�������
	P0M1 = 0x00;
	P0M0 = 0x07;

	//����P3��Ϊ׼˫���
	P3M1 = 0x00;
	P3M0 = 0x00;

	//����P4��Ϊ׼˫���
	P4M1 = 0x00;
	P4M0 = 0x00;
		
	//����P5��Ϊ׼˫���
	P5M1 = 0x00;
	P5M0 = 0x00;
    
	//��ʼ������
	bRS485_2_Ctrl = 0;//2#RS485���ͽ�ֹ�����ڽ���״̬��
   	bRS485_3_Ctrl = 0;//3#RS485���ͽ�ֹ�����ڽ���״̬��
	bRS485_4_Ctrl = 0;//4#RS485���ͽ�ֹ�����ڽ���״̬��
}