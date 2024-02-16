//bit set reset register
//go to reference many search for bsrr
// this resets the pin to normal status aka turn off


#include "stm32f4xx.h"



#define GPIOAEN 	(1U<<0)
#define PIN5		(1U<<5)
#define LED_PIN		PIN5


int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1)
	{
		GPIOA->BSRR = LED_PIN;
		for(int i =0; i <100000; i++){}

//		set 21 to 1 because the ref manual states to do so
		GPIOA->BSRR = (1U<<21);
		for(int i =0; i <100000; i++){}
	}
}
