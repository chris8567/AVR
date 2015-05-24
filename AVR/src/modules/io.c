/*
 * io.c
 *
 * Created: 2015/5/20 23:42:17
 *  Author: 305031727
 */ 
#include <asf.h>
#include "modules/io.h"

void init_IO(void){
	DDRB |= _BV(0); 
	DDRF |= _BV(3);
	DDRG |= _BV(0);
	
	PORTB |= _BV(0);
	PORTF |= _BV(0);
	PORTG &= ~_BV(0);
	
}

void Alarm(uint8_t state){
	if(state==ON){
		PORTB &=~_BV(0);
		PORTG |=_BV(0);
	}
	else{
		PORTB |= _BV(0);
		PORTG &= ~_BV(0);
	}
	
}

void Clean(uint8_t state){
	if(state==ON){
		PORTF &=~_BV(0);
	}
	else{
		PORTF |= _BV(0);
	}
	
}