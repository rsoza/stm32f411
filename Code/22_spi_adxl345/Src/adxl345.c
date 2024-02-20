#include "adxl345.h"

#define MULTI_BYTE_EN		0x40
#define READ_OPERATION		0x80



void adxl_read(uint8_t address, uint8_t *rxdata)
{
	// Set read operation
	address |= READ_OPERATION;

	// Enable multi byte
	address |= MULTI_BYTE_EN;

	// Pull cs line low, to enable the slave
	cs_enable();

	// Send the address to memory of the location wanting to read from
	spi1_transmit(&address, 1);

	// 6 items that we want to read, 6 bytes
	// Receive a piece of data to store
	// Read 6 bytes
	spi1_receive(rxdata, 6);

	// Pull cs line high to disable slave
	cs_disable();
}

void adxl_write(uint8_t address, char value)
{
	uint8_t data[2];

	//Enable multi byte
	// Place address to memory buffer
	data[0] = address|MULTI_BYTE_EN;

	// Place the data into buffer
	data[1] = value;

	// Pull cs line low to enable the slave
	cs_enable();

	// Transmit the data and address
	spi1_transmit(data,2);

	// Pull cs line high to disable slave
	cs_disable();

}


void adxl_init(void)
{
	// Enable SPI GPIO
	spi_gpio_init();

	// Enable SPI config, config SPI
	spi1_config();

	// Set data format range to +-4g
	adxl_write(DATA_FORMAT_R, FOUR_G);

	// Reset all bits
	adxl_write(POWER_CTL_R, RESET);

	// Set the power control measure bit
	adxl_write(POWER_CTL_R, SET_MEASURE_B);
}










