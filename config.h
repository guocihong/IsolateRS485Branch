#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "STC15.h"
#include "compiler.h"
#include <intrins.h>
#include <string.h>

/* Scheduler Tick */
#define SCHEDULER_TICK     5                       // unit is ms

//for Uart
#define	FRAME_STX         0x16                     // Frame header
#define	MAX_RecvFrame     50                       // ���ջ�������С
#define	MAX_TransFrame    50                       // ���ͻ�������С
#define RECV_TIMEOUT       4                       // �ֽڼ�����ʱ����, ��λΪtick
                                                   // ��Сֵ����Ϊ1,���Ϊ0���ʾ�����г�ʱ�ж�                                    
/* state constant(�����ڽ���) */                    
#define FSA_INIT            0                      //�ȴ�֡ͷ
#define FSA_ADDR_D          1                      //�ȴ�Ŀ�ĵ�ַ
#define FSA_ADDR_S          2                      //�ȴ�Դ��ַ
#define FSA_LENGTH          3                      //�ȴ������ֽ�
#define FSA_DATA            4                      //�ȴ����(���� ����ID �� ����)
#define FSA_CHKSUM          5                      //�ȴ�У���

/* Uart Queue */
typedef struct strUART_Q
{
  Byte  flag;                                      //״̬�� 0 - ���У� 1 - �ȴ����ͣ� 2 - ���ڷ���; 3 - �ѷ��ͣ��ȴ�Ӧ��
  Byte  tdata[MAX_TransFrame];                     //���ݰ�(���һ��У���ֽڿ��Բ���ǰ���㣬���ڷ���ʱ�߷��ͱ߼���)
  Byte  len;					                   //���ݰ���Ч����(��У���ֽ�)
  Byte  package_type;                              //0-������λ�������ݰ�;1-�豸��������ݰ�
}sUART_Q;

#define UART_QUEUE_NUM      8                      //UART ������
           
#define bRS485_2_Ctrl       P00                    //���������RS485����ʹ��: 1-������; 0 - ��ֹ����(����)
#define bRS485_3_Ctrl       P01                    //���������RS485����ʹ��: 1-������; 0 - ��ֹ����(����)
#define bRS485_4_Ctrl       P02                    //���������RS485����ʹ��: 1-������; 0 - ��ֹ����(����)

/* interrupt enable */
#define Enable_interrupt()  (EA = 1)
#define Disable_interrupt() (EA = 0)

#endif