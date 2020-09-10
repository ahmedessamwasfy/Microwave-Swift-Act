/*
 * lcd.h
 *
 * Created: 6/30/2018 2:37:32 AM
 *  Author: Carnival
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "lcdconfig.h"
#define  F_CPU 8000000UL
#include <util/delay.h>
//user defined pins


// function prototypes

void LCD_init(void);
void LCD_command(u8 cmd);
void LCD_lcdout(u8 out);
void LCD_print_sring(u8* str);
void LCD_Displaychar(u8  );
void LCD_clearscreen(void);
void LCD_IntgerToString(u16 data);
void LCD_GOTO_XY(u8 row,u8 col);


void LCD_Custom_Char (unsigned char loc, unsigned char *msg);
void LCD_Custom_Char_build ();

#endif /* LCD_H_ */
