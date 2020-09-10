/*
 * GPIO.h
 *
 * Created: 6/28/2018 11:47:18 AM
 *  Author: Ahmed wasfy
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "datatype.h"
#include "DIO_reg.h"



#define set_bit(reg,pin) (reg) |=1 << (pin)
#define reset_bit(reg,pin) (reg) &=~(1<< (pin))
#define toggel_bit(reg,pin) (reg) ^= (1<<(pin))
#define getbit(reg,pin) ((reg>>pin)&(1))


#define set_port(reg,mask) (reg)|=(mask)
#define reset_port(reg,mask) (reg)&=~(mask)
#define toggel_port(reg,mask) (reg)^=(mask)
#define write_port(reg,mask) (reg)=(mask)
#define get_port(reg) (reg)

#define all_high(reg) (reg)=(0xFF)
#define all_low(reg) (reg)=(0x00)



void set_port_value(u8 port  , state PST );
void set_port_direction(u8 port , direction PDR );

void set_pin_value(u8 port ,u8 pin , state PST );
void set_pin_direction(u8 port ,u8 pin , direction PDR );

extern u8 pin_read(u8 port,u8 pin);
extern u8 port_read(u8 port);



void DisableGlobalPullup();
void EnableGlobalPullup();

#endif /* GPIO_H_ */