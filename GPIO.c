/*
 * GPIO.c
 *
 * Created: 6/28/2018 11:47:03 AM
 *  Author: Carnival
 */ 


#include "GPIO.h"

																	
void set_pin_direction(u8 port ,u8 pin , direction PDR ){
	switch(port){
	case porta:
	if(PDR==input){
		reset_bit(myDDRA,pin);
		}else{
		set_bit(myDDRA,pin);
	}
	break;
	case portb:
	if(PDR==input){
		reset_bit(myDDRB,pin);
		}else{
		set_bit(myDDRB,pin);
	}
	break;
	case portc:
	if(PDR==input){
		reset_bit(myDDRC,pin);
		}else{
		set_bit(myDDRC,pin);
	}
	break;
	case portd:
	if(PDR==input){
		reset_bit(myDDRD,pin);
		}else{
		set_bit(myDDRD,pin);
	}
	break;
}
}


void set_pin_value(u8 port ,u8 pin , state PST ){
		switch(port){
			case porta:
			if(PST == low){
				reset_bit(myPORTA,pin);
				}else{
				set_bit(myPORTA,pin);
			}
			break;
			case portb:
			if(PST == low){
				reset_bit(myPORTB,pin);
				}else{
				set_bit(myPORTB,pin);
			}
			break;
			case portc:
			if(PST == low){
				reset_bit(myPORTC,pin);
				}else{
				set_bit(myPORTC,pin);
			}
			break;
			case portd:
			if(PST == low){
				reset_bit(myPORTD,pin);
				}else{
				set_bit(myPORTD,pin);
			}
			break;
		}
}



void set_port_direction(u8 port , direction PDR ){
	
switch(port){
	case porta:
	if(PDR==input){
		all_low(myDDRA);
		}else{
		all_high(myDDRA);
	}
	break;
	case portb:
	if(PDR==input){
		all_low(myDDRB);
		}else{
		all_high(myDDRB);
	}
	break;
	case portc:
	if(PDR==input){
		all_low(myDDRC);
		}else{
		all_high(myDDRC);
	}
	break;
	case portd:
	if(PDR==input){
		all_low(myDDRD);
		}else{
		all_high(myDDRD);
	}
	break;
	default:
	break;
}

}


void set_port_value(u8 port  , u8 value ){
	switch(port){
		case porta:
		myPORTA = value;
		break;
		case portb:
		myPORTB = value;
		break;
		case portc:
		myPORTC = value;
		break;
		case portd:
		myPORTD = value;
		break;
		default:
		break;
	}
}


void EnableGlobalPullup() {
	mySFIOR &= ~(1 << 2);
}


void DisableGlobalPullup() {
	mySFIOR |= (1 << 2);
}

extern u8 port_read(u8 port){
	u8 result=0;
	switch(port){
		case porta:
		result = myPINA;
		break;
		case portb:
		result = myPINB;
		break;
		case portc:
		result = myPINC;
		break;
		case portd:
		result = myPIND;
		break;
		default:
		break;
	}
	return result;
}

extern u8 pin_read(u8 port,u8 pin){
	
	u8 result=0;
	switch(port){
		case porta:
		result = (myPINA>>pin) & (1);
		break;
		case portb:
		result = (myPINB>>pin) & (1);
		break;
		case portc:
		result = (myPINC>>pin) & (1);
		break;
		case portd:
		result = (myPIND>>pin) & (1);
		break;
		default:
		break;
	}
	return result;
	
}