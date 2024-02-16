//in reference manual user push button is in PC13 pin 2
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN		(1U<<0)
#define GPIOA_5		(1U<<5)
#define LED_PIN		GPIOA_5

char key;

int main(void)
{
	// enable clock access to led
	RCC->AHB1ENR |= GPIOAEN;

	//SET PA4 AS OUTPUT PIN
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart2_rxtx_init();

	while(1)
	{
		key = uart2_read();
		if (key == '1')
		{
			GPIOA->ODR |= LED_PIN;
		}
		else{
			GPIOA->ODR &= ~LED_PIN;

		}
	}
}


