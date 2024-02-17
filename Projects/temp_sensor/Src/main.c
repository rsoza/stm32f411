//in reference manual user push button is in PC13 pin 2
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "temp_sensor.h"

uint32_t sensor_value;

int main(void)
{


	uart2_tx_init();
	temp_sensor_init();

	while(1)
	{
		start_converstion();
		sensor_value = temp_read();
		printf("Sensor Value: %d\n\r", (int)sensor_value);
	}
}


