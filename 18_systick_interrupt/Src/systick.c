#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL		16000
#define CTRL_ENABLE				(1U<<0)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)
#define CTRL_TICKINT			(1U<<1)

//default frequency of system
#define ONE_SEC_LOAD			(16000000)

void systickDelayMs(int delay)
{
	//configure systick::
	// Reload with number of clocks per millisec
	SysTick->LOAD = SYSTICK_LOAD_VAL;
	//Clear systick current value register
	SysTick->VAL = 0;
	//Enable systick and select internal clk src
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;
	for (int i =0 ; i<delay; i++ ){
		//wait until the countflag is set
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0 ){}
	}
	SysTick->CTRL = 0;
}


void systick_1hz_interrupt(void)
{
	// happens every one second
	// reload with number of clocks per second
	SysTick->LOAD = ONE_SEC_LOAD -1 ;

	// Clear systick current value register
	SysTick->VAL = 0;

	//Enable systick and select internal clk src and ENABLE INTERRUPT
	// to find the bit for interrupt fo to Cortexm4 generic user guide
	// seach for systick
	// tickint is the enabler, make symbolic name
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;
	//ENABLE SYSTICK INTERRUPT
	SysTick->CTRL |= CTRL_TICKINT;

}
