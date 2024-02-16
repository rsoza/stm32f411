#include "stm32f4xx.h"

#define GPIOAEN			(1U<<0)
#define TIM2EN			(1U<<0)
#define CR1_CEN			(1U<<0)
#define CC1E			(1U<<0)
#define AFR5_TIM		(1U<<20)

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


void tim2_pa5_output_compare(void)
{
	//Enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;
	// set pa5 to alternate function mode
	//THE FIRST BIT = 0 SECOND = 1
	// in ref search moder, moder5 := alternate function mode
	GPIOA->MODER &=~ (1U<<10);
	GPIOA->MODER |= (1U<<11);

	// set alternate function type to TIM2_ch1 (AF01)
	// page 161 AFRL5 = bits 20-23, AF01 = 0001
	GPIOA->AFR[0] |= AFR5_TIM;





	//enable clock access to timer 2
	RCC->APB1ENR |= TIM2EN;

	// set prescaler value, minus 1 because we start from zero
	TIM2->PSC = 1600 -1; //16 000 000 / 1600 = 10 000

	// set auto-reload value
	TIM2->ARR = 10000 - 1;

	// add this for output

	// set output compare toggle mode page 298 ref: toggle = 011, bit 6 is auto 0
	TIM2->CCMR1 = (1U<<4) | (1U<<5);
	// enable tim2 ch1 in compare mode
	TIM2->CCER |= CC1E;




	// clear timer counter
	// in ref manual search timx_cr1
	// CEN = counter
	TIM2->CNT = 0;

	// enable the timer
	TIM2->CR1 = CR1_CEN;


}
