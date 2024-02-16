/*
 * adc.h
 *
 *  Created on: Feb 12, 2024
 *      Author: rsoza
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pa1_adc_init(void);
void start_converstion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
