/*
 * menu.c
 *
 * Created: 2015/5/24 23:08:22
 *  Author: 305031727
 */ 
#include <asf.h>
#include "menu.h"
#include "modules/lcd12864.h"
#include "modules/adc.h"
#include "modules/timer0.h"
#include "modules/io.h"

uint8_t work_mode=1;

void draw_main_page(void){
	ADC_init();
	lcd12864_set_pos(1,1);
	lcd12864_write_char('0'+work_mode);
	lcd12864_set_pos(8,1);
	lcd12864_write_char(BLOWING_SYM);
	lcd12864_set_pos(15,1);
	lcd12864_write_char(ALARM_SYM);
	lcd12864_set_pos(1,2);
	lcd12864_write_str(STR_PRESSURE_DIFF);
	lcd12864_set_pos(1,3);
	lcd12864_write_str("Åç´µµçÁ÷:");
	lcd12864_set_pos(1,4);
	lcd12864_write_str(STR_MENU_FOOTER1);
	Timer0_RegisterCallbackFunction(refresh_page);
	
}

void refresh_page(void){
	uint16_t pd;
	pd = ADC_read();
	lcd12864_set_pos(7,2);
	lcd12864_write_float((float)pd);
	static uint8_t t=0;
	if(t){
		Alarm(t); t=0;
	}
	else
	{
		Alarm(t); t=1;
		
	}
	
	
}
