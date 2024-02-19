#include "stm32f4xx.h"


#define GPIOBEN			(1U<<1)
#define I2C1EN			(1U<<21)
#define CR1_PE			(1U<<0)
#define SR2_BUSY		(1U<<1)
#define CR1_START		(1U<<8)
#define SR1_SB			(1U<<0)
#define SR1_ADDR		(1U<<1)
#define SR1_TXE			(1U<<7)
#define SR1_RXNE			(1U<<6)
#define CR1_ACK			(1U<<10)
#define CR1_STOP		(1U<<9)
#define SR1_BTF			(1U<<2)

#define I2C_100KHZ				80 //decimal
#define SD_MODE_MAX_RISE_TIME	17


void I2C1_init(void){
	// Enable clock access to GPIOB
	RCC->AHB1ENR |= GPIOBEN;

	// Set PB8 and PB9 mode to alternate function
	// PB8
	GPIOB->MODER &=~ (1U<<16);
	GPIOB->MODER |= (1U<<17);
	//pb9
	GPIOB->MODER &=~ (1U<<18);
	GPIOB->MODER |= (1U<<19);

	// Set PB8 and PB9 output type to open drain
	GPIOB->OTYPER |= (1U<<8);
	GPIOB->OTYPER |= (1U<<9);

	// Enable pull up for PB8 and PB9
	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR &=~ (1U<<17);

	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR &=~ (1U<<19);

	// Alternate function mapping, AFR in ref man using AF4 0100
	// Set PB8 and PB9 alternate function type to I2C (AF4)
	GPIOB->AFR[1] &=~ (1U<<0);
	GPIOB->AFR[1] &=~ (1U<<1);
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &=~ (1U<<3);

	GPIOB->AFR[1] &=~ (1U<<4);
	GPIOB->AFR[1] &=~ (1U<<5);
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &=~ (1U<<7);

	// Enable clock access to I2C1
	RCC->APB1ENR |= I2C1EN;

//	enter reset mode
	I2C1->CR1 |= (1U<<15);
	I2C1->CR1 &=~ (1U<<15);

	// configure the peripheral clock
	I2C1->CR2 |= (1U<<4); //16MHz

	// set 12c to standard mode
	I2C1->CCR = I2C_100KHZ;

	// Set rise time
	I2C1->TRISE = SD_MODE_MAX_RISE_TIME;

	// Enable I2C1 module
	I2C1->CR1 |= CR1_PE;

}


void I2C1_byteRead(char saddr, char maddr, char* data) {
	volatile int tmp;

	// Wait until not busy
	while(I2C1->SR2 & (SR2_BUSY)) {}

	// Generate start condition
	I2C1->CR1 |= CR1_START;

	// WAIT until start flag is set
	while (!(I2C1->SR1 & (SR1_SB))) {}

	// transmit slave address and write
	I2C1->DR = saddr<<1;

	// Wait until addr flag is set
	while (! (I2C1->SR1 & (SR1_ADDR))) {}

	// Clear address flag
	tmp = I2C1->SR2;

	// Send memory address
	I2C1->DR = maddr;

	// wait until DR is empty
	while (!(I2C1->SR1 & SR1_TXE)) {}

	//once empty generate another start condition
	I2C1->CR1 |= CR1_START;

	// wait until start flag is set
	while (!(I2C1->SR1 & SR1_SB)) {}

	// Transmit slave address and read
	I2C1->DR = saddr << 1 | 1;

	// Wait until addr flag is set
	while (! (I2C1->SR1 & (SR1_ADDR))) {}

	// Disable the acknowledge
	I2C1->CR1 &=~ CR1_ACK;

	// Clear address flag
	tmp = I2C1->SR2;

	// Generate stop after data received
	I2C1->CR1 |= CR1_STOP;

	// wait until RXNE flag is set
	while(!(I2C1->SR1 & SR1_RXNE)){}

	// READ DATA FROM dr
	*data++ = I2C1->DR;

}


void I2C1_burstRead(char saddr, char maddr, int n, char* data)
{
	volatile int tmp;

	// Wait until not busy
	while(I2C1->SR2 & (SR2_BUSY)) {}

	// Generate start condition
	I2C1->CR1 |= CR1_START;

	// WAIT until start flag is set
	while (!(I2C1->SR1 & SR1_SB)) {}

	// transmit slave address and write
	I2C1->DR = saddr<<1;

	// Wait until addr flag is set
	while (! (I2C1->SR1 & SR1_ADDR)) {}

	// Clear address flag
	tmp = I2C1->SR2;

	// wait until DR is empty
	while (!(I2C1->SR1 & SR1_TXE)) {}

	// Send memory address
	I2C1->DR = maddr;

	// wait until DR is empty
	while (!(I2C1->SR1 & SR1_TXE)) {}

	// generate restart
	I2C1->CR1 |= CR1_START;
	// wait until start flag is set
	while (!(I2C1->SR1 & SR1_SB)) {}

	// Transmit slave address + read
	I2C1->DR = saddr << 1 | 1;

	// Wait until addr flag is set
	while (! (I2C1->SR1 & (SR1_ADDR))) {}


	// Clear address flag
	tmp = I2C1->SR2;

	// Enable acknowledge
	I2C1->CR1 |= CR1_ACK;


	while (n >0U)
	{
		// check if there is one byte left
		if (n == 1U)
		{
			// disable the acknowledg
			I2C1->CR1 &=~ CR1_ACK;

			// generate stop
			I2C1->CR1 |= CR1_STOP;

			// wait until RXNE flag is set
			while(!(I2C1->SR1 & SR1_RXNE)){}

			// READ DATA FROM dr
			*data++ = I2C1->DR;
			break;
		}
		else {
			// wait for the data to arrive
			while(!(I2C1->SR1 & SR1_RXNE)){}

			// once arrived read a data from DR
			(*data++) = I2C1->DR;
			n--;
		}
	}

}

void I2C1_burstWrite(char saddr, char maddr, int n, char* data)
{
	volatile int tmp;
	// Wait until not busy
	while(I2C1->SR2 & (SR2_BUSY)) {}

	// Generate start condition
	I2C1->CR1 |= CR1_START;

	// WAIT until start flag is set
	while (!(I2C1->SR1 & (SR1_SB))) {}

	// Transmit slave address
	I2C1->DR = saddr<<1;

	// Wait until addr flag is set
	while (! (I2C1->SR1 & (SR1_ADDR))) {}

	// Clear address flag
	tmp = I2C1->SR2;

	// wait until DR is empty
	while (!(I2C1->SR1 & (SR1_TXE))) {}

	// Send memory address
	I2C1->DR = maddr;

	// write
	for (int i = 0; i<n; i++)
	{
		// wait until data register empty
		while (!(I2C1->SR1 & (SR1_TXE))) {}
		// increment, transmit memory address
		I2C1->DR = *data++;
	}
	//btf flag in i2c_sr1
	while (!(I2C1->SR1 & (SR1_BTF))) {}
	// generate stop condition
	I2C1->CR1 |= CR1_STOP;
}



