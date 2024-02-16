/*
 * tim.h
 *
 *  Created on: Feb 13, 2024
 *      Author: rsoza
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);
void tim2_1hz_interrupt_init(void);

//IN REF MANUAL SEARCH TIMX_SR
// UIF BIT 0 ALLOWS FOR A FLAG
#define SR_UIF (1U<<0)


#endif /* TIM_H_ */
