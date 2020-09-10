/*
 * lcd.c
 *
 * Created: 6/30/2018 2:37:18 AM
 *  Author: Carnival
 */ 
#include "lcd.h"
#include <stdlib.h>


void LCD_Custom_Char (unsigned char loc, unsigned char *msg)
{
    unsigned char i;
    if(loc<8)
    {
     LCD_command (0x40 + (loc*8));  /* Command 0x40 and onwards forces 
                                       the device to point CGRAM address */
       for(i=0;i<8;i++)  /* Write 8 byte for generation of 1 character */
           LCD_lcdout(msg[i]);      
    }   
}

void LCD_Custom_Char_build (){

unsigned char Character1[8] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 };  /* Custom char set for alphanumeric LCD Module */
unsigned char Character2[8] = { 0x04, 0x1F, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F };
unsigned char Character3[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00 };
unsigned char Character4[8] = { 0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01 };
unsigned char Character5[8] = { 0x01, 0x03, 0x05, 0x09, 0x09, 0x0B, 0x1B, 0x18 };
unsigned char Character6[8] = { 0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04, 0x04 };
unsigned char Character7[8] = { 0x00, 0x00, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00 };
unsigned char Character8[8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 };

	/* ---------- Build Custom Characters -----------------*/
	
	LCD_Custom_Char(0, Character1);  /* Build Character1 at position 0 */
	LCD_Custom_Char(1, Character2);  /* Build Character2 at position 1 */
	LCD_Custom_Char(2, Character3);  /* Build Character3 at position 2 */
	LCD_Custom_Char(3, Character4);  /* Build Character4 at position 3 */
	LCD_Custom_Char(4, Character5);  /* Build Character5 at position 4 */
	LCD_Custom_Char(5, Character6);  /* Build Character6 at position 5 */
	LCD_Custom_Char(6, Character7);  /* Build Character6 at position 6 */
	LCD_Custom_Char(7, Character8);  /* Build Character6 at position 7 */
   
}




void LCD_init(void){
	// SET THE DIRECTIONS 
	all_high(LCD_DATA_PORT_DIR);
	set_bit(LCD_CTRL_PORT_DIR,RS);	
	set_bit(LCD_CTRL_PORT_DIR,RW);
	set_bit(LCD_CTRL_PORT_DIR,E);	
		
	//SET THE INITIAL VALUE 
	all_low(LCD_DATA_PORT);
	reset_bit(LCD_CTRL_PORT,RS);
	reset_bit(LCD_CTRL_PORT,RW);
	reset_bit(LCD_CTRL_PORT,E);
	

	#if (LCD_MODE==8)
		
		_delay_ms(20);
		LCD_command(LCD_FUNCTION_8BIT_2LINES);//0x38
	//	_delay_us(100);
		
	#warning "you are in 8 bit mode in LCD"	
	
	#elif (LCD_MODE==4)
				
				_delay_ms(20);
				LCD_command(0x33);//setting up 4 bit mode
				_delay_us(100);
				LCD_command(0x32);//setting up 4 bit mode
				_delay_us(100);
				LCD_command(LCD_FUNCTION_4BIT_2LINES);//setting up 4 bit mode 0x28
				_delay_us(100);		
				#warning "you are in 4 bit mode in LCD"
				
	#else //we should write an error message or act as 8 is default 
			#error "as7ale yasta w 7ot fel LCD_MODE 4 aw 8 w mat5tare34"
	
	#endif
	
	LCD_command(LCD_DISP_ON_CURSOR);//Display on - cursor blinking
//	_delay_us(100);
	LCD_command(LCD_ENTRY_MODE);//Clear display
//	_delay_us(2000); 
	LCD_command(LCD_ENTRY_INC_);//init command
	
}




void LCD_command(u8 cmd){
	if (LCD_MODE==8){
		write_port(LCD_DATA_PORT,cmd);
		_delay_us(100);
	}
	else if (LCD_MODE==4){
		all_low(LCD_DATA_PORT);
		set_port(LCD_DATA_PORT,(cmd&0xF0));
		reset_bit(LCD_CTRL_PORT,RS); 
		reset_bit(LCD_CTRL_PORT,RW);	
		set_bit(LCD_CTRL_PORT,E);
		_delay_us(1);
		reset_bit(LCD_CTRL_PORT,E);
		_delay_us(100);
		all_low(LCD_DATA_PORT);
		set_port(LCD_DATA_PORT,((cmd<<4)&(0xF0)));
	}
	reset_bit(LCD_CTRL_PORT,RS);
	reset_bit(LCD_CTRL_PORT,RW);
	set_bit(LCD_CTRL_PORT,E);
	_delay_us(1);
	reset_bit(LCD_CTRL_PORT,E);
	_delay_us(100);
	
	
	
}


void LCD_lcdout(u8 out){
	
	
	//_delay_us(100);
	if (LCD_MODE==8){
		write_port(LCD_DATA_PORT,out);
		_delay_us(100);
		set_bit(LCD_CTRL_PORT,RS);
	}
	else if (LCD_MODE==4){
		write_port(LCD_DATA_PORT,(out&0xF0));
		reset_bit(LCD_CTRL_PORT,RS);  // 4AKEK EN FEH ERROR HENA BDAL RESET SET
		reset_bit(LCD_CTRL_PORT,RW);
		set_bit(LCD_CTRL_PORT,E);
		_delay_us(1);
		reset_bit(LCD_CTRL_PORT,E);
		_delay_us(100);
		write_port(LCD_DATA_PORT,(out<<4));
		set_bit(LCD_CTRL_PORT,RS); 
		
	}

	reset_bit(LCD_CTRL_PORT,RW);
	set_bit(LCD_CTRL_PORT,E);
	_delay_us(1);
	reset_bit(LCD_CTRL_PORT,E);
	_delay_us(100);
}



void LCD_print_sring(u8* str){
	u8 i=0;
	while(str[i]!=0 /*which is ascii of null '\0'*/){
		LCD_lcdout(str[i]);
		i++;
		if (i==16)
		{LCD_GOTO_XY(1,0);
		}
	}
}
	
	void LCD_clearscreen(void){
		
		LCD_command(LCD_CLEAR_SCREEN);
		
	}
	
	
	void LCD_IntgerToString(u16 data)//think about other way to do this function without stdlib.h library
	{ 
		char buff[16]; // String to hold the ascii result
		itoa(data,buff,10); //10 for decimal
		LCD_print_sring(buff);
		
	}
	
	
void LCD_GOTO_XY(u8 row,u8 col)
{
	u8 Address;
	
	/* first of all calculate the required address */
	if(row==0)	Address=col; 
	else	Address=col+0x40;	//first location in the second row is 0x40
								// actually it is 0xC0 but it will be as this after we or 0x40 an 0x80
	
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_command(Address | LCD_BEGIN_AT_FIRST_RAW);  //same as address+0x80
}