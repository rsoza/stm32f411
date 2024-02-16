//in reference manual user push button is in PC13 pin 2
#include "stm32f4xx.h"



#define GPIOAEN 	(1U<<0)
#define GPIOCEN 	(1U<<2)

#define PIN5		(1U<<5)
#define PIN13		(1U<<13)

#define LED_PIN		PIN5
#define BTN_PIN		PIN13


int main(void)
{

//	Enable clock access to GPIOA and GPIOC
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

//	Set PA5 as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

//	Set PC13 as input pin, look for moder13 in ref manual
//	for input both bits need to set to zero
	GPIOC->MODER &=~ (0U<<26);
	GPIOC->MODER &=~ (0U<<27);


	while(1)
	{

//		CHECK IF BTN IS pressed
//		IDR13 represents input on pin 13
		if(GPIOC->IDR & BTN_PIN)
		{
//			turn on led
		GPIOA->BSRR = LED_PIN;
		}
		else {
//			turn off
		GPIOA->BSRR = (1U<<21);
		}
	}
}
