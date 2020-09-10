/*
 * Timer2.h
 *
 * Created: 9/7/2018 4:47:23 PM
 *  Author: Carnival
 */ 


#ifndef TIMER2_H_
#define TIMER2_H_


#include "Timer_config2.h"

#define get_Timer2_counter			myTCNT2
#define set_Timer2_value(val)		myTCNT2=value
//#define Set_compare_value(val)

void Timer2_init(void);
void Timer2_Start(void);
void Timer2_Stop(void);
void Timer2_set_CTC_value(u8 value);
void SET_ISR_FUN_overflow_timer2(void (*fun)(void));
void SET_ISR_FUN_CTC_timer2(void (*fun)(void));


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
#endif /* TIMER2_H_*/