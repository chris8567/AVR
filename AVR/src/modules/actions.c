/*
 * actions.c
 *
 * Created: 2015/6/29 20:57:12
 *  Author: 305031727
 */ 

#include "actions.h"
#include "modules/lcd12864.h"
#include "modules/io.h"
#include "modules/menu.h"
#include "modules//adc.h"
#include <stdlib.h>
#define ADC_UPPER_LIMIT 920
#define ADC_UPPER_VALUE 3400
#define DEFAULT_PD_UPPER 1020
#define DEFAULT_PD_LOWER 510
#define DEFAULT_BLOWER_COUNTER_LIMIT 1000000
#define ON 1
#define OFF 0

#define UNIT_MMH2O 0x01;
#define UNIT_PA	   0x02;

uint8_t PD_Unit = UNIT_PA;
uint16_t PD_Upper_Limit = DEFAULT_PD_UPPER;
uint16_t PD_Lower_Limit = DEFAULT_PD_LOWER;
uint8_t PD_Mode =1;
uint8_t Alarm_State = OFF;
uint8_t Blowing_State = OFF;

#define MODE0 "[X]"
#define MODE1 "[1]"
#define MODE2 "[2]"
#define MODE3 "[3]"

void Act_Update_Main(void){
	static uint8_t blink_factor = 0;
	blink_factor = !blink_factor;
	static uint16_t days=0, hours=0, m=0,s=0;
	char *time="00d00h00m";
	char pdstr[4];
	int pressure_diff = (int)ADC_read(PRESSURE);
	itoa(pressure_diff,pdstr,10);
	lcd12864_set_pos(0,1);
	switch(PD_Mode){
		case 1:
		lcd12864_write_str(MODE1);
		break;
		case 2:
		lcd12864_write_str(MODE2);
		break;
		case 3:
		lcd12864_write_str(MODE3);
		break;
		default:
		lcd12864_write_str(MODE0);
		break;
	}
	
	lcd12864_set_pos(4,1);
	if(Blowing_State){
		if(blink_factor)
		lcd12864_write_char(0x0f);
		else
		lcd12864_write_char(0x09);
	}
	else{
		if(blink_factor)
		lcd12864_write_char(0x07);
		else
		lcd12864_write_char(0x09);
		
	}
	
	lcd12864_set_pos(7,1);
	if(Alarm_State){
		if(blink_factor)
			lcd12864_write_char(0x21);
		else
			lcd12864_write_char(' ');
	}
	else{
		lcd12864_write_char(0x02);
		
	}
	
	lcd12864_set_pos(5,2);
	lcd12864_write_str(pdstr);
	lcd12864_set_pos(3,3);
	s++;
	if(s==60){
		m++; s=0;
	}
	if(m==60){
		hours++; m=0;
	}
	if(hours == 24){
		days++;
	}
	time[7]=m%10+'0';
	time[6]=m/10+'0';
	time[4]=hours%10+'0';
	time[3]=hours/10+'0';
	time[1]=days%10+'0';
	time[0]=days/10+'0';

	lcd12864_write_str(time);
	
	
	if(pressure_diff > PD_Upper_Limit){
		Alarm_State = 1;
		Alarm(1);
	}
	else if(pressure_diff < PD_Lower_Limit){
		Alarm_State=0;
		Alarm(0);
	}


}

void Act_pressure_setting1_display(void){
	lcd12864_set_pos(6,3);
	lcd12864_write_int(PD_Upper_Limit);
	lcd12864_set_pos(6,2);
	lcd12864_write_int(PD_Lower_Limit);
}


void Act_PdUAddone(void){
	;
}
void Act_PdDDecone(void){
	;
}

void Act_PdUAddten(void){
	;
}
void Act_PdDDecten(void){
	;
}
void Act_PdUAddHud(void){
	;
}
void Act_PdDDecHud(void){
	;
}
void Act_SwitchUnit(void){
	;
}
void Act_PdUApply(void){
	;
}

void Act_DispUnit(void){
	;
}