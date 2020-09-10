/*
 * VECTOR_TABLE.h
 *
 * Created: 7/18/2018 9:00:23 PM
 *  Author: Carnival
 */ 


#ifndef VECTOR_TABLE_H_
#define VECTOR_TABLE_H_


/********************************VECTOR TABLE**********************************/

#define  EXTERNALinterrupt0								__vector_1
#define  EXTERNALinterrupt1								__vector_2
#define  EXTERNALinterrupt2								__vector_3
#define  TIMER_COUNTER2_COMPARE_MATCH					__vector_4
#define  TIMER_COUNTER2_OVERFLOW						__vector_5
#define  TIMER_COUNTER1_CAPTURE_EVENT					__vector_6
#define  TIMER_COUNTER1_COMPARE_MATCH_A					__vector_7
#define  TIMER_COUNTER1_COMPARE_MATCH_B					__vector_8
#define  TIMER_COUNTER1_OVERFLOW						__vector_9
#define  TIMER_COUNTER0_COMPARE_MATCH					__vector_10
#define  TIMER_COUNTER0_OVERFLOW						__vector_11
#define  SPI_TRANSFERE_COMPLETE							__vector_12
#define  USART_RECIVE_COMPLETE							__vector_13
#define  USART_DATA_REGISTER_EMPTY						__vector_14
#define  USART_TRANSMIT_COMPLETE						__vector_15
#define  ADC_CONVERSION_COMPLETE						__vector_16
#define  EEPROM_READY									__vector_17
#define  ANALOG_COMPARATOR								__vector_18
#define  I2C_INTEERFACE									__vector_19
#define  STORE_PROGRAM_MEMORY_READY						__vector_20

/********************************EXT INT ISR**********************************/
#define ISR(vector, ...) \
void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
void vector(void)



#define mySREG	*(volatile u8*)(0x5F) //global interrupt enable or disable in bit 7
#define global_interrupt_pin 7

#endif /* VECTOR_TABLE_H_ */