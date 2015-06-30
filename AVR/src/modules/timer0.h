/*
 * timer0.h
 *
 * Created: 4/2/2015 4:11:40 PM
 *  Author: 305031727
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_
#include <asf.h>

typedef void (*TIMER_CALLBACK_FUNC) (void);

#define TIMER0_NUM_CALLBACKS        8
#define TIMER0_NUM_COUNTDOWNTIMERS  8
typedef struct Event_Struct{
	TIMER_CALLBACK_FUNC pFunc;
	uint16_t event_intval;
	uint16_t counter;
	}timer_event;

void Timer0_Init(void);

bool Timer0_RegisterCallbackFunction(TIMER_CALLBACK_FUNC pFunc,uint16_t intv_time);
bool Timer0_RemoveCallbackFunction(TIMER_CALLBACK_FUNC pFunc);


uint8_t Timer0_AllocateCountdownTimer(void);
uint8_t Timer0_GetCountdownTimer(uint8_t timer);
void Timer0_SetCountdownTimer(uint8_t timer, uint8_t value);
void Timer0_ReleaseCountdownTimer(uint8_t timer);

void timer0_event(void);



#endif /* TIMER0_H_ */