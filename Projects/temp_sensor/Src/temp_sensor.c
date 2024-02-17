#include "stm32f4xx.h"
#include "temp_sensor.h"


#define ADC1EN		 	(1U<<8)
#define GPIOAEN 	 	(1U<<0)
#define ADON			(1U<<0)
#define CONT			(1U<<1)
#define SWSTART			(1U<<30)
#define SR_EOC			(1U<<1)
#define TSVREFE			(1U<<23)




void temp_sensor_init(void)
{
	// Configure the ADC GPIO pin

	// Enable clock access to ADC pin's port: GPIOA
	RCC->APB2ENR |= GPIOAEN;

	// Set the mode of PA1 to analog mode in the MODER
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	// Configure the ADC module
	// Enable clock access to ADC
	RCC->APB2ENR |= ADC1EN;

	// Configure ADC parameters to temperature sensor
	ADC1->SQR3 |= 16;
	ADC1->SQR1 = 0x00;
	//Temp sensor
	ADC->CCR |= TSVREFE;
	// Enable ADON
	ADC1->CR2 |= ADON;
	ADC1->CR2 |= CONT;
}


void start_converstion(void)
{
	// start adc convertion
	ADC1->CR2 |= SWSTART;
}

uint32_t temp_read(void)
{
	uint32_t temp = 0;
	// wait for conversion to complete
	while(!(ADC1->SR & SR_EOC)){}
	temp = ADC1->DR;
	temp -= 0.76;
	temp /= 0.0025;
	temp += 25;

	// read converted result
	return temp;
}
