//in reference manual user push button is in PC13 pin 2
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"



int main(void)
{


	uar2_tx_init();

	while(1)
	{
//		call the corrector
		printf("HI HI from STM32F4.....\n\r");
	}
}

