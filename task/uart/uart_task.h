#ifndef _UART_TASK_H_
#define _UART_TASK_H_

#include "driver/uart/uart_drv.h"
#include "config.h"

void uart_task_init(void);
void uart_task(void);

Byte uart2_get_recv_buffer(void);
Byte uart2_get_send_buffer(void);

Byte uart3_get_recv_buffer(void);
Byte uart3_get_send_buffer(void);

Byte uart4_get_recv_buffer(void);
Byte uart4_get_send_buffer(void);
#endif