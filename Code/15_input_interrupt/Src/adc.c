#include "stm32f4xx.h"
#include "adc.h"

//#define APB2ENR		(0x44)

// module has a channel that need to be configure in the analog mode
// which pins are connected to the ADC module? answer will be the configuration
#define ADC1EN		 	(1U<<8)
#define GPIOAEN 	 	(1U<<0)
#define ADC_CH1		 	(1U<<0)
#define ADC_SEQ_LEN_1	0x00
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define SR_EOC			(1U<<1)
#define CR2_CONT		(1U<<1)





void pa1_adc_init(void)
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

	// Configure ADC parameters
	ADC1->SQR3 = ADC_CH1;
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	ADC1->CR2 = CR2_ADON;
}


void start_converstion(void)
{
	// enable continuous converstion
	ADC1->CR2 |= CR2_CONT;

	// start adc convertion
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	// wait for conversion to complete
	while(!(ADC1->SR & SR_EOC)){}
	// read converted result
	return (ADC1->DR);
}
