/*
 * buttons.c
 *
 * Created: 4/2/2015 3:22:41 PM
 *  Author: 305031727
 */   

#include <asf.h>
#include "buttons.h"
#include "modules/lcd12864.h"
#include "modules/timer0.h"

bool gButtonTimerpout  = false;
bool KEY_VALID = false;
uint8_t KEY = KEY_NULL;

uint8_t CountdownTimerHandler;

void buttons_init(void){
	BUTTON_SWITCH_IO_IN;
	BUTTON_IO_PULLUP;

	EICRA |= _BV(ISC11);
	EIMSK |= _BV(1); 
	DDRD &=~_BV(1);
	PORTD |= _BV(1);
	
	sei();
	CountdownTimerHandler = Timer0_AllocateCountdownTimer();

}

ISR(INT1_vect){
cli();	
button_interrupt();
sei();
}




void button_interrupt(){
	uint8_t key_byte = BUTTON_IO_PIN;
	uint8_t key;
	key_byte = ~key_byte;
	
	if(key_byte & _BV(0)) key = BUTTON_DEM;
	else if(key_byte & _BV(1)) key = BUTTON_ALMRST;
	else if(key_byte & _BV(2)) key=BUTTON_ENTER;
	else if(key_byte & _BV(3)) key=BUTTON_MENU;
	else if(key_byte & _BV(4)) key=BUTTON_RIGHT;
	else if(key_byte & _BV(5)) key=BUTTON_LEFT;
	else if(key_byte & _BV(6)) key=BUTTON_UP;
	else if(key_byte & _BV(7)) key=BUTTON_DOWN;
	else key=KEY_NULL;
	
	if(key!=KEY_NULL){
		if(!KEY_VALID){
			KEY = key; KEY_VALID = true; 
		}
		
		
		
	}
	
}

uint8_t getkey(void){
	uint8_t k;
	cli();
	if(KEY_VALID){
		k = KEY;
		KEY_VALID = false;
		
	}
	else k=KEY_NULL;
	sei();
	
	return k;
	
	
	
}