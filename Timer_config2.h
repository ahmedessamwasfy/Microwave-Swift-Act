/*
 * Timer2_config.h
 *
 * Created: 9/7/2018 4:47:41 PM
 *  Author: Carnival
 */ 


#ifndef TIMER2_CONFIG_H_
#define TIMER2_CONFIG_H_


#include "MACROS.h"
#include "datatype.h"
#include "VECTOR_TABLE.h"

/********************************SFOIR REG**********************************/

#define mySFIOR *(volatile u8* const)(0x50)
#define prescaler2_reset_bit 1  // to set prescaler in timer 2



/********************************Asynchronus REG**********************************/

#define myASSR   *((volatile unsigned char* const)0X42)
#define Asynchronous_mode	FALSE
#define AS2_bit				3
#define TCN2UB_bit			2
#define OCR2UB_bti			1
#define TCR2UB_bit			0


/********************************TCRT 0 timer control register **********************************/
#define myTCCR2  *((volatile unsigned char* const)0X45)

///there id bit 7 i want to know what it does


//the clock mode
#define TIMER2_waveform_mode     Timer2_PWM    //WGM00 and WGM01
//the moods mask on bits 6 and 3
#define Timer2_Normal	 0b00000000 //normal on overflowing
#define Timer2_PWM		 0b01000000
#define Timer2_CTC		 0b00001000//compare match
#define Timer2_FastPWM	 0b01001000


//the external pin OC2 mode
#define TIMER2_Compare_match_output_mode       TIMER2_Clear_OC2_on_comparematch //COM00 and COM01
//the moods to chose and their masks on bits 5:4     //modes in CTC NON PWM MODE
#define TIMER2_NormalPort_OC2_disconnected		 0b00000000 // the OC2 pin will be Dio pin normally
#define TIMER2_Toggle_OC2_on_comparematch		 0b00010000 // the OC2 pin will toggel on compare match
#define TIMER2_Clear_OC2_on_comparematch		 0b00100000 // the OC2 pin will Clear on compare match
#define TIMER2_Set_OC2_on_comparematch			 0b00110000 // the OC2 pin will Set on compare match
/// note :-check the modes of COM in PWM and fast PWM



//Clock select and prescaler
#define TIMER2_Clock_select_mode TIMER2_Prescaler256 //CS02 CS01 CS00
//the moods to chose and their masks on bits 2,1,0
#define TIMER2_NO_clock_source											 0b00000000 // Timer is stopped
#define TIMER2_Prescaler1												 0b00000001 // clk/1 no prescaler
#define TIMER2_Prescaler8												 0b00000010 // clk/8
#define TIMER2_Prescaler32												 0b00000011 // clk/64
#define TIMER2_Prescaler64												 0b00000100 // clk/256
#define TIMER2_Prescaler128												 0b00000101 // clk/1024
#define TIMER2_Prescaler256												 0b00000110 
#define TIMER2_Prescaler1024											 0b00000111	


/********************************TCNT 0 timer  register (read the counter or set the timer ) **********************************/

#define myTCNT2  *((volatile unsigned char* const)0X44)

/********************************OCR0 output compare march register  register (write the number i want) **********************************/
#define myOCR2   *((volatile unsigned char* const)0X43)

#define OCR2_intial_value   0x55

/********************************TIMSK Interrupt mask  register **********************************/
#define myTIMSK  *((volatile unsigned char* const)0X59)

#define comparematch_interrupt_Enable_timer2 TRUE	// bit 1 OCIE2
#define Overflow_interrupt_Enable_timer2 FALSE		// bit 0 TOIE2




/********************************TIFR Interrupt Flag  register (READ and reset by write) **********************************/
#define myTIFR   *((volatile unsigned char* const)0X58)

#define comparematch_flag_bit_timer2 1	// bit 1 OCF2
#define Overflow_flag_bit_timer2 0		// bit 0 TOV2




#endif /* TIMER2_CONFIG_H_ */