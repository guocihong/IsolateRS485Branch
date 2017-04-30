#include "driver/timer/timer_drv.h"

/* UART2 */
extern xdata  Byte        recv2_state;                 //receive state
extern xdata  Byte        recv2_timer;                 //receive time-out, �����ֽڼ䳬ʱ�ж�

/* UART3 */
extern xdata  Byte        recv3_state;                 //receive state
extern xdata  Byte        recv3_timer;                 //receive time-out, �����ֽڼ䳬ʱ�ж�

/* UART4 */
extern xdata  Byte        recv4_state;                 //receive state
extern xdata  Byte        recv4_timer;                 //receive time-out, �����ֽڼ䳬ʱ�ж�

void timer0_init(void)   // 5ms@22.1184MHz
{    
    // ��ʱ��0��ʼ��	
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��0����ģʽΪ��ʽ0��16λ�Զ���װ��ʱ��
	TL0 = 0x00;		    //���ö�ʱ��ֵ
	TH0 = 0xDC;		    //���ö�ʱ��ֵ
	TF0 = 0;		    //���TF0��־
	ET0 = 1;            //ʹ��T0�ж�����λ
	PT0 = 0;            //�����ж����ȼ�Ϊ���ȼ�1
	TR0 = 1;		    //��ʱ��0��ʼ��ʱ
}

void timer0_isr(void) interrupt TIMER0_VECTOR
{            
	// UART2�ֽ�֮����ճ�ʱ
	if (recv2_state != FSA_INIT) { 
		//�ǳ�ʼ״̬����Ҫ����Ƿ�ʱ
		if (recv2_timer > 0) {
			recv2_timer--;
		}
		
		if (recv2_timer == 0) {
			recv2_state = FSA_INIT;   //���ճ�ʱ, �ָ�����ʼ״̬			
		}
	}
	
	// UART3�ֽ�֮����ճ�ʱ
	if (recv3_state != FSA_INIT) {
		//�ǳ�ʼ״̬����Ҫ����Ƿ�ʱ
		if (recv3_timer > 0) {
			recv3_timer--;
		}
		
		if (recv3_timer == 0){
			recv3_state = FSA_INIT;   //���ճ�ʱ, �ָ�����ʼ״̬
		}
	}
	
	// UART4�ֽ�֮����ճ�ʱ
	if (recv4_state != FSA_INIT) { 
		//�ǳ�ʼ״̬����Ҫ����Ƿ�ʱ
		if (recv4_timer > 0) {
			recv4_timer--;
		}
		
		if (recv4_timer == 0) {
			recv4_state = FSA_INIT;   //���ճ�ʱ, �ָ�����ʼ״̬			
		}
	}
}