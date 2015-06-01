/*
 * emv.c
 *
 * Created: 2015/6/1 19:42:51
 *  Author: 305031727
 */ 

#include <asf.h>
#include <util/delay.h>
#include "modules/emv.h"
#include "modules/timer0.h"

uint16_t emv_switches = 0xffff;
uint16_t emv_control_word = 0xff;
bool emv_working = false;
uint8_t blower_on_time_ms = 100;
uint8_t blower_interval_s = 2; 
void emv_ports_init(void){
	DDRB |= _BV(7)|_BV(6)|_BV(5);
	DDRG |= _BV(4)|_BV(4);
	MR_HIGH;
	OEn_LOW;
	
}

void set_emv_ctrl_word(uint16_t emv_word){
	emv_control_word = emv_word;
	emv_refresh();
	
}

void set_emv_channel(uint8_t channel){
	if(channel>0 && channel <=16)
	emv_switches |= _BV(channel);
	emv_refresh();
}

void unset_emv_channel(uint8_t channel){
		if(channel>0 && channel <=16)
		emv_switches &=~_BV(channel);
		emv_refresh();
	
}

void emv_refresh(void){
	uint8_t i=0;
	uint16_t buffer = emv_switches;
	SCK_LOW;
	RCK_LOW;
	for(i=0;i<16;i++){
		if(buffer & 0x01) DATA_HIGH;
		else DATA_LOW;
		buffer = buffer>>1;
		SCK_HIGH; 
		SCK_LOW;
	}
	RCK_HIGH;
	
}

void set_blower_interval(uint8_t intv_s){
	blower_interval_s = intv_s;
}
void set_blower_on_time(uint8_t time_ms){
	blower_on_time_ms = time_ms;
}
uint8_t start_sequence(void){
	if(emv_working == true) 
	return 1;
	emv_working = true;
	//Timer0_RegisterCallbackFunction(blow_seq);
	return 0;

}

void blow_seq(void){
	static uint8_t i=15;
	static uint8_t count = 0;
	if(count++!=0 && count <= blower_interval_s) return;
	if(emv_control_word | _BV(i)){
		set_emv_channel(i);
		//_delay_ms(blower_on_time_ms);
		unset_emv_channel(i);
	}
	else{
		
		while(!(emv_control_word |_BV(--i)));
		
	}
	
	count = 1;
	

}