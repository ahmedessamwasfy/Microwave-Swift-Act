/*
 * interrupt.h
 *
 * Created: 7/14/2018 11:42:44 PM
 *  Author: Carnival
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include "interrupt_config.h"

extern void interrupt_init(void);
extern void interrupt_INT0(interrupt_generate signal);
extern void interrupt_INT1(interrupt_generate signal);
 void interrupt0_isr_Set( void (isr_ptr)(void) );
 void interrupt1_isr_Set( void (isr_ptr)(void));
extern void interrupt_disable(void);
 
 
 //note mohema f45 setting the call back function of isr must be set before setting any thing about interrupt so the first function to use is interrupt isr set

#endif /* INTERRUPT_H_ */