/*
 * Timer1.c
 *
 * Created: 9/7/2018 9:05:17 PM
 *  Author: Carnival
 */ 

#include "Timer1.h"
void (*ISRptr_overflow)(void);
void (*ISRptr_CTC)(void);


void Timer1_init(void){
	

	myTCCR1BA|= (waveform_mode)|(Compare_match_output_modeB)|(Compare_match_output_modeA)|(Clock_select_mode);
	#if (comparematchA_interrupt_Enable_Timer1)
	set_bit(mySREG,7);
	set_bit(myTIMSK,4);
	#endif
		#if (comparematchB_interrupt_Enable_Timer1)
		set_bit(mySREG,7);
		set_bit(myTIMSK,3);
		#endif
	/*#if (Compare_match_output_modeA!=NormalPort_OC1A_disconnected)
	set_bit(myDDRB,3);
	#endif
*/
	#if (Overflow_interrupt_Enable_Timer1)
	set_bit(mySREG,7);
	set_bit(myTIMSK,2);
	#endif
	#if (waveform_mode==Timer1_CTC)
	
	Timer1_set_CTC_value(OCR1A_intial_value);
	#endif
}

void Timer1_set_CTC_value(u16 value){
	
	myOCR1ALH=value;
	
}

void SET_ISR_FUN_overflow_Timer1(void (*fun)(void)){
	ISRptr_overflow=fun;
}

ISR(TIMER_COUNTER1_OVERFLOW){
	ISRptr_overflow();
}

void SET_ISR_FUN_CTCA_Timer1(void (*fun)(void)){
	
	ISRptr_CTC=fun;
}

ISR(TIMER_COUNTER1_COMPARE_MATCH_A){
	
	ISRptr_CTC();
	
}


void input_capture_init(void){
	
		myTCCR1B|=Clock_select_mode |(Input_capture_noise_canceler<<ICNC1)|(Input_capture_noise_edge_select<<ICES1);
		#if (input_capture_interrupt)
		set_bit(mySREG,7);
		set_bit(myTIMSK,5);
		#endif
		myTIFR|=(1<<input_capture_flag_bit_Timer1);
	
	
}

u8 input_capture_get(edge selected_edge){
	u8 result=0;
	switch (selected_edge){
	case RISING:
			set_bit(myTCCR1B,ICES1);
			while ((myTIFR&(1<<input_capture_flag_bit_Timer1)) == 0);
			result=myICR1LH;
			myTIFR|=(1<<input_capture_flag_bit_Timer1);
		break;
	case FALLING:
			reset_bit(myTCCR1B,ICES1);
			while ((myTIFR&(1<<input_capture_flag_bit_Timer1)) == 0);
			result=myICR1LH;
			myTIFR|=(1<<input_capture_flag_bit_Timer1);
		break;
	}
	return result;
	
}

void get_dutycycle_freq(f32 * arr){
	u8 first=0,second=0,third=0;
	u8 higher=0,period=0;
	first=input_capture_get(RISING);
	second=input_capture_get(FALLING);
	third=input_capture_get(RISING);
	higher=second-first;
	period=third-first;
	u32 freq=F_CPU/period;
	arr[0]=freq;
	f32 duty_cyle=(f32)higher /(f32)period*100;
	arr[1]=duty_cyle;
}
