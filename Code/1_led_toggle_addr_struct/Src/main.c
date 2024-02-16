#include <stdint.h>


#define PERIPH_BASE			(0x40000000UL) // 4000 0000
#define AHB1PERIPH_OFFSET	(0x00020000UL) // 0002 0000

//starting point
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET) // 4002 0000

#define GPIOA_OFFSET		(0x0000UL) // hex =32 bit values, doesn't matter if it is 4 or 8 digits
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET) // 4002 0000

#define RCC_OFFSET			(0x3800UL) // this equals 0x0000 38000
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET) // 4002 3800


#define GPIOAEN				(1U<<0)

// PIN5 set
#define PIN5				(1U<<5)
#define LED_PIN				PIN5




typedef struct
{
	volatile uint32_t DUMMY[12]; //each 4 bytes
	volatile uint32_t AHB1ENR;
} RCC_TypeDef;

typedef struct
{
	volatile uint32_t MODER; 	// GPIO port mode register			Address Offset: 0x00
	volatile uint32_t DUMMY[4]; // keeps address in place
	volatile uint32_t ODR;		// GPIO port output data register	Address Offset: 0x14
} GPIOA_TypeDef;


#define RCC		((RCC_TypeDef*) RCC_BASE)
#define GPIOA	((GPIOA_TypeDef*) GPIOA_BASE)

int main(void)
{
	// 1. Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// 2. Set PA5 as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1){
		// 4. Experiment 2: toggle PA5 on/off
		GPIOA->ODR ^= LED_PIN;
		for (int i =0; i<100000;i++) {
		}
	}
}