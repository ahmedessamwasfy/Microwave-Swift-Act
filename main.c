/*
 * Swift_Act_microwave_projectr.c
 *
 * Created: 2/23/2020 2:39:09 PM
 * Author : Ahmed Wasfy
 */ 


/* ----------------------------[Includes]------------------------------*/
#include "GPIO.h"
#include "lcd.h"
#include "timer0.h"
#include "Timer2.h"
#include "keypad.h"
#include "interrupt.h"



/*	Common
	*STD_Types
	
	MCAL
	* DIO
	* PWM
	* External_interrupts
	
	HAL
	* LCD
	* Keypad

*/


/**
 * @defgroup main_private_typedefs
 * @{
 */


/**
 * @}
 */

/**
 * @defgroup main_private_defines
 * @{
 */
/**
 * @brief   Buffer array size
 */

#define START_BUTTON_PORT	portd
#define START_BUTTON_PIN	1

#define CANCEL_BUTTON_PORT	portd
#define CANCEL_BUTTON_PIN	2

#define DOOR_SENSOR_PORT	portd
#define DOOR_SENSOR_PIN		3

#define WEIGHT_SENSOR_PORT	portd
#define WEIGHT_SENSOR_PIN	4
								
#define HEATER_OUTPUT_PORT	portd
#define HEATER_OUTPUT_PIN	6	
								
#define LAMP_OUTPUT_PORT	portd
#define LAMP_OUTPUT_PIN		5	
								
#define MOTOR_OUTPUT_PORT	portd
#define MOTOR_OUTPUT_PIN	7	
								
								





/**
 * @}
 */

/**
 * @defgroup main_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_variables
 * @{
 */

void  (*LCD_Current_state) (void);

void  (*Microwave_Current_state) (void);

void (*Button_Current_State)(void);


	//int min=0;
	//int sec=0;
	boolen door_sensor=false;
	boolen weight_sensor=false;
	boolen Start_button=false;
	boolen Cancel_button=false;
	volatile u8  min=0;
	volatile u8  sec=0;
	
	volatile u8 Timer_count=0;
	
	u8 Current_state=0;
	
	
	
	
volatile u8 port_dir=0;
volatile u8 prev_key_value=0;


/**
 * @brief   Source and destination buffers
 */

/**
 * @}
 */

/**
 * @defgroup main_private_function_prototypes
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_functions
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_exported_functions
 * @{
 */


/* ----------------------------[Function prototypes]------------------------------*/



/**
 * @brief   Buttons_Check function
 * @note
 * @param   none
 * @retval  none
 */
void Buttons_Sensors_init(void);




/**
 * @brief   Sensor_Button_Check function
 * @note
 * @param   none
 * @retval  none
 */
 void Sensor_Button_Check(void);


/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void Current_State_Update(void);



/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void Heating_Start(void);





/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void Heating_Stop(void);






/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void LCD_Start_Screen(void);





/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void LCD_timer_update(void);


/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void LCD_Error_Prev(void);





void Time_out_check(void);


void Timer0_ISR(void);


void External_Interrupt_0_ISR(void);




/*								Sequence
	
	1.Power ON :- a)INIT all modules 
				  b)close all actuators and lamps and reset counter and LCD
				  c)Enter Hold state "read data from Keypad ONLY"
	2.Start to input Time
	3.check Door and Weight:- a)if OK continue 
							  b)if NOT_OK show in LCD Error or a check box for sensors
	4.hold on start button :- a)if not entered keep reading for key pad
							  b)if entered continue
	5.Show the Count down on LCD
	6.Operate motor , heater , and  lamp & start countdown & check continuously on door 
	7. a)if Time is up return to 1->b
	   b)if door is opened return to 1->b
	   c)if cancel is clicked return to 1->b
	   
	   
	
								Main Screen States
	1. Waiting Screen :- lamp is off , motor is off ,heater is off , timer not counting 
						 listen to :- sensors and Keypad and Start button
	2.Heating Screen :- lamp is on , motor is on ,heater is on , timer is counting
						listen to :- Door and Cancel Button 
	
	
*/


int main(void)
{
	LCD_init(); //done
	Keypad_init();//done
	
	Buttons_Sensors_init();//check
	
	timer0_init();// done
	Timer2_init();// done
	
	interrupt_init();//not done
	interrupt_INT0(falling_edge);
	
	LCD_Current_state=LCD_Start_Screen;//done
	
	//Microwave_Current_state=Heating_Stop;
	
	//Button_Current_State=Sensor_Button_Check;
	
	Heating_Stop();
	SET_ISR_FUN_overflow_timer0(Timer0_ISR);
	interrupt0_isr_Set(External_Interrupt_0_ISR);
	

    while (1) 
    {
		
		Time_out_check();
		Sensor_Button_Check();
		Current_State_Update();
		LCD_Current_state();

    }
}

/* ----------------------------[Function prototypes]------------------------------*/

/**
 * @brief   Buttons_Check function
 * @note
 * @param   none
 * @retval  none
 */
void Buttons_Sensors_init(void){
	
		//set_pin_direction(); for weight sensor
		set_pin_direction(WEIGHT_SENSOR_PORT,WEIGHT_SENSOR_PIN,input);
		//set_pin_direction(); for door sensor
		set_pin_direction(DOOR_SENSOR_PORT,DOOR_SENSOR_PIN,input);
		
		//set_pin_direction(); for lamp
		set_pin_direction(LAMP_OUTPUT_PORT,LAMP_OUTPUT_PIN,output);
		//set_pin_direction(); for heater
		set_pin_direction(HEATER_OUTPUT_PORT,HEATER_OUTPUT_PIN,output);
		//set_pin_direction(); for motor
		set_pin_direction(MOTOR_OUTPUT_PORT,MOTOR_OUTPUT_PIN,output);
		
		//for Start_button
		set_pin_direction(START_BUTTON_PORT,START_BUTTON_PIN,input);
		//for Canclel button
		set_pin_direction(CANCEL_BUTTON_PORT,CANCEL_BUTTON_PIN,input);
	
}






/**
 * @brief   Sensor_Button_Check function
 * @note
 * @param   none
 * @retval  none
 */
 void Sensor_Button_Check(void){
	 //Check weight sensor
	 weight_sensor=pin_read(WEIGHT_SENSOR_PORT,WEIGHT_SENSOR_PIN);
	 //check door sensor
	 door_sensor=pin_read(DOOR_SENSOR_PORT,DOOR_SENSOR_PIN);
	 //check start button
	 Start_button=pin_read(START_BUTTON_PORT,START_BUTTON_PIN);	 
 }


/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void Current_State_Update(void){
	/*
		1.check on buttons
		2.check on keypad
		3.check on sensors
		4.assign lcd to lcd_update
		5.assign  heater state
		6.activate heater state if there is change
	
	*/
	/*
		void  (*LCD_Current_state) (void);

		void  (*Microwave_Current_state) (void);

		void (*Button_Current_State)(void);

	*/
	switch(Current_state){
		
		case 0: //start screen case 
				if(Cancel_button||((min|sec)==0)) {Cancel_button=0; min=0; sec=0; break;}
				else if(Start_button&&door_sensor&&weight_sensor){
//					Button_Current_State=Sensor_Button_Check;
					LCD_Current_state=LCD_timer_update;
					Heating_Start();
					Current_state=1;
					
				}
				else {
					LCD_Current_state=LCD_Error_Prev; 
					Current_state=2;	
				}
				break;
		
		case 1://heating screen
				
				if(Cancel_button||((min|sec)==0)){
					Cancel_button=0;
					min=0;sec=0;
	//				Button_Current_State=Sensor_Button_Check;
					LCD_Current_state=LCD_Start_Screen;
					Heating_Stop();
					Current_state=0;
				}
				else if ((!door_sensor)||(!weight_sensor)){
					LCD_Current_state=LCD_Error_Prev;
					Heating_Stop();
					Current_state=2;
				}
				else break; 
				break;
		case 2: //error prievew
		
				if(Cancel_button||((min|sec)==0)){
					Cancel_button=0;
					min=0;sec=0;
//					Button_Current_State=Sensor_Button_Check;
					LCD_Current_state=LCD_Start_Screen;
					Heating_Stop();
					Current_state=0;
				}
				else if(Start_button&&door_sensor&&weight_sensor){
//					Button_Current_State=Sensor_Button_Check;
					LCD_Current_state=LCD_timer_update;
					Heating_Start();
					Current_state=1;
					
				}
				else break; 
				break;
	
	
	}
	
}



/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void Heating_Start(void){
	Timer0_Start();
	Timer2_Start();
	set_pin_value(HEATER_OUTPUT_PORT,HEATER_OUTPUT_PIN,high);
	set_pin_value(LAMP_OUTPUT_PORT,LAMP_OUTPUT_PIN,high);
	
	
	LCD_clearscreen();
	LCD_GOTO_XY(0,0);
	LCD_print_sring(" Start Heating");
	
	
	LCD_GOTO_XY(1,1);
	if (min<10)LCD_lcdout('0');
	LCD_IntgerToString(min);
	LCD_lcdout(':');
	if (sec<10)LCD_lcdout('0');
	LCD_IntgerToString(sec);
}







/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void Heating_Stop(void){
		Timer0_Stop();
		Timer2_Stop();
		
		set_pin_value(HEATER_OUTPUT_PORT,HEATER_OUTPUT_PIN,low);
		set_pin_value(LAMP_OUTPUT_PORT,LAMP_OUTPUT_PIN,low);
		
		LCD_clearscreen();
		LCD_GOTO_XY(0,0);
		LCD_print_sring(" Stop Heating");
		
		

}





/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void LCD_Start_Screen(void){
	
	 Timer0_Stop();
	 Timer2_Stop();
	
	LCD_clearscreen();
	LCD_GOTO_XY(0,0);
	LCD_print_sring(" Time door food");
	LCD_GOTO_XY(1,0);
	LCD_print_sring(" 00:00  ");
	LCD_lcdout(door_sensor+'0');
	LCD_print_sring("    ");
	LCD_lcdout(weight_sensor+'0');
	volatile u8  i=0;
//	volatile u8 key_value=Keypad_getkey();
//	if((key_value==0)||((key_value-'0')>10)||((key_value-'0')<0))continue;
	//_delay_ms(200);
	
	for (i=0;i<4;i++)
	{
		volatile u8 key_value=Keypad_getkey();
		if((key_value==0)||(key_value==prev_key_value)||((key_value-'0')>10)||((key_value-'0')<0)){i--;prev_key_value=key_value;continue;}
		
		
		if (i<2)
		{
			//min=key_value-'0';
			min=((min%10)*(10>>(3*!i))+(key_value-'0'));
		}
		else{
			//sec=key_value-'0';
			sec=(sec%10)*(10>>(3*!(i-2)))+(key_value-'0');
			
			
		}
		LCD_GOTO_XY(1,1);
		//LCD_IntgerToString(time);
		//if (time!=0)LCD_lcdout(time);
		
		
		if (min<10)LCD_lcdout('0');
		LCD_IntgerToString(min);
		LCD_lcdout(':');
		if (sec<10)LCD_lcdout('0');
		LCD_IntgerToString(sec);
		
		if (Cancel_button||Start_button)break;
		prev_key_value=key_value;
		//_delay_ms(5);		
	}
	
	
	
	
	
}




/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void LCD_timer_update(void){

		
	
	
	LCD_GOTO_XY(1,1);
	if (min<10)LCD_lcdout('0');
	LCD_IntgerToString(min);
	LCD_lcdout(':');
	if (sec<10)LCD_lcdout('0');
	LCD_IntgerToString(sec);
	Timer2_set_CTC_value(OCR2_intial_value);

		
}


/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
void LCD_Error_Prev(void){

	LCD_GOTO_XY(1,8);
//	LCD_print_sring(" 00:00  ");
	LCD_lcdout(door_sensor+'0');
	LCD_print_sring("    ");
	LCD_lcdout(weight_sensor+'0');
		_delay_ms(10);
}





void Time_out_check(void){

if(Timer_count>121){ //14
	Timer_count%=122;//15
	set_pin_value(portd,0,high);
	
	if(min==0&&sec==0)return;
	if (sec==0){
		min--;
		sec=60;
	}
	sec--;
	
	
}


}


void Timer0_ISR(void){
	
	
	Timer_count++;
}


void External_Interrupt_0_ISR(void){
	
	
	Cancel_button=1;
}
