//in reference manual user push button is in PC13 pin 2
// this good for sensors
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"


int timestamp = 0;

// set up:: connect a jumper wire from pa5 to pa6
// nucleo guide figure 19 shows where pa5/6 are on the board
int main(void)
{
	// pin is toggled every second generating a square wave
	// signal source being captured at pa6
	tim2_pa5_output_compare();
	tim3_pa6_input_capture();

	while(1)
	{
		// wait until edge is captured
		while(!(TIM3->SR & SR_CC1IF)) {}
		// read captured value
		timestamp = TIM3->CCR1;


	}
}


