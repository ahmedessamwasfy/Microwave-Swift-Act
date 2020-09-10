/*
 * timer_config.h
 *
 * Created: 7/17/2018 12:48:16 PM
 *  Author: Carnival
 */ 


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#include "MACROS.h"
#include "datatype.h"
#include "VECTOR_TABLE.h"

/********************************SFOIR REG**********************************/

#define mySFIOR *(volatile u8* const)(0x50)
#define prescaler01_reset_bit 0  // to set prescaler in timer 0 and timer 1


/********************************TCRT 0 timer control register **********************************/
#define myTCCR0  *((volatile unsigned char* const)0X53)

///there id bit 7 i want to know what it does


//the clock mode 
#define TIMER0_waveform_mode     timer0_Normal    //WGM00 and WGM01
//the moods mask on bits 6 and 3 
#define timer0_Normal	 0b00000000 //normal on overflowing
#define timer0_PWM		 0b01000000
#define timer0_CTC		 0b00001000//compare match
#define timer0_FastPWM	 0b01001000


//the external pin OC0 mode 
#define TIMER0_Compare_match_output_mode       NormalPort_OC0_disconnected //COM00 and COM01
//the moods to chose and their masks on bits 5:4     //modes in CTC NON PWM MODE
#define NormalPort_OC0_disconnected		 0b00000000 // the OC0 pin will be Dio pin normally
#define Toggle_OC0_on_comparematch		 0b00010000 // the OC0 pin will toggel on compare match
#define Clear_OC0_on_comparematch		 0b00100000 // the OC0 pin will Clear on compare match
#define Set_OC0_on_comparematch			 0b00110000 // the OC0 pin will Set on compare match
/// note :-check the modes of COM in PWM and fast PWM



//Clock select and prescaler 
#define TIMER0_Clock_select_mode TIMER0_Prescaler256 //CS02 CS01 CS00
//the moods to chose and their masks on bits 2,1,0   
#define TIMER0_NO_clock_source											 0b00000000 // Timer is stopped
#define TIMER0_Prescaler1												 0b00000001 // clk/1 no prescaler
#define TIMER0_Prescaler8												 0b00000010 // clk/8
#define TIMER0_Prescaler64												 0b00000011 // clk/64
#define TIMER0_Prescaler256												 0b00000100 // clk/256
#define TIMER0_Prescaler1024											 0b00000101 // clk/1024
#define TIMER0_External_clc_on_T0_pin_clock_on_falling_edge				 0b00000110 // external clk source with clock on falling edge
#define TIMER0_External_clc_on_T0_pin_clock_on_rising_edge				 0b00000111	// external clk source with clock on rising edge


/********************************TCNT 0 timer  register (read the counter or set the timer ) **********************************/

#define myTCNT0  *((volatile unsigned char* const)0X52)  

/********************************OCR0 output compare march register  register (write the number i want) **********************************/
#define myOCR0   *((volatile unsigned char* const)0X5C)  

#define OCR0_intial_value   0x50

/********************************TIMSK Interrupt mask  register **********************************/
#define myTIMSK  *((volatile unsigned char* const)0X59)

#define comparematch_interrupt_Enable_timer0 FALSE	// bit 1 OCIE0
#define Overflow_interrupt_Enable_timer0 TRUE		// bit 0 TOIE0




/********************************TIFR Interrupt Flag  register (READ and reset by write) **********************************/
#define myTIFR   *((volatile unsigned char* const)0X58)   

#define comparematch_flag_bit_timer0 1	// bit 1 OCF0
#define Overflow_flag_bit_timer0 0		// bit 0 TOV0	

#endif /* TIMER_CONFIG_H_ */