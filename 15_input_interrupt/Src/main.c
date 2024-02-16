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

static void exti_callback(void);

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);


	pc13_exti_init();
	uart2_tx_init();

	while(1)
	{



	}
}

// callback function to deal with interrupt
static void exti_callback(void)
{
	printf("BTN PRESSED...\n\r");
	GPIOA->ODR ^= LED;

}

void EXTI15_10_IRQHandler(void)
{
	// in startup.s file line 185 shows that this function needs the name of the interrupt name
	// the handler = g_pfnVectors name
	// all interrupts are found in the startup.s file
	// to read a bit you need to use the and operand
	// the interrupt is occurred
	if ((EXTI->PR & LINE13) != 0)
	{
		// clear the pr flag to re-arm it
		EXTI->PR |= LINE13;

		// do something ONCE INTERRUPT OCCURRED
		exti_callback();

	}

}
