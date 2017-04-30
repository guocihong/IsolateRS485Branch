#include "driver/timer/timer_drv.h"

/* UART2 */
extern xdata  Byte        recv2_state;                 //receive state
extern xdata  Byte        recv2_timer;                 //receive time-out, 用于字节间超时判定

/* UART3 */
extern xdata  Byte        recv3_state;                 //receive state
extern xdata  Byte        recv3_timer;                 //receive time-out, 用于字节间超时判定

/* UART4 */
extern xdata  Byte        recv4_state;                 //receive state
extern xdata  Byte        recv4_timer;                 //receive time-out, 用于字节间超时判定

void timer0_init(void)   // 5ms@22.1184MHz
{    
    // 定时器0初始化	
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器0工作模式为方式0：16位自动重装定时器
	TL0 = 0x00;		    //设置定时初值
	TH0 = 0xDC;		    //设置定时初值
	TF0 = 0;		    //清除TF0标志
	ET0 = 1;            //使能T0中断允许位
	PT0 = 0;            //设置中断优先级为优先级1
	TR0 = 1;		    //定时器0开始计时
}

void timer0_isr(void) interrupt TIMER0_VECTOR
{            
	// UART2字节之间接收超时
	if (recv2_state != FSA_INIT) { 
		//非初始状态，需要检测是否超时
		if (recv2_timer > 0) {
			recv2_timer--;
		}
		
		if (recv2_timer == 0) {
			recv2_state = FSA_INIT;   //接收超时, 恢复至初始状态			
		}
	}
	
	// UART3字节之间接收超时
	if (recv3_state != FSA_INIT) {
		//非初始状态，需要检测是否超时
		if (recv3_timer > 0) {
			recv3_timer--;
		}
		
		if (recv3_timer == 0){
			recv3_state = FSA_INIT;   //接收超时, 恢复至初始状态
		}
	}
	
	// UART4字节之间接收超时
	if (recv4_state != FSA_INIT) { 
		//非初始状态，需要检测是否超时
		if (recv4_timer > 0) {
			recv4_timer--;
		}
		
		if (recv4_timer == 0) {
			recv4_state = FSA_INIT;   //接收超时, 恢复至初始状态			
		}
	}
}