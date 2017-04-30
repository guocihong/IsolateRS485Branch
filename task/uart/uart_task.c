#include "task/uart/uart_task.h"

#define REPLY_DLY      (100/SCHEDULER_TICK)         //�յ�PC������Ӧ����ʱ

/* UART2 */
extern xdata  Byte     recv2_buf[MAX_RecvFrame];    // receiving buffer
extern xdata  Byte     recv2_state;                 // receive state
extern xdata  Byte     recv2_timer;                 // receive time-out, �����ֽڼ䳬ʱ�ж�
extern xdata  Byte     recv2_chksum;                // computed checksum
extern xdata  Byte     recv2_ctr;                   // reveiving pointer

extern xdata  Byte     trans2_buf[MAX_TransFrame];  // uart transfer message buffer
extern xdata  Byte     trans2_ctr;                  // transfer pointer
extern xdata  Byte     trans2_size;                 // transfer bytes number
extern xdata  Byte     trans2_chksum;               // computed check-sum of already transfered message

extern xdata  Byte     uart2_q_index;               // ���ڷ���ĳ���������ţ���Ϊ0xFF, ��ʾû���κ�����뷢������
extern xdata  sUART_Q  uart2_send_queue[UART_QUEUE_NUM];     // ���ڷ��Ͷ���
extern xdata  sUART_Q  uart2_recv_queue[UART_QUEUE_NUM];     // ���ڽ��ն���

/* UART3 */
extern xdata  Byte     recv3_buf[MAX_RecvFrame];    // receiving buffer
extern xdata  Byte     recv3_state;                 // receive state
extern xdata  Byte     recv3_timer;                 // receive time-out, �����ֽڼ䳬ʱ�ж�
extern xdata  Byte     recv3_chksum;                // computed checksum
extern xdata  Byte     recv3_ctr;                   // reveiving pointer

extern xdata  Byte     trans3_buf[MAX_TransFrame];  // uart transfer message buffer
extern xdata  Byte     trans3_ctr;                  // transfer pointer
extern xdata  Byte     trans3_size;                 // transfer bytes number
extern xdata  Byte     trans3_chksum;               // computed check-sum of already transfered message

extern xdata  Byte     uart3_q_index;               // ���ڷ���ĳ���������ţ���Ϊ0xFF, ��ʾû���κ�����뷢������
extern xdata  sUART_Q  uart3_send_queue[UART_QUEUE_NUM];     // ���ڷ��Ͷ���
extern xdata  sUART_Q  uart3_recv_queue[UART_QUEUE_NUM];     // ���ڽ��ն���

/* UART4 */
extern xdata  Byte     recv4_buf[MAX_RecvFrame];    // receiving buffer
extern xdata  Byte     recv4_state;                 // receive state
extern xdata  Byte     recv4_timer;                 // receive time-out, �����ֽڼ䳬ʱ�ж�
extern xdata  Byte     recv4_chksum;                // computed checksum
extern xdata  Byte     recv4_ctr;                   // reveiving pointer

extern xdata  Byte     trans4_buf[MAX_TransFrame];  // uart transfer message buffer
extern xdata  Byte     trans4_ctr;                  // transfer pointer
extern xdata  Byte     trans4_size;                 // transfer bytes number
extern xdata  Byte     trans4_chksum;               // computed check-sum of already transfered message

extern xdata  Byte     uart4_q_index;               // ���ڷ���ĳ���������ţ���Ϊ0xFF, ��ʾû���κ�����뷢������
extern xdata  sUART_Q  uart4_send_queue[UART_QUEUE_NUM];     // ���ڷ��Ͷ���
extern xdata  sUART_Q  uart4_recv_queue[UART_QUEUE_NUM];     // ���ڽ��ն���

void uart_task_init(void)
{
	Byte i;
   
	//uart2��ر�����ʼ��
	recv2_state = FSA_INIT;
	recv2_timer = 0;
	recv2_ctr = 0;
	recv2_chksum = 0;
	trans2_size = 0;
	trans2_ctr = 0;

	for (i = 0; i < UART_QUEUE_NUM; i++){
		uart2_send_queue[i].flag = 0; //������
		uart2_recv_queue[i].flag = 0; //������
	}
	uart2_q_index = 0xFF;    //�޶�������뷢������

	//uart3��ر�����ʼ��
	recv3_state = FSA_INIT;
	recv3_timer = 0;
	recv3_ctr = 0;
	recv3_chksum = 0;
	trans3_size = 0;
	trans3_ctr = 0;

	for (i = 0; i < UART_QUEUE_NUM; i++){
		uart3_send_queue[i].flag = 0; //������
		uart3_recv_queue[i].flag = 0; //������
	}
	uart3_q_index = 0xFF;    //�޶�������뷢������

	//uart4��ر�����ʼ��
	recv4_state = FSA_INIT;
	recv4_timer = 0;
	recv4_ctr = 0;
	recv4_chksum = 0;
	trans4_size = 0;
	trans4_ctr = 0;

	for (i = 0; i < UART_QUEUE_NUM; i++){
		uart4_send_queue[i].flag = 0; //������
		uart4_recv_queue[i].flag = 0; //������
	}
	uart4_q_index = 0xFF;    //�޶�������뷢������

	//UARTӲ����ʼ��
	uart_init();             //֮���Ѿ�׼���ô����շ���ֻ�ǻ�δʹ��ȫ���ж�
}

void uart_task(void)
{
    Byte i,k;
    Byte *ptr;
    
    //����UART4��������λ�������ݰ�
	//1��UART4���ն����Ƿ��еȴ�ת�������ݰ�
	for (k = 0; k < UART_QUEUE_NUM; k++)
	{
		if (uart4_recv_queue[k].flag == 1)//�еȴ�ת�������ݰ�
		{
			ptr = uart4_recv_queue[k].tdata;
			
			//1.1����UART2���Ͷ������ҿ���Buffer
            i = uart2_get_send_buffer();
            if (i < UART_QUEUE_NUM) {
                //�ҵ��˿���buffer, д��data
                uart2_send_queue[i].tdata[0] = FRAME_STX;
                memcpy(&uart2_send_queue[i].tdata[1], ptr, ptr[2] + 3);
                uart2_send_queue[i].len = ptr[2] + 5;
            } 
            
            //1.2����UART3���Ͷ������ҿ���Buffer
            i = uart3_get_send_buffer();
            if (i < UART_QUEUE_NUM) {
                //�ҵ��˿���buffer, д��data
                uart3_send_queue[i].tdata[0] = FRAME_STX;
                memcpy(&uart3_send_queue[i].tdata[1], ptr, ptr[2] + 3);
                uart3_send_queue[i].len = ptr[2] + 5;
            }

            //1.3���������,�ͷŸö�����
			uart4_recv_queue[k].flag = 0;
            
            break;
        }
    }

	//����UART2��������λ�������ݰ�
    //2��UART2���ն����Ƿ��еȴ�ת�������ݰ�
	for (k = 0; k < UART_QUEUE_NUM; k++)
	{
		if (uart2_recv_queue[k].flag == 1)//�еȴ�ת�������ݰ�
		{
			ptr = uart2_recv_queue[k].tdata;
			
			//ת��������,��UART4���Ͷ������ҿ���Buffer
			i = uart4_get_send_buffer();
			if (i < UART_QUEUE_NUM) {
				//�ҵ��˿���buffer, д��data               
				uart4_send_queue[i].tdata[0] = FRAME_STX;
				memcpy(&uart4_send_queue[i].tdata[1], ptr, ptr[2] + 3);
				uart4_send_queue[i].len = ptr[2] + 5;
			}
			
			//�������,�ͷŸö�����
			uart2_recv_queue[k].flag = 0;

			break;
		}
	}    
    
    //����UART3��������λ�������ݰ�
    //3��UART3���ն����Ƿ��еȴ�ת�������ݰ�
	for (k = 0; k < UART_QUEUE_NUM; k++)
	{
		if (uart3_recv_queue[k].flag == 1)//�еȴ�ת�������ݰ�
		{
			ptr = uart3_recv_queue[k].tdata;
			
			//ת��������,��UART4���Ͷ������ҿ���Buffer
			i = uart4_get_send_buffer();
			if (i < UART_QUEUE_NUM) {
				//�ҵ��˿���buffer, д��data               
				uart4_send_queue[i].tdata[0] = FRAME_STX;
				memcpy(&uart4_send_queue[i].tdata[1], ptr, ptr[2] + 3);
				uart4_send_queue[i].len = ptr[2] + 5;
			}
			
			//�������,�ͷŸö�����
			uart3_recv_queue[k].flag = 0;

			break;
		}
	}   
    
    //4. UART4 ���з���
	if ((uart4_q_index == 0xFF) && (recv4_state == FSA_INIT)) {
		//UART4�޽��뷢�����̵Ķ�����, ���Ƿ��еȴ����͵���
		for (i = 0; i < UART_QUEUE_NUM; i++) {
			if (uart4_send_queue[i].flag == 1){
                //������λ�������ݰ�:�еȴ����͵�����Ŵ����
				uart4_send_queue[i].flag = 2;
				uart4_q_index = i;
				memcpy(trans4_buf, uart4_send_queue[i].tdata, uart4_send_queue[i].len - 1);
				trans4_size = uart4_send_queue[i].len;
				uart4_start_trans();
				break;
			}
		}
	}
    
    //5. UART3 ���з���
	if ((uart3_q_index == 0xFF) && (recv3_state == FSA_INIT)) {
		//UART3�޽��뷢�����̵Ķ�����, ���Ƿ��еȴ����͵���
		for (i = 0; i < UART_QUEUE_NUM; i++) {
			if (uart3_send_queue[i].flag == 1){
                //������λ�������ݰ�:�еȴ����͵�����Ŵ����
				uart3_send_queue[i].flag = 2;
				uart3_q_index = i;
				memcpy(trans3_buf, uart3_send_queue[i].tdata, uart3_send_queue[i].len - 1);
				trans3_size = uart3_send_queue[i].len;
				uart3_start_trans();
				break;
			}
		}
	}

    //6. UART2 ���з���
	if ((uart2_q_index == 0xFF) && (recv2_state == FSA_INIT)) {
		//UART2�޽��뷢�����̵Ķ�����, ���Ƿ��еȴ����͵���
		for (i = 0; i < UART_QUEUE_NUM; i++) {
			if (uart2_send_queue[i].flag == 1){
                //������λ�������ݰ�:�еȴ����͵�����Ŵ����
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
		if (flag == 0)   //���ҵ�����Buffer
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
		if (flag == 0)   //���ҵ�����Buffer
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
		if (flag == 0)   //���ҵ�����Buffer
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
		if (flag == 0)   //���ҵ�����Buffer
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
		if (flag == 0)   //���ҵ�����Buffer
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
		if (flag == 0)   //���ҵ�����Buffer
		{
			uart4_recv_queue[i].flag = 1;
			break;
		}
	}
	return i;
}