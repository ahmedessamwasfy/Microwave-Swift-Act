/*
 * interrupt.c
 *
 * Created: 7/14/2018 11:42:27 PM
 *  Author: Carnival
 */ 
#include "interrupt.h"
// 
 void(*  intrrupt0_isr)(void);
 void( *  intrrupt1_isr)(void);
 
extern  void interrupt_init(void){
	set_bit(mySREG,7);
}
extern  void interrupt_disable(void){
	reset_bit(mySREG,7);
}

 extern void interrupt_INT0(interrupt_generate signal){
	reset_bit(INT0_port,2);
	set_bit(myGICR,6);
	switch(signal){
		case low_level:
			reset_bit(myMCUCR,0);
			reset_bit(myMCUCR,1);
			break;
		case logic_toggel:
			reset_bit(myMCUCR,1);
			set_bit(myMCUCR,0);
			break;
		case falling_edge:
			reset_bit(myMCUCR,0);
			set_bit(myMCUCR,1);
			break;
		case rising_edge:
			set_bit(myMCUCR,0);
			set_bit(myMCUCR,1);
			break;
		default:
		break;
	}
	
}

extern  void interrupt_INT1(interrupt_generate signal){
	reset_bit(INT0_port,3);
	set_bit(myGICR,7);
	switch(signal){
		case low_level:
		reset_bit(myMCUCR,2);
		reset_bit(myMCUCR,3);
		break;
		case logic_toggel:
		reset_bit(myMCUCR,3);
		set_bit(myMCUCR,2);
		break;
		case falling_edge:
		reset_bit(myMCUCR,2);
		set_bit(myMCUCR,3);
		break;
		case rising_edge:
		set_bit(myMCUCR,2);
		set_bit(myMCUCR,3);
		break;
		default:
		break;
	}
	
}

void interrupt0_isr_Set( void (isr_ptr)(void) ){
	intrrupt0_isr=isr_ptr;
}

void interrupt1_isr_Set( void (isr_ptr)(void) ){
	intrrupt1_isr=isr_ptr;
}
ISR(EXTERNALinterrupt1){
	
	intrrupt1_isr();

}

ISR(EXTERNALinterrupt0){

	intrrupt0_isr();
}








	
	