//in reference manual user push button is in PC13 pin 2
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"



int main(void)
{

	tim2_pa5_output_compare();

	while(10000000)
	{

	}
}


