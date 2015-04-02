/*
 * buttons.c
 *
 * Created: 4/2/2015 3:22:41 PM
 *  Author: 305031727
 */ 

#include <asf.h>
#include "buttons.h"
#include "modules/lcd12864.h"

bool gButtonTimerpout  = false;
bool KEY_VALID = false;

uint8_t CountdownTimerHandle;

void buttons_init(void){
	BUTTON_SWITCH_IO_IN;
	BUTTON_PULLUP;
	EICRB |= _BV(ISC41)|_BV(ISC51)|_BV(ISC61)|_BV(ISC71);
	
	EIMSK |= _BV(BUTTON1_INTRRUPT)|_BV(BUTTON2_INTRRUPT)|_BV(BUTTON3_INTRRUPT)|_BV(BUTTON4_INTRRUPT);
	sei();
	CountdownTimerHandle = Timer0_AllocateCountdownTimer();
	
}

ISR(INT4_vect){
cli();	
button_interrupt(KEY_A);	
sei();
}

ISR(INT5_vect){
	cli();
	button_interrupt(KEY_B);
	sei();
}

ISR(INT6_vect){
	cli();
	button_interrupt(KEY_C);
	sei();
}

ISR(INT7_vect){
	cli();
	button_interrupt(KEY_D);
	sei();
}

void button_interrupt(uint8_t num){
	uint8_t buttons, key;
	key = num;
	
	
}