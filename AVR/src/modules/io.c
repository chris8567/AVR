/*
 * io.c
 *
 * Created: 2015/5/20 23:42:17
 *  Author: 305031727
 */ 
#include <asf.h>
#include "modules/io.h"

void init_IO(void){
	DDRB |=_BV(0); 
	DDRF |=_BV(3);
	DDRG |=_BV(0);
	
	PORTB |= _BV(0);
	PORTF |= _BV(3);
	PORTG &= ~_BV(0);
	
}

void Alarm(bool state){
	if(state==ALARM_ON){
		PORTB &=~_BV(0);
		//PORTG |=_BV(0);
	}
	else{
		PORTB |= _BV(0);
		//PORTG &= ~_BV(0);
	}
	
}

void Clean(bool state){
	if(state==ALARM_ON){
		PORTF &=~_BV(3);
	}
	else{
		PORTF |= _BV(3);
	}
	
}