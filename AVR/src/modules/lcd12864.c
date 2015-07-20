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
#define DELAY 150


void lcd12864_init(void){
	SWITCH_LCD_IO_OUT;
	LCD12864_RESET_0;
	delay_ms(50);
	LCD12864_RESET;
	LCD12864_BACKLIGHT_ENABLE;
	delay_ms(10);
	lcd12864_send_cmd(0x30);
	lcd12864_send_cmd(0x0C);
	lcd12864_send_cmd(0x01);
	lcd12864_send_cmd(0x02);

	lcd12864_send_cmd(0x80);

	lcd12864_send_cmd(0x04);
	lcd12864_send_cmd(0x0C);
	lcd12864_clrGDRAM();
	

}

void lcd12864_clear(void){
	lcd12864_send_cmd(0x01);
	delay_ms(10);

}

void lcd12864_send_byte(uint8_t data){
	uint8_t i;

	for (i=0;i<8;i++){
		LCD12864_CLK_L;	
		if(data & 0x80)
			LCD12864_SID_1;
		else
			LCD12864_SID_0;
			data<<=1;
		nop();nop();nop();
		LCD12864_CLK_H;
		nop();nop();

	}
}

void lcd12864_send_data(uint8_t data){
	LCD12864_ENABLE;
	lcd12864_send_byte(0xfa);
	lcd12864_send_byte(0xf0&data);
	lcd12864_send_byte(0xf0&(data<<4));
	LCD12864_DISABLE;
	lcd12864_wait_busy();
}

void lcd12864_wait_busy(void){
delay_us(DELAY);
}

void lcd12864_send_cmd(uint8_t cmd){
	LCD12864_ENABLE;
	
	lcd12864_send_byte(0xf8);
	lcd12864_send_byte(cmd & 0xf0);
	lcd12864_send_byte(cmd<<4);
	lcd12864_wait_busy();
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
	
	lcd12864_send_cmd(tmp|x); 
	//if(x%2==0)
//		lcd12864_write_char(0x20);
	

	
}

void lcd12864_write_char(char data){

		lcd12864_send_data(data);

	
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


void lcd12864_write_int(int v){
	char *str="    ";
	itoa(v,str,10);
	lcd12864_write_str(str);
}



void lcd12864_SetWhite(uint8_t x, uint8_t y, uint8_t width, uint8_t clear){
	
	uint8_t i,j;
	uint8_t start_x=0, start_y=0;
	uint8_t real_width=0;
	if(y>4) y=4; if(y<1)y=1;
	uint8_t block;
	if(clear) block=0x00; 
	else block = 0xff;
	
	switch(y){
		case 1:
			start_x = 0x80+x/2;
			start_y = 0x80;
			break;
		case 2:
			start_x = 0x80+x/2;
			start_y=0x90;
			break;
		case 3:
			start_x = 0x88+x/2;
			start_y = 0x80;
			break;
		case 4:
			start_x = 0x88+x/2;
			start_y = 0x90;
			break;
		default:
			break;
	}
	
	lcd12864_send_cmd(0x34);
	
	if(x%2==0 && width%2==0){
		real_width = width/2;
		for(i=0;i<16;i++){
			lcd12864_send_cmd(start_y+i);
			lcd12864_send_cmd(start_x);
			for(j=0;j<real_width;j++){
				lcd12864_send_data(block);
				lcd12864_send_data(block);
			}
		}
	}
	else if(x%2==0 && width%2!=0){
		real_width = width/2;
		for(i=0;i<16;i++){
			lcd12864_send_cmd(start_y+i);
			lcd12864_send_cmd(start_x);
			for(j=0;j<real_width;j++){
				lcd12864_send_data(block);
				lcd12864_send_data(block);
			}
			lcd12864_send_data(block);
			lcd12864_send_data(0x00);
		}
	}
	else if(x%2!=0 && width%2==0){
		real_width = width/2-1;
		for(i=0;i<16;i++){
			lcd12864_send_cmd(start_y+i);
			lcd12864_send_cmd(start_x);
			lcd12864_send_data(0x00);
			lcd12864_send_data(block);
			for(j=0;j<real_width;j++){
				lcd12864_send_data(block);
				lcd12864_send_data(block);
			}
			lcd12864_send_data(block);
			lcd12864_send_data(0x00);
		}
		
	}
	else if(x%2!=0 && width%2!=0){
		real_width = width/2;
		for(i=0;i<16;i++){
			lcd12864_send_cmd(start_y+i);
			lcd12864_send_cmd(start_x);
			lcd12864_send_data(0x00);
			lcd12864_send_data(block);
			for(j=0;j<real_width;j++){
				lcd12864_send_data(block);
				lcd12864_send_data(block);
			}
			
		}
	}
	
	lcd12864_send_cmd(0x36);
	lcd12864_send_cmd(0x30);		
}

void lcd12864_clrGDRAM(void){
	uint8_t i,j;
	lcd12864_send_cmd(0x34);
	for(i=0;i<16;i++){
		lcd12864_send_cmd(0x80+i);
		lcd12864_send_cmd(0x80);
		for(j=0;j<16;j++){
			lcd12864_send_data(0x00);
			lcd12864_send_data(0x00);
		}
	}
	for(i=0;i<16;i++){
		lcd12864_send_cmd(0x90+i);
		lcd12864_send_cmd(0x80);
		for(j=0;j<16;j++){
			lcd12864_send_data(0x00);
			lcd12864_send_data(0x00);
		}
	}
	for(i=0;i<16;i++){
		lcd12864_send_cmd(0x80+i);
		lcd12864_send_cmd(0x88);
		for(j=0;j<16;j++){
			lcd12864_send_data(0x00);
			lcd12864_send_data(0x00);
		}
	}
	for(i=0;i<16;i++){
		lcd12864_send_cmd(0x90+i);
		lcd12864_send_cmd(0x88);
		for(j=0;j<16;j++){
			lcd12864_send_data(0x00);
			lcd12864_send_data(0x00);
		}
	}
	
	lcd12864_send_cmd(0x30);
}