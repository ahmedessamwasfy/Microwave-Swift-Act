/*
 * keypad.h
 *
 * Created: 7/3/2018 1:32:07 AM
 *  Author: Carnival
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "GPIO.h" 

#define  F_CPU 8000000UL

#include<util/delay.h>




//Keypad Information
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define keypadPORT myPORTB
#define keypadPIN myPINB
#define keypadDDR myDDRB

//note you should put the fist 4 bits as output and last as input
//Keypad functions and global variables



void  Keypad_init(void);
u8 Keypad_getkey(void);



#endif /* KEYPAD_H_ */