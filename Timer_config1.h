/*
 * Timer_config1.h
 *
 * Created: 9/7/2018 9:05:48 PM
 *  Author: Carnival
 */ 


#ifndef TIMER_CONFIG1_H_
#define TIMER_CONFIG1_H_


#include "MACROS.h"
#include "datatype.h"
#include "VECTOR_TABLE.h"


typedef enum{
	RISING=0,
	FALLING=1
}edge;



#ifndef F_CPU

# warning "F_CPU not defined for PWM function and we put it by1000000UL "
# define F_CPU 1000000UL
#endif



/********************************SFOIR REG**********************************/

#define mySFIOR *(volatile u8* const)(0x50)
#define prescaler01_reset_bit 0  // to set prescaler in timer 0 and timer 1


/********************************TCRT 0 timer control register **********************************/
#define myTCCR1A *((volatile unsigned char* const)0X4F)
#define myTCCR1B *((volatile unsigned char* const)0X4E)

#define myTCCR1BA *((volatile u16* const)0X4E)

///there id bit 7 i want to know what it does


//input capture pins and edge select

#define ICNC1	7
#define Input_capture_noise_canceler	FALSE

#define ICES1	6
#define Input_capture_noise_edge_select	RISING

//


//the clock mode
#define waveform_mode     Timer1_Normal    //WGM10 and WGM11 and WGM12 and WGM13  //the moods mask on bits 8 and 9 and 3 and 4 respectively 
//the moods								 mask XXXXXX10 XXX32XXX				MODE					TOP			update OCR1x		TOV1 flag set on 
#define Timer1_Normal						0b0000000000000000		//normal on overflowing			0XFFFF		  Immediate				 MAX
#define Timer1_PHASE_CORRECT_8				0b0000000100000000		//phase correct 8-bits			0x00FF			TOP					Bottom
#define Timer1_PHASE_CORRECT_9				0b0000001000000000		//phase correct 9-bits			0x01FF			TOP					BOTTOM
#define Timer1_PHASE_CORRECT_10				0b0000001100000000		//phase correct 10-bits			0x03FF			TOP					BOTTOM
#define Timer1_CTC_OCR1A					0b0000000000001000		//COMPARE MATCH					OCR1A		  Immediate				  MAX
#define Timer1_FAST_PWM_8					0b0000000100001000		//FAST PWM 8-BIT				0x00FF			Bottom				  TOP
#define Timer1_FAST_PWM_9					0b0000001000001000		//FAST PWM 9-BIT				0x01FF			BOTTOM				  TOP
#define Timer1_FAST_PWM_10					0b0000001100001000		//FAST PWM 10-BIT				0x03FF			BOTTOM				  TOP
#define Timer1_PHAASE_FREQ_CORRECT_ICR1		0b0000000000010000		//PHASE AND FREQ. CORRECT		ICR1			BOTTOM				BOTTOM
#define Timer1_PHAASE_FREQ_CORRECT_OCR1A	0b0000000100010000		//PHASE AND FREQ. CORRECT		OCR1A			BOTTOM				BOTTOM
#define Timer1_PHASE_CORRECT_ICR1			0b0000001000010000		//PHASE CORRECT					ICR1			 TOP				BOTTOM
#define Timer1_PHASE_CORRECT_OCR1A			0b0000001100010000		//PHASE CORRECT					OCR1A			 TOP				BOTTOM
#define Timer1_CTC_ICR1						0b0000000000011000		//COMPARE MATCH					ICR1		  Immediate				  MAX
#define Timer1_FAST_PWM_ICR1				0b0000001000011000		//FAST PWM						ICR1			BOTTOM				  TOP
#define Timer1_FAST_PWM_OCR1A				0b0000001100011000		//FAST PWM						OCR1A			BOTTOM				  TOP
							   


//the external pin OC1A mode
#define Compare_match_output_modeA       NormalPort_OC1A_disconnected //COM1A0 and COM1A1
//the moods to chose and their masks on bits 5:4     //modes in CTC NON PWM MODE
#define NormalPort_OC1A_disconnected		 0b0000000000000000 // the OC1A pin will be Dio pin normally		 in Ctc and normal mode			 ///the OC1A pin will be Dio pin normally								in fast PWM			//the OC1A pin will be Dio pin normally	 
#define Toggle_OC1A_on_comparematch			 0b0100000000000000 // the OC1A pin will toggel on compare match	 in Ctc and normal mode			 ///the OC1A pin will toggel on compare match and OC!B will disconnect	in fast PWM			//the OC1A pin will toggel on compare match
#define Clear_OC1A_on_comparematch			 0b1000000000000000 // the OC1A pin will Clear on compare match	 in Ctc and normal mode			 ///the OC1A pin will Clear on compare match and set in bottom			in fast PWM			//the OC1A pin will Clear on compare match when up counting and set on ctc when down-counting
#define Set_OC1A_on_comparematch			 0b1100000000000000 // the OC1A pin will Set on compare match		 in Ctc and normal mode			 ///the OC1A pin will Set on compare match	 and clear in bottom		in fast PWM			//the OC1A pin will Set on compare match   when up counting and clear on ctc when down-counting 

//the external pin OC1B mode
#define Compare_match_output_modeB       NormalPort_OC1B_disconnected //COM1B0 and COM1B1
//the moods to chose and their masks on bits 5:4     //modes in CTC NON PWM MODE							
#define NormalPort_OC1B_disconnected		 0b0000000000000000 // the OC1 pin will be Dio pin normally		 in Ctc and normal mode			///the OC1A pin will be Dio pin normally								in fast PWM			//the OC1A pin will be Dio pin normally	 
#define Toggle_OC1B_on_comparematch			 0b0001000000000000 // the OC1 pin will toggel on compare match	 in Ctc and normal mode			///the OC1A pin will toggel on compare match and OC!B will disconnect	in fast PWM			//the OC1A pin will toggel on compare match
#define Clear_OC1B_on_comparematch			 0b0010000000000000 // the OC1 pin will Clear on compare match		 in Ctc and normal mode 		///the OC1A pin will Clear on compare match and set in bottom			in fast PWM			//the OC1A pin will Clear on compare match when up counting and set on ctc when down-counting
#define Set_OC1B_on_comparematch			 0b0011000000000000 // the OC1 pin will Set on compare match		 in Ctc and normal mode			///the OC1A pin will Set on compare match	 and clear in bottom		in fast PWM			//the OC1A pin will Set on compare match   when up counting and clear on ctc when down-counting 
 




/// note :-check the modes of COM in PWM and fast PWM



//Clock select and prescaler
#define Clock_select_mode Prescaler1024 //CS12 CS11 CS10
//the moods to chose and their masks on bits 2,1,0
#define NO_clock_source											 0b0000000000000000 // Timer is stopped
#define Prescaler1												 0b0000000000000001 // clk/1 no prescaler
#define Prescaler8												 0b0000000000000010 // clk/8
#define Prescaler64												 0b0000000000000011 // clk/64
#define Prescaler256											 0b0000000000000100 // clk/256
#define Prescaler1024											 0b0000000000000101 // clk/1024
#define External_clc_on_T0_pin_clock_on_falling_edge			 0b0000000000000110 // external clk source with clock on falling edge
#define External_clc_on_T0_pin_clock_on_rising_edge				 0b0000000000000111	// external clk source with clock on rising edge


/********************************TCNT 0 timer  register (read the counter or set the timer ) **********************************/

#define myTCNT1H *((volatile unsigned char* const)0X4D)
#define myTCNT1L *((volatile unsigned char* const)0X4C)

#define myTCNT1LH *((volatile u16* const)0X4C)


/********************************OCRA output compare march register A register (write the number i want) **********************************/
#define myOCR1AH *((volatile unsigned char* const)0X4B)
#define myOCR1AL *((volatile unsigned char* const)0X4A)
#define myOCR1ALH *((volatile u16* const)0X4A)

#define OCR1A_intial_value   0x31


/********************************OCB output compare march register B register (write the number i want) **********************************/

#define myOCR1BH *((volatile unsigned char* const)0X49)
#define myOCR1BL *((volatile unsigned char* const)0X48)
#define myOCR1BLH *((volatile u16* const)0X48)


#define OCR1B_intial_value   0x31

/********************************TIMSK Interrupt mask  register **********************************/
#define myTIMSK  *((volatile unsigned char* const)0X59)

#define input_capture_interrupt				  FALSE			// bit 5 TICIE1
#define comparematchA_interrupt_Enable_Timer1 FALSE			// bit 4 OCIE1A
#define comparematchB_interrupt_Enable_Timer1 FALSE			// bit 3 OCIE1B
#define Overflow_interrupt_Enable_Timer1	   TRUE			// bit 2 TOIE1 




/********************************TIFR Interrupt Flag  register (READ and reset by write) **********************************/
#define myTIFR   *((volatile unsigned char* const)0X58)


#define input_capture_flag_bit_Timer1 5			// bit 5 ICF1
#define comparematchA_flag_bit_Timer1 4			// bit 4 OCF1A
#define comparematchB_flag_bit_Timer1 3			// bit 3 OCF1B
#define Overflow_flag_bit_Timer1	  2			// bit 2 TOV1 



/********************************Input capture unit register **********************************/


#define myICR1H  *((volatile unsigned char* const)0X47)
#define myICR1L  *((volatile unsigned char* const)0X46)
#define myICR1LH  *((volatile u16* const)0X46)


#endif /* TIMER_CONFIG1_H_ */