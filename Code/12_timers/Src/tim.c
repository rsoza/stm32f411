#include "stm32f4xx.h"

#define TIM2EN			(1U<<0)
#define CR1_CEN			(1U<<0)

void tim2_1hz_init(void)
{

	//enable clock access to timer 2
	RCC->APB1ENR |= TIM2EN;

	// set prescaler value, minus 1 because we start from zero
	TIM2->PSC = 1600 -1; //16 000 000 / 1600 = 10 000

	// set auto-reload value
	TIM2->ARR = 10000 - 1;

	// clear timer counter
	// in ref manual search timx_cr1
	// CEN = counter
	TIM2->CNT = 0;

	// enable the timer
	TIM2->CR1 = CR1_CEN;



}
