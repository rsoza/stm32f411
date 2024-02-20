#include "spi.h"

#define GPIOAEN			(1U<<0)
#define SPI1EN			(1U<<12)
#define CPOL			(1U<<1)
#define CPHA			(1U<<0)
#define RXONLY			(1U<<10)
#define LSB_FIRST		(1U<<7)
#define MSTR			(1U<<2)
#define DFF				(1U<11)
#define SSI				(1U<8)
#define SSM				(1U<9)
#define SPE				(1U<6)

#define SR_TXE			(1U<<1)
#define SR_BUSY			(1U<<7)
#define SR_RXNE			(1U<<0)
/*
 * PA5 -> CLK
 * PA6 -> MISO
 * PA7 -> MOSI
 * PA9 -> SS
 */

void spi_gpio_init(void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA5, PA6, PA7 mode to alternate function
	//PA5
	GPIOA->MODER &=~ (1U<<10);
	GPIOA->MODER |= (1U<<11);
	//PA6
	GPIOA->MODER &=~ (1U<<12);
	GPIOA->MODER |= (1U<<13);
	//PA7
	GPIOA->MODER &=~ (1U<<14);
	GPIOA->MODER |= (1U<<15);

	//PA9 - OUTPUT MODE because it is SS
	GPIOA->MODER |= (1U<<18);
	GPIOA->MODER &=~ (1U<<19);

	// Set PA5, PA6, PA7 mode to SPI1 (AF05) from alt func mapping
	//PA5
	GPIOA->AFR[0] &=~ (1U<<23); //0
	GPIOA->AFR[0] |=  (1U<<22); //1
	GPIOA->AFR[0] &=~ (1U<<21); //0
	GPIOA->AFR[0] |=  (1U<<20); //1
	//PA6
	GPIOA->AFR[0] &=~ (1U<<27);
	GPIOA->AFR[0] |=  (1U<<26);
	GPIOA->AFR[0] &=~ (1U<<25);
	GPIOA->AFR[0] |=  (1U<<24);
	//PA7
	GPIOA->AFR[0] &=~ (1U<<31);
	GPIOA->AFR[0] |=  (1U<<30);
	GPIOA->AFR[0] &=~ (1U<<29);
	GPIOA->AFR[0] |=  (1U<<28);

}

void spi1_config(void)
{
	// Enable clock access to the SP1 module
	RCC->APB1ENR |= SPI1EN;

	// Set clock to fPCLK/4
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &=~ (1U<<4);
	SPI1->CR1 &=~ (1U<<5);

	// Set CPOL to 1 and CPHA to 1
	SPI1->CR1 |= CPHA;
	SPI1->CR1 |= CPOL;

	// Enable full-duplex
	SPI1->CR1 &=~ RXONLY;

	// Set MSB First
	SPI1->CR1 &=~ LSB_FIRST;

	// Set Master
	SPI1->CR1 |= MSTR;

	// Set 8 bit data mode
	SPI1->CR1 &=~ DFF;

	// Select software slave management
	SPI1->CR1 |= SSM;
	SPI1->CR1 |= SSI;

	// enable SPI module
	SPI1->CR1 |= SPE;
}


void spi1_transmit(uint8_t *data, uint32_t size)
{
	uint32_t i =0;
	uint8_t temp;
	while(i<size)
	{
		// Wait until TXE is set which is in the status register
		// if false, get stuck here
		while (!(SPI1->SR & SR_TXE)){}

		// if there is space, write data to the data register
		SPI1->DR = data[i];
		i++;
	}

	// wait for TXE to be set, to indicate everything has been transmitted
	while (!(SPI1->SR & SR_TXE)){}
	// wait for the busy flag to reset to indicate that its not busy
	// while busy flag is one get stuck here, wait while it is high
	// once low get out of the loop
	while ((SPI1->SR & SR_BUSY)){}


	// Clear OVR flag, overrun flag, page 599 in ref
	temp = SPI1->DR;
	temp = SPI1->SR;
}


void spi1_receive(uint8_t *data, uint32_t size)
{
	while(size)
	{
		// Send ummy data
		SPI1->DR = 0;

		// In ref SPI_SR bit 0 = RXNE
		while (!(SPI1->SR & SR_RXNE)) {}
		// ONCE RXNE IS SET THERE IS NEW DATA TO BE READ
		//Read data from data register
		*data++ = SPI1->DR;
		size--;

	}
}


void cs_enable(void)
{
	// Disable the pin to enable cs line, setting to 0
	GPIOA->ODR &=~ (1U<<9);
}



void cs_disable(void)
{
	// Enable the pin to disable cs line, setting to 1
	GPIOA->ODR |= (1U<<9);
}
