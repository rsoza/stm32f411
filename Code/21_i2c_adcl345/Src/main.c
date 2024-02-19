// transfer the uart data (tx using dma)

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



static void dma_callback(void);

int main(void)
{
	char message[31] = "Hello from Stm32 DMA transfer\n\r";



	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	uart2_tx_init();
	// destination is the DMA data register
	// use & for the address of USART2 data register
	dma1_stream6_init((uint32_t) message, (uint32_t) &USART2->DR, 31);

	while(1)
	{

	}
}

static void dma_callback(void)
{
	GPIOA->ODR |= LED;

}

// handler name is found in the IRQ
void DMA1_Stream6_IRQHandler(void)
{
	// when any interrupt occurs run this
	// in ref manual, look for DMA_HISR
	// high interrupt status register
	// TCIF6 is the transfer complete

	/*Check for transfer complete interrupt*/
	// use if for check, while for wait
	if(DMA1->HISR & HISR_TCIF6)
	{
		/*CLEAR FLAG*/
		// look for HIFCR in DMA
		DMA1->HIFCR |= HIFCR_CTCIF6;

		/*DO SOMETHING*/
		dma_callback();
	}
}
