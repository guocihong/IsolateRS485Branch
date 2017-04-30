#include "config.h"

/* UART2 */
xdata  Byte        recv2_buf[MAX_RecvFrame];    // receiving buffer
xdata  Byte        recv2_state;                 // receive state
xdata  Byte        recv2_timer;                 // receive time-out, 用于字节间超时判定
xdata  Byte        recv2_chksum;                // computed checksum
xdata  Byte        recv2_ctr;                   // reveiving pointer

xdata  Byte        trans2_buf[MAX_TransFrame];  // uart transfer message buffer
xdata  Byte        trans2_ctr;                  // transfer pointer
xdata  Byte        trans2_size;                 // transfer bytes number
xdata  Byte        trans2_chksum;               // computed check-sum of already transfered message

xdata  Byte        uart2_q_index;               // 正在发送某队列项的序号：若为0xFF, 表示没有任何项进入发送流程
xdata  sUART_Q     uart2_send_queue[UART_QUEUE_NUM];     // 串口发送队列
xdata  sUART_Q     uart2_recv_queue[UART_QUEUE_NUM];     // 串口接收队列

/* UART3 */
xdata  Byte        recv3_buf[MAX_RecvFrame];    // receiving buffer
xdata  Byte        recv3_state;                 // receive state
xdata  Byte        recv3_timer;                 // receive time-out, 用于字节间超时判定
xdata  Byte        recv3_chksum;                // computed checksum
xdata  Byte        recv3_ctr;                   // reveiving pointer

xdata  Byte        trans3_buf[MAX_TransFrame];  // uart transfer message buffer
xdata  Byte        trans3_ctr;                  // transfer pointer
xdata  Byte        trans3_size;                 // transfer bytes number
xdata  Byte        trans3_chksum;               // computed check-sum of already transfered message

xdata  Byte        uart3_q_index;               // 正在发送某队列项的序号：若为0xFF, 表示没有任何项进入发送流程
xdata  sUART_Q     uart3_send_queue[UART_QUEUE_NUM];     // 串口发送队列
xdata  sUART_Q     uart3_recv_queue[UART_QUEUE_NUM];     // 串口接收队列

/* UART4 */
xdata  Byte        recv4_buf[MAX_RecvFrame];    // receiving buffer
xdata  Byte        recv4_state;                 // receive state
xdata  Byte        recv4_timer;                 // receive time-out, 用于字节间超时判定
xdata  Byte        recv4_chksum;                // computed checksum
xdata  Byte        recv4_ctr;                   // reveiving pointer

xdata  Byte        trans4_buf[MAX_TransFrame];  // uart transfer message buffer
xdata  Byte        trans4_ctr;                  // transfer pointer
xdata  Byte        trans4_size;                 // transfer bytes number
xdata  Byte        trans4_chksum;               // computed check-sum of already transfered message

xdata  Byte        uart4_q_index;               // 正在发送某队列项的序号：若为0xFF, 表示没有任何项进入发送流程
xdata  sUART_Q     uart4_send_queue[UART_QUEUE_NUM];     // 串口发送队列
xdata  sUART_Q     uart4_recv_queue[UART_QUEUE_NUM];     // 串口接收队列