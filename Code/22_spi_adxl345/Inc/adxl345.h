/*
 * adxl345.h
 *
 *  Created on: Feb 19, 2024
 *      Author: rsoza
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "spi.h"
#include <stdint.h>

//adxl345 datasheet memory map
#define DEVID_R				(0x00)
// I2C in adxl345 datasheet shows this R/W bit page 17
#define DEVICE_ADDR			(0x53) //slave address
// data format control
#define DATA_FORMAT_R		(0x31)
// Power control
#define POWER_CTL_R			(0x2D)
#define DATA_START_ADDR		(0x32)
#define DATA_FORMAT_R		(0x31)

// setting data format r to four g bits 0 and 1
#define FOUR_G				(0x01)
#define RESET				(0x00)
#define SET_MEASURE_B		(0X08) // 8 hertz wake up; 0b 1000


void adxl_init(void);
void adxl_read(uint8_t address, uint8_t *rxdata);

#endif /* ADXL345_H_ */
