/*
 * temp_sensor.h
 *
 *  Created on: Feb 17, 2024
 *      Author: rsoza
 */

#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include <stdint.h>

void temp_sensor_init(void);
void start_converstion(void);
uint32_t temp_read(void);

#endif /* TEMP_SENSOR_H_ */
