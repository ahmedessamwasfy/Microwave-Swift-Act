/*
 * keypad.c
 *
 * Created: 7/3/2018 1:31:53 AM
 *  Author: Carnival
 */ 
#include "Keypad.h"

void  Keypad_init(void){
	
	set_bit(keypadDDR,R0);
	set_bit(keypadDDR,R1);
	set_bit(keypadDDR,R2);
	set_bit(keypadDDR,R3);
	reset_bit(keypadDDR,C0);
	reset_bit(keypadDDR,C1);
	reset_bit(keypadDDR,C2);
	reset_bit(keypadDDR,C3);
	all_high(keypadPORT);
	set_bit(keypadPORT,R0);
	set_bit(keypadPORT,R1);
	set_bit(keypadPORT,R2);
	set_bit(keypadPORT,R3);
	//DisableGlobalPullup();
	
}

u8 Keypad_getkey(void){
	volatile u8 out=0;
	volatile u8 i=0,j=0;
	for (i=0;i<4;i++)
	{
			set_bit(keypadPORT,R0);
			set_bit(keypadPORT,R1);
			set_bit(keypadPORT,R2);
			set_bit(keypadPORT,R3);
			reset_bit(keypadPORT,R0+i);
		for (j=0;j<4;j++){
				
			out=getbit(keypadPIN,(j+4));
		
			if (!((keypadPIN)&(1<<(j+4)))){
				if (!((keypadPIN)&(1<<(j+4)))){
			//while (!((keypadPIN)&(1<<(j+4))));
			switch(i)
			{
				case(0):
				{
					if (j == 0) return '7';
					else if (j == 1) return '8';
					else if (j == 2) return '9';
					else if (j == 3) return '/';
					break;
				}
				case(1):
				{
					if (j == 0) return '4';
					else if (j == 1) return '5';
					else if (j == 2) return '6';
					else if (j == 3) return '*';
					break;
				}
				case(2):
				{
					if (j == 0) return '1';
					else if (j == 1) return '2';
					else if (j == 2) return '3';
					else if (j == 3) return '-';
					break;
				}
				case(3):
				{
					if (j == 0) return 'C';
					else if (j == 1) return '0';
					else if (j == 2) return '=';
					else if (j == 3) return '+';
					break;
				}
			}
				}
			
			}
			//DELAY_MS(500);
			}
			
	}
	 out=0;
	return out;
}
