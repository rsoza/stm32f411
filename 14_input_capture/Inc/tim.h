/*
 * tim.h
 *
 *  Created on: Feb 13, 2024
 *      Author: rsoza
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);


//IN REF MANUAL SEARCH TIMX_SR
// UIF BIT 0 ALLOWS FOR A FLAG
#define SR_UIF (1U<<0)


// REF TIMX_SR
// CC1IF Capture/compare 1 interrupt flag
#define SR_CC1IF	(1U<<1)


#endif /* TIM_H_ */
