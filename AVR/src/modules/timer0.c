/*
 * timer0.c
 *
 * Created: 4/2/2015 4:14:09 PM
 *  Author: 305031727
 */ 

#include <asf.h>
#include "modules/timer0.h"
#include <avr/io.h>

timer_event EventList[TIMER0_NUM_CALLBACKS];
uint8_t CountDownTimers[TIMER0_NUM_COUNTDOWNTIMERS];


void Timer0_Init(void){
		uint8_t i;
		for (i=0; i<TIMER0_NUM_CALLBACKS; i++){
		EventList[i].pFunc = NULL;
		EventList[i].event_intval = 0;
		EventList[i].counter = 0;
		}
		for (i=0; i<TIMER0_NUM_COUNTDOWNTIMERS; i++)
		CountDownTimers[i] = 0xff;
		TCCR0 =0;
		TCCR0 |= _BV(CS00)|_BV(CS01)|_BV(CS02);
		TCNT0 = 184;
		TIFR |=_BV(TOV0);
		TIMSK |= _BV(OCIE0);
			sei();
}


ISR(TIMER0_COMP_vect){
	static uint16_t tmp_counter=0;
	TCNT0 = 184;
	uint8_t i;
	for(i=0;i<TIMER0_NUM_CALLBACKS;i++){
		if(EventList[i].pFunc !=NULL){
			if(EventList[i].counter == EventList[i].event_intval){
				EventList[i].counter = 0;
				EventList[i].pFunc();
			}
		else 
			EventList[i].counter++;
		}
	}
	
	if(tmp_counter++==100){
		for(i=0;i<TIMER0_NUM_COUNTDOWNTIMERS;i++){
			if(CountDownTimers[i] != 0xff && CountDownTimers[i]!=0)
				CountDownTimers[i]--;
		}
		tmp_counter =0;
	}
	
}

bool Timer0_RegisterCallbackFunction(TIMER_CALLBACK_FUNC pFunc, uint16_t time_interval)
{
	uint8_t i;
	if(time_interval < 10) 
		time_interval = 10;
		
	for (i=0; i<TIMER0_NUM_CALLBACKS; i++)
	{
		if (EventList[i].pFunc == pFunc)
		return true;
	}
	
	for (i=0; i<TIMER0_NUM_CALLBACKS; i++)
	{
		if (EventList[i].pFunc == NULL)
		{
			EventList[i].pFunc = pFunc;
			EventList[i].event_intval = time_interval/10;
			EventList[i].counter = 0;
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
		if (EventList[i].pFunc == pFunc)
		{
			EventList[i].pFunc = NULL;
			EventList[i].event_intval =0;
			EventList[i].counter = 0;
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


