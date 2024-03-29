#include "uart.h"

#define GPIOAEN 	(1U<<0)
#define UART2EN 	(1U<<17)

#define CR1_TE		(1U<<3)
#define CR1_RE		(1U<<2)

#define CR1_UE		(1U<<13)


#define CR1_RXNEIE (1U<<5)
#define CR1_TXEIE  (1U<<7)


// symbolic name to set clock tree
#define SYS_FREQ	(16000000)
#define APB1_CLK	SYS_FREQ

// popular baudrate
#define UART_BAUDRATE	115200



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}


void uart2_rx_interrupt_init(void)
{
	// in ref manual look for usart_cr1
	// Nominate RXNEIE: EIE = enroute enable


	//1. Configure the UART GPIO pin(s) - just TX
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);


	GPIOA->AFR[0] |=  (1U<<8);
	GPIOA->AFR[0] |=  (1U<<9);
	GPIOA->AFR[0] |=  (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	// set PA3 mode to alternate function mode for rx
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	// set PA3 alternate function type to UART_RX (AF07)
	GPIOA->AFR[0] |=  (1U<<12);
	GPIOA->AFR[0] |=  (1U<<13);
	GPIOA->AFR[0] |=  (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);

	//2. Configure UARR module
	RCC->APB1ENR |= UART2EN;

	// Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure the transfer direction: enables transmitter and receiver
	USART2->CR1 = (CR1_TE | CR1_RE); // USART_CR1 RE mean receiver enable






	// ADD EN ROUTE, ADD INTERRUPT
	USART2->CR1 |= CR1_RXNEIE;
	// ENABLE UART2 INTERRUPT IN NVIC
	NVIC_EnableIRQ(USART2_IRQn);




	// Configure the transfer direction
	USART2->CR1 |= CR1_UE;
}


void uart2_tx_interrupt_init(void)
{
	// in ref manual look for usart_cr1
	// Nominate RXNEIE: EIE = enroute enable


	//1. Configure the UART GPIO pin(s) - just TX
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);


	GPIOA->AFR[0] |=  (1U<<8);
	GPIOA->AFR[0] |=  (1U<<9);
	GPIOA->AFR[0] |=  (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	// set PA3 mode to alternate function mode for rx
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	// set PA3 alternate function type to UART_RX (AF07)
	GPIOA->AFR[0] |=  (1U<<12);
	GPIOA->AFR[0] |=  (1U<<13);
	GPIOA->AFR[0] |=  (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);

	//2. Configure UARR module
	RCC->APB1ENR |= UART2EN;

	// Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure the transfer direction: enables transmitter and receiver
	USART2->CR1 = (CR1_TE | CR1_RE); // USART_CR1 RE mean receiver enable






	// ADD EN ROUTE, ADD INTERRUPT
	USART2->CR1 |= CR1_TXEIE;
	// ENABLE UART2 INTERRUPT IN NVIC
	NVIC_EnableIRQ(USART2_IRQn);




	// Configure the transfer direction
	USART2->CR1 |= CR1_UE;
}


void uart2_rxtx_init(void)
{
	//1. Configure the UART GPIO pin(s) - just TX
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);


	GPIOA->AFR[0] |=  (1U<<8);
	GPIOA->AFR[0] |=  (1U<<9);
	GPIOA->AFR[0] |=  (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	// set PA3 mode to alternate function mode for rx
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	// set PA3 alternate function type to UART_RX (AF07)
	GPIOA->AFR[0] |=  (1U<<12);
	GPIOA->AFR[0] |=  (1U<<13);
	GPIOA->AFR[0] |=  (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);

	//2. Configure UARR module
	RCC->APB1ENR |= UART2EN;

	// Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure the transfer direction: enables transmitter and receiver
	USART2->CR1 = (CR1_TE | CR1_RE); // USART_CR1 RE mean receiver enable

	// Configure the transfer direction
	USART2->CR1 |= CR1_UE;
}



void uart2_tx_init(void)
{
	//1. Configure the UART GPIO pin(s) - just TX
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA2 mode to alternate function mode
	// go to ref manual:moder, identify pin2
	// moder2 has pins 4 and 5 and alternate function mode is 10
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	// Set PA2 alternate function typer to UART_TX (AF07)
	// scroll down from moder to alternate function low register: AFRL takes care of pins 1-7
	// while high register is for pins 8-15
	// AFRL2 occupies bit 8-11 and we want AF7:: 0111
	// little endian
	GPIOA->AFR[0] |=  (1U<<8);
	GPIOA->AFR[0] |=  (1U<<9);
	GPIOA->AFR[0] |=  (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);


	//2. Configure UARR module
	// Enable clock access to UART2
	RCC->APB1ENR |= UART2EN;

	// Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// Configure the transfer direction
	// just the TX
	// go to ref manual, search USART_CR1
	// bit 3 says TE: transmitter enable, set this to one to enable
	// we are erasing everything in this register to set to 1
	USART2->CR1 = CR1_TE;
	// Enable the UART module, once done
	// do not want to clean everything, want to add UE bit to the state of TE
	USART2->CR1 |= CR1_UE;
}

char uart2_read(void)
{
	// make sure the receive data register is not empty
	// aka RXNE flag
	// to wait we use while, to check us if
	while (!(USART2->SR & SR_RXNE)){}
	// Read data
	return USART2->DR;
}

void uart2_write(int ch)
{
	// two registers: transmit data register and receive data register
	// this does two things:
	// 1. Make sure the transmit data register is empty
	// read bit by using and operator if the register is true it will set this bit
	while (!(USART2->SR & SR_TXE)){}

	// 2. Write to transmit data register
	// transmits 8 bits
	USART2->DR = (ch & 0xFF);
	// search in the ref manual for the status register: USART_SR
	// bit 7 TXE = Transmit data register empty: make this a symbolic name

}



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/ BaudRate);
}

