/*
 * timer.c
 *
 * Created: 7/17/2018 12:47:39 PM
 *  Author: Carnival
 */ 

#include "timer0.h"

void (*ISRptr_overflow)(void);
void (*ISRptr_CTC)(void);

void timer0_init(void){
	

	myTCCR0|= (TIMER0_waveform_mode)|(TIMER0_Compare_match_output_mode);
	#if (comparematch_interrupt_Enable_timer0)
		set_bit(mySREG,7);
		set_bit(myTIMSK,1);
	#endif
		#if (Compare_match_output_mode!=NormalPort_OC0_disconnected)
		set_bit(myDDRB,3);
		#endif

	#if (Overflow_interrupt_Enable_timer0)
		set_bit(mySREG,7);
		set_bit(myTIMSK,0);
	#endif
	#if (waveform_mode==timer0_CTC)
			
			timer0_set_CTC_value(OCR0_intial_value);
#endif
}

void Timer0_Start(void){
	myTCNT0 =0x00;
	myTCCR0|=(TIMER0_Clock_select_mode);
	
}

void Timer0_Stop(void){
	myTCNT0 =0x00;
	myTCCR0&=~(TIMER0_Clock_select_mode);
	
}

void timer0_set_CTC_value(u8 value){
	
	myOCR0=value;
	myTCNT0=0x00;
}

void SET_ISR_FUN_overflow_timer0( void (isr_ptr)(void) ){
	ISRptr_overflow=isr_ptr;
}

ISR(TIMER_COUNTER0_OVERFLOW){
	ISRptr_overflow();
}

void SET_ISR_FUN_CTC_timer0( void (isr_ptr)(void) ){
	
	ISRptr_CTC=isr_ptr;
}

ISR(TIMER_COUNTER0_COMPARE_MATCH){
	
	ISRptr_CTC();
	
}
