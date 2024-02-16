/*
 * Interrupt occur when push button is pressed
 * The push button is connected to PC13
 * Configure PC13 to generate an interrupt whether a rising or falling edge is detected
 *  The change in signal creates the interrupt
 */


#include "exti.h"

#define GPIOCEN		(1U<<2)
#define SYSCFGEN	(1U<<14)

void pc13_exti_init(void)
{
	// Disable global interrupt, good practice but not required
	__disable_irq();

	// Enable clock access for GPIOC
	RCC->AHB1ENR |= GPIOCEN;

	// SET pc13 AS INPUT
	// go to moder
	// look for moder13: bits 27.26
	// for input =00
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);



	// Enable clock access to SYSCFG
	// go to ref manual, configure APB2ENR
	// bit 14: SYSCFGEN
	RCC->APB2ENR |= SYSCFGEN;


	// Select PORT C for EXTI13
	// IN REF MANUAL: SYSCFG_EXTICR
	// NEED SYSCFG_EXTICR4 because it holds 13  BITS 4-7
	// need PC so its 0 0 1 0
//					  7 6 5 4
	SYSCFG->EXTICR[3] |= (1U<<5);

	// Unmask/uncover EXTI13
	// in ref manual: EXTI_IMR : 0 = masked 1 = unmasked
	EXTI->IMR |= (1U<<13);


	// Select trigger for rising or falling edge
	// SELECT FALLING EDGE
	// EXTI_FTSR in ref
	EXTI->FTSR |= (1U<<13);

	// Enable EXTI line in NVIC
	// built in function nvic enable interrupt

	NVIC_EnableIRQ(EXTI15_10_IRQn);


	// Enable global interrupt or it wont work
	__enable_irq();
}
