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
#define	MAX_RecvFrame     50                       // 接收缓存区大小
#define	MAX_TransFrame    50                       // 发送缓存区大小
#define RECV_TIMEOUT       4                       // 字节间的最大时间间隔, 单位为tick
                                                   // 最小值可以为1,如果为0则表示不进行超时判定                                    
/* state constant(仅用于接收) */                    
#define FSA_INIT            0                      //等待帧头
#define FSA_ADDR_D          1                      //等待目的地址
#define FSA_ADDR_S          2                      //等待源地址
#define FSA_LENGTH          3                      //等待长度字节
#define FSA_DATA            4                      //等待命令串(包括 命令ID 及 参数)
#define FSA_CHKSUM          5                      //等待校验和

/* Uart Queue */
typedef struct strUART_Q
{
  Byte  flag;                                      //状态： 0 - 空闲； 1 - 等待发送； 2 - 正在发送; 3 - 已发送，等待应答
  Byte  tdata[MAX_TransFrame];                     //数据包(最后一个校验字节可以不提前计算，而在发送时边发送边计算)
  Byte  len;					                   //数据包有效长度(含校验字节)
  Byte  package_type;                              //0-来自下位机的数据包;1-设备自身的数据包
}sUART_Q;

#define UART_QUEUE_NUM      8                      //UART 队列数
           
#define bRS485_2_Ctrl       P00                    //推挽输出，RS485发送使能: 1-允许发送; 0 - 禁止发送(接收)
#define bRS485_3_Ctrl       P01                    //推挽输出，RS485发送使能: 1-允许发送; 0 - 禁止发送(接收)
#define bRS485_4_Ctrl       P02                    //推挽输出，RS485发送使能: 1-允许发送; 0 - 禁止发送(接收)

/* interrupt enable */
#define Enable_interrupt()  (EA = 1)
#define Disable_interrupt() (EA = 0)

#endif