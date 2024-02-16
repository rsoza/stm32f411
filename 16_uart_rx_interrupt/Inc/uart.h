/*
 * uart.h
 *
 *  Created on: Feb 11, 2024
 *      Author: rsoza
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>

#include "stm32f4xx.h"
#define SR_RXNE		(1U<<5)
#define SR_TXE		(1U<<7)


void uart2_tx_init(void);
void uart2_rxtx_init(void);
char uart2_read(void);
void uart2_rx_interrupt_init(void);
void uart2_tx_interrupt_init(void);


#endif /* UART_H_ */
