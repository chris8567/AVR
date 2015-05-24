/*
 * lcd12864.c
 *
 * Created: 3/30/2015 4:07:17 PM
 *  Author: 305031727
 */ 


#include "modules\lcd12864.h"
#include <asf.h>
#include <string.h>
#include <stdlib.h>


void lcd12864_init(void){
	SWITCH_LCD_IO_OUT;

	LCD12864_RESET;
	LCD12864_BACKLIGHT_ENABLE;

	delay_ms(10);
	lcd12864_send_cmd(0x30);

	lcd12864_send_cmd(0x01);

	lcd12864_send_cmd(0x06);

	lcd12864_send_cmd(0x0c);

}

void lcd12864_clear(void){
	lcd12864_send_cmd(0x01);
	lcd12864_wait_busy();
}

void lcd12864_send_data(uint8_t data){
	uint8_t i;

	for (i=0;i<8;i++){
		if(data & 0x80)
			LCD12864_SID_1;
		else
			LCD12864_SID_0;
			data<<=1;
		LCD12864_CLK_H;
		nop();nop();nop();
		LCD12864_CLK_L;	
	}

	
}

void lcd12864_wait_busy(void){
delay_us(600);
}

void lcd12864_send_cmd(uint8_t cmd){
	LCD12864_ENABLE;
	lcd12864_wait_busy();
	lcd12864_send_data(0xf8);
	lcd12864_send_data(cmd & 0xf0);
	lcd12864_send_data(cmd<<4);
	LCD12864_DISABLE;
}

void lcd12864_set_pos(uint8_t x, uint8_t y){
	uint8_t tmp;
	switch(y){
		case 1:
			tmp=0x80; break;
		case 2:
			tmp=0x90; break;
		case 3:
			tmp=0x88; break;
		case 4:
			tmp=0x98; break;
		default:
			tmp=0x98;
			break;
				
	}
	
	if(x>16) return; 
	
	lcd12864_send_cmd(tmp+(x+1)/2-1);
	if(x%2==0)
		lcd12864_write_char(0x20);
	

	
}

void lcd12864_write_char(char data){
		LCD12864_ENABLE;
		lcd12864_wait_busy();
		lcd12864_send_data(0xfa);
		lcd12864_send_data(0xf0&data);
		lcd12864_send_data(0xf0&data<<4);
		LCD12864_DISABLE;
	
}

void lcd12864_write_str(char *str){
	uint8_t i;
	for(i=0;str[i]!='\0';i++){
		lcd12864_write_char(str[i]);
	}
}

void lcd12864_loop(char *str){
	static char buffer[4][16];
	uint8_t i;
	for(i=0;i<4;i++){
		strcpy(buffer[i],buffer[i+1]);
	}
	strcpy(buffer[3],str);
	
	for (i=0;i<4;i++)
	{
		lcd12864_set_pos(1,i+1);
		lcd12864_write_str(buffer[i]);
		
	}	
}

void lcd12864_write_float(float v){
	char *str=" ";
	itoa((int)v,str,10);
	lcd12864_write_str(str);
	lcd12864_write_char('.');
	float digi = v - (int)v;
	digi*=100;
	itoa((int)digi,str,10);
	lcd12864_write_str(str);
}



