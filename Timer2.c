/*
 * Timer2.c
 *
 * Created: 9/7/2018 4:47:08 PM
 *  Author: Carnival
 */ 

#include "Timer2.h"

void (*ISRptr_overflow)(void);
void (*ISRptr_CTC)(void);


void Timer2_init(void){
	
	
	myTCCR2|= (TIMER2_waveform_mode)|(TIMER2_Compare_match_output_mode);
	#if (comparematch_interrupt_Enable_timer2)
	set_bit(mySREG,7);
	set_bit(myTIMSK,1);
	#endif
	#if (Compare_match_output_mode!=NormalPort_OC0_disconnected)
	set_bit(myDDRB,3);
	#endif

	#if (Overflow_interrupt_Enable_timer2)
	set_bit(mySREG,7);
	set_bit(myTIMSK,0);
	#endif
	#if (waveform_mode==Timer2_CTC)
	
	Timer2_set_CTC_value(OCR2_intial_value);
	#endif
	myASSR|=(Asynchronous_mode<<AS2_bit);

}


void Timer2_Start(void){
		myTCNT2 =0x00;
		myTCCR2|=(TIMER2_Clock_select_mode);
	
}
void Timer2_Stop(void){
	myTCNT2 =0x00;
	myTCCR2&=~(TIMER2_Clock_select_mode);
	
}

void Timer2_set_CTC_value(u8 value){
	
	myOCR2=value;
	
}
void SET_ISR_FUN_overflow_timer2(void (*fun)(void)){	
	ISRptr_overflow=fun;
}

ISR(TIMER_COUNTER2_OVERFLOW){
	ISRptr_overflow();
}

void SET_ISR_FUN_CTC_timer2(void (*fun)(void)){
	
	ISRptr_CTC=fun;
}

ISR(TIMER_COUNTER2_COMPARE_MATCH){
	
	ISRptr_CTC();
	
}



