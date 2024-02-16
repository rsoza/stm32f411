/*
 * exti.h
 *
 *  Created on: Feb 14, 2024
 *      Author: rsoza
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f4xx.h"
void pc13_exti_init(void);

// ref EXTI_PR
// pending register allows us to know the request was made
#define LINE13	(1U<<13)


#endif /* EXTI_H_ */
