//in reference manual user push button is in PC13 pin 2
// this good for sensors
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

uint32_t sensor_value;

int main(void)
{
	uart2_tx_init();
	pa1_adc_interrupt_init();
	start_conversion();

	while(1)
	{


	}
}


static void adc_callback(void)
{
	// dont want to read_adc because we should just be checking the contents of the register
	sensor_value = ADC1->DR;
	printf("Sensor Values : %d \n\r", (int)sensor_value);
}

void ADC_IRQHandler(void)
{
	// check if end of conversion flag is raised in SR
	// IF NOT SET
	if((ADC1->SR & SR_EOC) !=0)
	{
		//clear eoc by disabling
		ADC1->SR &= ~SR_EOC;
		//do something
		adc_callback();

	}
}


