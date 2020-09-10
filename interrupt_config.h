/*
 * interrupt_config.h
 *
 * Created: 7/14/2018 11:44:33 PM
 *  Author: Carnival
 */ 


#ifndef INTERRUPT_CONFIG_H_
#define INTERRUPT_CONFIG_H_
#include "datatype.h"
//#include <avr/interrupt.h>
#include "MACROS.h"
#include "VECTOR_TABLE.h"
/********************************EXT INT REGIStERS**********************************/

#define myMCUCR	*(volatile u8*)(0x55)  // to control  the external interrupt 1 and 0   INTI0 (0,1) INTI1 (2,3)
#define myMCUCSR  *(volatile u8*)(0x54)	// to define whether it will the external interrupt 2 be rising edge (1) or falling  edge (0)   ///the desired bit is 6	 
#define myGICR	*(volatile u8*)(0x5B)	// general interrupt control to enable or disable the external interrupt 0, 1 and 2
#define myGIFR	*(volatile u8*)(0x5A)	//interrupt flag register  we care about bits	5 6 7

/********************************EXT INT PORT&PINS**********************************/
#define myDDRD   *((volatile u8* const)0X31)
#define myDDRB   *((volatile u8* const)0X37)




#define INT0_pin  2
#define INT0_port myDDRD

#define INT1_pin  3
#define INT1_port myDDRD

#define INT2_pin  2
#define INT2_port myDDRB
/********************************EXT INT TRIGGER **********************************/

typedef enum {rising_edge=0 
			 ,falling_edge
			 ,logic_toggel
			 ,low_level }interrupt_generate;



 
#endif /* INTERRUPT_CONFIG_H_ */