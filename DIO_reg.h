/*
 * DIO_reg.h
 *
 * Created: 7/16/2018 2:09:58 AM
 *  Author: Carnival
 */ 


#ifndef DIO_REG_H_
#define DIO_REG_H_
#include "datatype.h"
#define myPORTA  *((volatile u8* const)0X3B)
#define myDDRA   *((volatile u8* const)0X3A)
#define myPINA   *((volatile u8* const)0X39)
#define myPORTB  *((volatile u8* const)0X38)
#define myDDRB   *((volatile u8* const)0X37)
#define myPINB   *((volatile u8* const)0X36)
#define myPORTC  *((volatile u8* const)0X35)
#define myDDRC   *((volatile u8* const)0X34)
#define myPINC   *((volatile u8* const)0X33)
#define myPORTD  *((volatile u8* const)0X32)
#define myDDRD   *((volatile u8* const)0X31)
#define myPIND	*((volatile u8* const)0X30)


#define porta 0
#define portb 1
#define portc 2
#define portd 3



#define PORT_HIGH 0xff

#define PORT_LOW 0x00

#define LOWER_NIBBLE_HIGH 0x0f

#define UPPER_NIBBLE_HIGH 0xf0

#define HIGH 1

#define LOW 1





#define mySFIOR  *((volatile unsigned char* const)0X50)






#endif /* DIO_REG_H_ */