/*
 * timer.h
 *
 * Created: 7/17/2018 12:47:53 PM
 *  Author: Carnival
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "timer_config0.h"

#define get_timer0_counter			myTCNT0
#define set_timer0_value(val)		myTCNT0=value
//#define Set_compare_value(val)		

void timer0_init(void);
void Timer0_Start(void);
void Timer0_Stop(void);
void timer0_set_CTC_value(u8 value);
void SET_ISR_FUN_CTC_timer0( void (isr_ptr)(void) );
void SET_ISR_FUN_overflow_timer0( void (isr_ptr)(void) );


#endif /* TIMER_H_ */



/*				timer calculations 

Frequency
********************************Timer**********************************





********************************PWM**********************************
given
Time = 1/Frequency
duty cycle 45%

time on	  =	45%	* time
time off  = 55% * time


*/
