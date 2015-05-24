/*
 * adc.c
 *
 * Created: 2015/5/24 16:16:37
 *  Author: 305031727
 */ 
#include <asf.h>
#include <util/delay.h>
#include "adc.h"

void ADC_init(void){
	DDRF &=~(_BV(0)|_BV(1));
	
	ADCSRA =0x86;
	ADMUX = 0x10;
	ADCSRA &=~_BV(ADFR);
}

uint16_t ADC_readonce(void){
	uint16_t result = 0;
	ADCSRA |= _BV(ADSC);
	while(!bit_is_set(ADCSRA,ADIF));
	_delay_us(100);
	result = ADCL;
	result += ADCH*256;

	return result;	
}

float ADC_read(uint8_t target){
	float buff = 0;
	uint8_t i = 0;
	switch(target){
		case PRESSURE:
			ADMUX = 0x10;
			break;
		case EMV:
			ADMUX = 0b00000100;
			break;
		case VIN:
			ADMUX = 0b00000101;
			break;
		case VPP:
			ADMUX = 0b00000110;
			break;
		case VCC:
			ADMUX = 0b00000111;
			break;
		default:
		break;
		
	}
	
	for(i=0;i<8;i++)
		buff+= ADC_readonce();
	buff /=8;
	buff/=1024;
	buff*=SCALE;
	return buff;
	
}