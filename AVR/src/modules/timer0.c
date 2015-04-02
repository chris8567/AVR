/*
 * timer0.c
 *
 * Created: 4/2/2015 4:14:09 PM
 *  Author: 305031727
 */ 

#include <asf.h>
#include "modules/timer0.h"

TIMER_CALLBACK_FUNC CallbackFunc[TIMER0_NUM_CALLBACKS];
uint8_t CountDownTimers[TIMER0_NUM_COUNTDOWNTIMERS];

void Timer0_Init(void){
		uint8_t i;
		for (i=0; i<TIMER0_NUM_CALLBACKS; i++)
		CallbackFunc[i] = NULL;
		for (i=0; i<TIMER0_NUM_COUNTDOWNTIMERS; i++)
		CountDownTimers[i] = 0xff;
		TCCR0 = 0x07;
		TCNT0 = 0;
		TIFR |=_BV(TOV0);
		TIMSK |= _BV(OCIE0);
		sei();
}

void timer0_event(void){
	uint8_t i;
	for (i=0; i<TIMER0_NUM_CALLBACKS; i++)
	if (CallbackFunc[i] != NULL)
	CallbackFunc[i]();
	
	for (i=0; i<TIMER0_NUM_COUNTDOWNTIMERS; i++)
	if (CountDownTimers[i] != 0xff && CountDownTimers[i] != 0)
	CountDownTimers[i]--;
	
}

ISR(TIMER0_COMP_vect){

	static uint8_t count=0;
	if(count++==30){
		timer0_event();
		count = 0;
	}
	
}

bool Timer0_RegisterCallbackFunction(TIMER_CALLBACK_FUNC pFunc)
{
	uint8_t i;
	
	for (i=0; i<TIMER0_NUM_CALLBACKS; i++)
	{
		if (CallbackFunc[i] == pFunc)
		return true;
	}
	
	for (i=0; i<TIMER0_NUM_CALLBACKS; i++)
	{
		if (CallbackFunc[i] == NULL)
		{
			CallbackFunc[i] = pFunc;
			return true;
		}
	}
	
	return false;
}

bool Timer0_RemoveCallbackFunction(TIMER_CALLBACK_FUNC pFunc)
{
	uint8_t i;
	
	for (i=0; i<TIMER0_NUM_CALLBACKS; i++)
	{
		if (CallbackFunc[i] == pFunc)
		{
			CallbackFunc[i] = NULL;
			return true;
		}
	}
	
	return false;
}

uint8_t Timer0_AllocateCountdownTimer(void)
{
	uint8_t i;
	for (i=0; i<TIMER0_NUM_COUNTDOWNTIMERS; i++)
	if (CountDownTimers[i] == 255)
	{
		CountDownTimers[i] = 0;
		return i+1;
	}

	return 0;
}

uint8_t Timer0_GetCountdownTimer(uint8_t timer)
{
	uint8_t t;
	cli();
	t = CountDownTimers[timer-1];
	sei();
	
	return t;
}

void Timer0_ReleaseCountdownTimer(uint8_t timer)
{
	cli();
	CountDownTimers[timer-1] = 255;
	sei();
}


