/*
 * io.c
 *
 * Created: 2015/5/20 23:42:17
 *  Author: 305031727
 */ 
#include <asf.h>
#include "modules/io.h"

void init_IO(void){
	//output ports
	DDRB |=_BV(0); //alarm led
	DDRF |=_BV(3); //clean led
	DDRG |=_BV(0); //alarm output
	
	DDRD |=_BV(7); //clean output
	DDRD |=_BV(6); //start fan as star
	DDRD |=_BV(5); //start fan as delta
	DDRD |=_BV(4); //unload dust valve
	
	
	PORTB |= _BV(0);    //alarm led
	PORTF |= _BV(3);	//clean_led
	PORTG &= ~_BV(0);	//alarm_output
	PORTD &= ~(_BV(5)|_BV(6)|_BV(7)|_BV(4));
	
	
	//input ports
	DDRC &= ~(_BV(0)|_BV(1)|_BV(2)|_BV(3));
	//PORTC |= _BV(0); // program disable
	//PORTC |= _BV(1); //alarm reset
	//PORTC |= _BV(2); //start 
	//PORTC |=_BV(3);  //running
	
	
}

void Alarm(bool state){
	if(state==IO_ON){
		PORTB &=~_BV(0);
		PORTG |=_BV(0);
	} 
	else{
		PORTB |= _BV(0);
		PORTG &= ~_BV(0);
	}
	
}

void Clean(bool state){
	if(state==IO_ON){
		PORTF &=~_BV(3);
		PORTD |= _BV(7);
	}
	else{
		PORTF |= _BV(3);
		PORTD &= ~_BV(7);
	}
	
}

void Airfan(uint8_t mode){
	if(mode==STAR){
		PORTD |= _BV(6); 
		PORTD &= ~_BV(5);
	}
	else if(mode == DELTA){
		PORTD &= ~_BV(6);
		PORTD |= _BV(5); 
	}
	else{
		PORTD &= ~_BV(5);
		PORTD &= ~_BV(6); 
	}
	
}

void DustValve(uint8_t sw){
	if(sw == IO_ON)
		PORTD |= _BV(4);
	else
		PORTD &= ~_BV(4);
	
}

bool START_Read(void){
	if(PINC & _BV(2))
		return false;
	else
		return true;
}

bool RUNNING_Read(void){
	if(PINC & _BV(3))
	return false;
	else
	return true;	
	
}

bool PROGDISABLE_Read(void){
	if(PINC & _BV(0))
	return false;
	else
	return true;
}

bool ALARM_RESET_Read(void){
	if(PINC & _BV(1))
	return false;
	else
	return true;
}