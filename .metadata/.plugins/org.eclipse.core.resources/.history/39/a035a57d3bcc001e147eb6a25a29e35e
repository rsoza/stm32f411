//in reference manual user push button is in PC13 pin 2
// this good for sensors
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

#define GPIOAEN	(1U<<0)
#define PIN5	(1U<<5)
#define LED		PIN5

char key;

static void uart_callback(void);

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);


//	uart2_rx_interrupt_init();
	uart2_tx_interrupt_init();

	while(1)
	{

	}
}

static void uart_callback(void){
	key = USART2->DR;
	if(key == '1'){
		GPIOA->ODR |= LED;

	}
	else{
		GPIOA->ODR &= ~LED;
	}
}

void USART2_IRQHandler(void)
{
	//check if RXNE is set
	if (USART2->SR & SR_TXE)
	{
		// sets key to data in usart
		//do something
		uart_callback();

	}
}


