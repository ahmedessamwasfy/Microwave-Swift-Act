/*
 * Timer1.h
 *
 * Created: 9/7/2018 9:05:33 PM
 *  Author: Carnival
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_



#include "Timer_config1.h"

#define get_Timer1_counter			myTCNT1LH
#define set_Timer1_value(val)		myTCNT1LH=value
//#define Set_compare_value(val)

void Timer1_init(void);
void Timer1_set_CTC_value(u16 value);
void SET_ISR_FUN_CTCA_Timer1(void (*fun)(void));
void SET_ISR_FUN_overflow_Timer1(void (*fun)(void));
void input_capture_init(void);
u8 input_capture_get(edge selected_edge);
void get_dutycycle_freq(f32 * arr);










#endif /* TIMER1_H_ */