#include "task/uart/uart_task.h"

#define REPLY_DLY      (100/SCHEDULER_TICK)         //收到PC命令后的应答延时

/* UART2 */
extern xdata  Byte     recv2_buf[MAX_RecvFrame];    // receiving buffer
extern xdata  Byte     recv2_state;                 // receive state
extern xdata  Byte     recv2_timer;                 // receive time-out, 用于字节间超时判定
extern xdata  Byte     recv2_chksum;                // computed checksum
extern xdata  Byte     recv2_ctr;                   // reveiving pointer

extern xdata  Byte     trans2_buf[MAX_TransFrame];  // uart transfer message buffer
extern xdata  Byte     trans2_ctr;                  // transfer pointer
extern xdata  Byte     trans2_size;                 // transfer bytes number
extern xdata  Byte     trans2_chksum;               // computed check-sum of already transfered message

extern xdata  Byte     uart2_q_index;               // 正在发送某队列项的序号：若为0xFF, 表示没有任何项进入发送流程
extern xdata  sUART_Q  uart2_send_queue[UART_QUEUE_NUM];     // 串口发送队列
extern xdata  sUART_Q  uart2_recv_queue[UART_QUEUE_NUM];     // 串口接收队列

/* UART3 */
extern xdata  Byte     recv3_buf[MAX_RecvFrame];    // receiving buffer
extern xdata  Byte     recv3_state;                 // receive state
extern xdata  Byte     recv3_timer;                 // receive time-out, 用于字节间超时判定
extern xdata  Byte     recv3_chksum;                // computed checksum
extern xdata  Byte     recv3_ctr;                   // reveiving pointer

extern xdata  Byte     trans3_buf[MAX_TransFrame];  // uart transfer message buffer
extern xdata  Byte     trans3_ctr;                  // transfer pointer
extern xdata  Byte     trans3_size;                 // transfer bytes number
extern xdata  Byte     trans3_chksum;               // computed check-sum of already transfered message

extern xdata  Byte     uart3_q_index;               // 正在发送某队列项的序号：若为0xFF, 表示没有任何项进入发送流程
extern xdata  sUART_Q  uart3_send_queue[UART_QUEUE_NUM];     // 串口发送队列
extern xdata  sUART_Q  uart3_recv_queue[UART_QUEUE_NUM];     // 串口接收队列

/* UART4 */
extern xdata  Byte     recv4_buf[MAX_RecvFrame];    // receiving buffer
extern xdata  Byte     recv4_state;                 // receive state
extern xdata  Byte     recv4_timer;                 // receive time-out, 用于字节间超时判定
extern xdata  Byte     recv4_chksum;                // computed checksum
extern xdata  Byte     recv4_ctr;                   // reveiving pointer

extern xdata  Byte     trans4_buf[MAX_TransFrame];  // uart transfer message buffer
extern xdata  Byte     trans4_ctr;                  // transfer pointer
extern xdata  Byte     trans4_size;                 // transfer bytes number
extern xdata  Byte     trans4_chksum;               // computed check-sum of already transfered message

extern xdata  Byte     uart4_q_index;               // 正在发送某队列项的序号：若为0xFF, 表示没有任何项进入发送流程
extern xdata  sUART_Q  uart4_send_queue[UART_QUEUE_NUM];     // 串口发送队列
extern xdata  sUART_Q  uart4_recv_queue[UART_QUEUE_NUM];     // 串口接收队列

void uart_task_init(void)
{
	Byte i;
   
	//uart2相关变量初始化
	recv2_state = FSA_INIT;
	recv2_timer = 0;
	recv2_ctr = 0;
	recv2_chksum = 0;
	trans2_size = 0;
	trans2_ctr = 0;

	for (i = 0; i < UART_QUEUE_NUM; i++){
		uart2_send_queue[i].flag = 0; //均空闲
		uart2_recv_queue[i].flag = 0; //均空闲
	}
	uart2_q_index = 0xFF;    //无队列项进入发送流程

	//uart3相关变量初始化
	recv3_state = FSA_INIT;
	recv3_timer = 0;
	recv3_ctr = 0;
	recv3_chksum = 0;
	trans3_size = 0;
	trans3_ctr = 0;

	for (i = 0; i < UART_QUEUE_NUM; i++){
		uart3_send_queue[i].flag = 0; //均空闲
		uart3_recv_queue[i].flag = 0; //均空闲
	}
	uart3_q_index = 0xFF;    //无队列项进入发送流程

	//uart4相关变量初始化
	recv4_state = FSA_INIT;
	recv4_timer = 0;
	recv4_ctr = 0;
	recv4_chksum = 0;
	trans4_size = 0;
	trans4_ctr = 0;

	for (i = 0; i < UART_QUEUE_NUM; i++){
		uart4_send_queue[i].flag = 0; //均空闲
		uart4_recv_queue[i].flag = 0; //均空闲
	}
	uart4_q_index = 0xFF;    //无队列项进入发送流程

	//UART硬件初始化
	uart_init();             //之后，已经准备好串口收发，只是还未使能全局中断
}

void uart_task(void)
{
    Byte i,k;
    Byte *ptr;
    
    //处理UART4：来自上位机的数据包
	//1、UART4接收队列是否有等待转发的数据包
	for (k = 0; k < UART_QUEUE_NUM; k++)
	{
		if (uart4_recv_queue[k].flag == 1)//有等待转发的数据包
		{
			ptr = uart4_recv_queue[k].tdata;
			
			//1.1、在UART2发送队列中找空闲Buffer
            i = uart2_get_send_buffer();
            if (i < UART_QUEUE_NUM) {
                //找到了空闲buffer, 写入data
                uart2_send_queue[i].tdata[0] = FRAME_STX;
                memcpy(&uart2_send_queue[i].tdata[1], ptr, ptr[2] + 3);
                uart2_send_queue[i].len = ptr[2] + 5;
            } 
            
            //1.2、在UART3发送队列中找空闲Buffer
            i = uart3_get_send_buffer();
            if (i < UART_QUEUE_NUM) {
                //找到了空闲buffer, 写入data
                uart3_send_queue[i].tdata[0] = FRAME_STX;
                memcpy(&uart3_send_queue[i].tdata[1], ptr, ptr[2] + 3);
                uart3_send_queue[i].len = ptr[2] + 5;
            }

            //1.3、处理完成,释放该队列项
			uart4_recv_queue[k].flag = 0;
            
            break;
        }
    }

	//处理UART2：来自下位机的数据包
    //2、UART2接收队列是否有等待转发的数据包
	for (k = 0; k < UART_QUEUE_NUM; k++)
	{
		if (uart2_recv_queue[k].flag == 1)//有等待转发的数据包
		{
			ptr = uart2_recv_queue[k].tdata;
			
			//转发此命令,在UART4发送队列中找空闲Buffer
			i = uart4_get_send_buffer();
			if (i < UART_QUEUE_NUM) {
				//找到了空闲buffer, 写入data               
				uart4_send_queue[i].tdata[0] = FRAME_STX;
				memcpy(&uart4_send_queue[i].tdata[1], ptr, ptr[2] + 3);
				uart4_send_queue[i].len = ptr[2] + 5;
			}
			
			//处理完成,释放该队列项
			uart2_recv_queue[k].flag = 0;

			break;
		}
	}    
    
    //处理UART3：来自下位机的数据包
    //3、UART3接收队列是否有等待转发的数据包
	for (k = 0; k < UART_QUEUE_NUM; k++)
	{
		if (uart3_recv_queue[k].flag == 1)//有等待转发的数据包
		{
			ptr = uart3_recv_queue[k].tdata;
			
			//转发此命令,在UART4发送队列中找空闲Buffer
			i = uart4_get_send_buffer();
			if (i < UART_QUEUE_NUM) {
				//找到了空闲buffer, 写入data               
				uart4_send_queue[i].tdata[0] = FRAME_STX;
				memcpy(&uart4_send_queue[i].tdata[1], ptr, ptr[2] + 3);
				uart4_send_queue[i].len = ptr[2] + 5;
			}
			
			//处理完成,释放该队列项
			uart3_recv_queue[k].flag = 0;

			break;
		}
	}   
    
    //4. UART4 队列发送
	if ((uart4_q_index == 0xFF) && (recv4_state == FSA_INIT)) {
		//UART4无进入发送流程的队列项, 找是否有等待发送的项
		for (i = 0; i < UART_QUEUE_NUM; i++) {
			if (uart4_send_queue[i].flag == 1){
                //来自下位机的数据包:有等待发送的项，安排此项发送
				uart4_send_queue[i].flag = 2;
				uart4_q_index = i;
				memcpy(trans4_buf, uart4_send_queue[i].tdata, uart4_send_queue[i].len - 1);
				trans4_size = uart4_send_queue[i].len;
				uart4_start_trans();
				break;
			}
		}
	}
    
    //5. UART3 队列发送
	if ((uart3_q_index == 0xFF) && (recv3_state == FSA_INIT)) {
		//UART3无进入发送流程的队列项, 找是否有等待发送的项
		for (i = 0; i < UART_QUEUE_NUM; i++) {
			if (uart3_send_queue[i].flag == 1){
                //来自上位机的数据包:有等待发送的项，安排此项发送
				uart3_send_queue[i].flag = 2;
				uart3_q_index = i;
				memcpy(trans3_buf, uart3_send_queue[i].tdata, uart3_send_queue[i].len - 1);
				trans3_size = uart3_send_queue[i].len;
				uart3_start_trans();
				break;
			}
		}
	}

    //6. UART2 队列发送
	if ((uart2_q_index == 0xFF) && (recv2_state == FSA_INIT)) {
		//UART2无进入发送流程的队列项, 找是否有等待发送的项
		for (i = 0; i < UART_QUEUE_NUM; i++) {
			if (uart2_send_queue[i].flag == 1){
                //来自上位机的数据包:有等待发送的项，安排此项发送
				uart2_send_queue[i].flag = 2;
				uart2_q_index = i;
				memcpy(trans2_buf, uart2_send_queue[i].tdata, uart2_send_queue[i].len - 1);
				trans2_size = uart2_send_queue[i].len;
				uart2_start_trans();
				break;
			}
		}
	}
}

Byte uart2_get_send_buffer(void)
{
	Byte i, flag;

	for (i = 0; i < UART_QUEUE_NUM; i++)
	{
		Disable_interrupt();
		flag = uart2_send_queue[i].flag;
		Enable_interrupt();
		if (flag == 0)   //已找到空闲Buffer
		{
			uart2_send_queue[i].flag = 1;
			break;
		}
	}
	return i;
}


Byte uart2_get_recv_buffer(void)
{
	Byte i, flag;

	for (i = 0; i < UART_QUEUE_NUM; i++)
	{
		Disable_interrupt();
		flag = uart2_recv_queue[i].flag;
		Enable_interrupt();
		if (flag == 0)   //已找到空闲Buffer
		{
			uart2_recv_queue[i].flag = 1;
			break;
		}
	}
	return i;
}

Byte uart3_get_send_buffer(void)
{
	Byte i, flag;

	for (i = 0; i < UART_QUEUE_NUM; i++)
	{
		Disable_interrupt();
		flag = uart3_send_queue[i].flag;
		Enable_interrupt();
		if (flag == 0)   //已找到空闲Buffer
		{
			uart3_send_queue[i].flag = 1;
			break;
		}
	}
	return i;
}

Byte uart3_get_recv_buffer(void)
{
	Byte i, flag;

	for (i = 0; i < UART_QUEUE_NUM; i++)
	{
		Disable_interrupt();
		flag = uart3_recv_queue[i].flag;
		Enable_interrupt();
		if (flag == 0)   //已找到空闲Buffer
		{
			uart3_recv_queue[i].flag = 1;
			break;
		}
	}
	return i;
}

Byte uart4_get_send_buffer(void)
{
	Byte i, flag;

	for (i = 0; i < UART_QUEUE_NUM; i++)
	{
		Disable_interrupt();
		flag = uart4_send_queue[i].flag;
		Enable_interrupt();
		if (flag == 0)   //已找到空闲Buffer
		{
			uart4_send_queue[i].flag = 1;
			break;
		}
	}
	return i;
}

Byte uart4_get_recv_buffer(void)
{
	Byte i, flag;

	for (i = 0; i < UART_QUEUE_NUM; i++)
	{
		Disable_interrupt();
		flag = uart4_recv_queue[i].flag;
		Enable_interrupt();
		if (flag == 0)   //已找到空闲Buffer
		{
			uart4_recv_queue[i].flag = 1;
			break;
		}
	}
	return i;
}