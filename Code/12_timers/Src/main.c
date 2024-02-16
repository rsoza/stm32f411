//in reference manual user push button is in PC13 pin 2
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOAEN	(1U<<0)
#define PIN5	(1U<<5)
#define LED		PIN5

int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	uart2_tx_init();
	tim2_1hz_init();

	while(1)
	{
//		 wait for UIF, IF THIS IS FALSE GET STUCK HERE
		while (!(TIM2->SR & SR_UIF)) {}

		// CLEAR UIF, ONCE UIF IS TRUE CLEAR IT
		TIM2->SR &=~SR_UIF;

		printf("A second passed !! \n\r");
		GPIOA->ODR ^=LED;
	}
}

