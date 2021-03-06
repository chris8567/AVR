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
#include "modules/adc.h"
#include "modules/emv.h"
#include <stdlib.h>

  

uint8_t PD_Unit = UNIT_PA;
float PD_Upper_Limit = DEFAULT_PD_UPPER;
float PD_Lower_Limit = DEFAULT_PD_LOWER;
uint8_t PD_Mode =1;
uint8_t Alarm_State = OFF;
bool Blowing_State = false;

bool switch_start = false;
bool swtich_monitoring = false;
uint8_t Delay_DustvavleToFan=5;
uint8_t Delay_FanStarToDelta=5; 
uint8_t Delay_FantoDustvavle=5;


#define MODE0 "[X]"
#define MODE1 "[1]"
#define MODE2 "[2]"
#define MODE3 "[3]"

void Act_Update_Main(void){
	static uint8_t blink_factor = 0;
	static int days=0;
	static uint8_t hours=0, m=0,s=0;
	blink_factor = !blink_factor;
	static char *time="00d00h00m";
	int pressure_diff = (int)ADC_read(PRESSURE);

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
	if(swtich_monitoring){
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
	}
	else{
		lcd12864_write_char(' ');
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
	WriteBlank(6);
	lcd12864_set_pos(5,2);
	if(PD_Unit == UNIT_PA)
	lcd12864_write_float(Fun_UnitChange(pressure_diff),0);
	else
	lcd12864_write_float(Fun_UnitChange(pressure_diff),1);

	lcd12864_set_pos(3,3);
	if(swtich_monitoring){
	s++;
	if(s==60){
		m++; s=0;
	}
	if(m==60){
		hours++; m=0;
	}
	if(hours == 24){
		days++; hours =0;
	}
	time[7]=m%10+'0';
	time[6]=m/10+'0';
	time[4]=hours%10+'0';
	time[3]=hours/10+'0';
	time[1]=days/10+'0';
	time[0]=days%10+'0';

	lcd12864_write_str(time);
	
	
	if(Fun_UnitChange(pressure_diff) > PD_Upper_Limit){
			start_sequence();
	}
	else if(Fun_UnitChange(pressure_diff) < PD_Lower_Limit){
		stop_sequence();
		
	}
	
	}


}

float Fun_UnitChange(int ADValue){
	float result; 
	if(PD_Unit == UNIT_PA)
		result = (float)ADValue * UNIT_CONV_PA;
	else
		result = (float)ADValue * UNIT_CONV_H2O;
	return result;
	
		
	
}

void Act_pressure_setting1_display(void){
	uint8_t n=0;
	if(PD_Unit == UNIT_MMH2O)
		n=1;
	lcd12864_set_pos(5,2);
	lcd12864_write_float(PD_Upper_Limit,n);
	lcd12864_set_pos(5,3);
	lcd12864_write_float(PD_Lower_Limit,n);
}


void Act_PdUAddone(void){
	float upper_limit;
	if(PD_Unit == UNIT_PA){
		upper_limit = ADC_UPPER_LIMIT*UNIT_CONV_PA;
		if(PD_Upper_Limit+1<=upper_limit)
		PD_Upper_Limit +=1;
	}
	else{
		upper_limit = ADC_UPPER_LIMIT*UNIT_CONV_H2O;
		if(PD_Upper_Limit+0.1<=upper_limit)
		PD_Upper_Limit +=0.1;
	}

}

void Act_PdUDecone(void){
	float lower_limit;
	if(PD_Unit == UNIT_PA){
		lower_limit = PD_Lower_Limit;
		if(PD_Upper_Limit-1>=lower_limit)
		PD_Upper_Limit -=1;
	}
	else{
		lower_limit = PD_Lower_Limit;
		if(PD_Upper_Limit-0.1>=lower_limit)
		PD_Upper_Limit -=0.1;
	}

}

void Act_PdDAddone(void){
	float upper_limit;
	if(PD_Unit == UNIT_PA){
		upper_limit = PD_Upper_Limit;
		if(PD_Lower_Limit+1<=upper_limit)
		PD_Lower_Limit+=1;
	}
	else{
		upper_limit = PD_Upper_Limit;
		if(PD_Lower_Limit+0.1<=upper_limit)
		PD_Lower_Limit +=0.1;
	}
}

void Act_PdDDecone(void){
	float lower_limit;
	if(PD_Unit == UNIT_PA){
		lower_limit = ADC_LOWER_LIMIT*UNIT_CONV_PA;
		if(PD_Lower_Limit-1>=lower_limit)
		PD_Lower_Limit -=1;
	}
	else{
		lower_limit = ADC_LOWER_LIMIT*UNIT_CONV_H2O;
		if(PD_Lower_Limit-0.1>=lower_limit)
		PD_Lower_Limit -=0.1;
	}
}

void Act_PdUAddten(void){
	float upper_limit;
	if(PD_Unit == UNIT_PA){
		upper_limit = ADC_UPPER_LIMIT*UNIT_CONV_PA;
		if(PD_Upper_Limit+10<=upper_limit)
		PD_Upper_Limit +=10;
	}
	else{
		upper_limit = ADC_UPPER_LIMIT*UNIT_CONV_H2O;
		if(PD_Upper_Limit+1<=upper_limit)
		PD_Upper_Limit +=1;
	}
}

void Act_PdUDecten(void){
	float lower_limit;
	if(PD_Unit == UNIT_PA){
		lower_limit = PD_Lower_Limit;
		if(PD_Upper_Limit-10>=lower_limit)
		PD_Upper_Limit -=10;
	}
	else{
		lower_limit = PD_Lower_Limit;
		if(PD_Upper_Limit-1>=lower_limit)
		PD_Upper_Limit -=1;
	}
	
}

void Act_PdDAddten(void){
	float upper_limit;
	if(PD_Unit == UNIT_PA){
		upper_limit = PD_Upper_Limit;
		if(PD_Lower_Limit+10<=upper_limit)
		PD_Lower_Limit+=10;
	}
	else{
		upper_limit = PD_Upper_Limit;
		if(PD_Lower_Limit+1<=upper_limit)
		PD_Lower_Limit +=1;
	}
}

void Act_PdDDecten(void){
	float lower_limit;
	if(PD_Unit == UNIT_PA){
		lower_limit = ADC_LOWER_LIMIT*UNIT_CONV_PA;
		if(PD_Lower_Limit-10>=lower_limit)
		PD_Lower_Limit -=10;
	}
	else{
		lower_limit = ADC_LOWER_LIMIT*UNIT_CONV_H2O;
		if(PD_Lower_Limit-1>=lower_limit)
		PD_Lower_Limit -=1;
	}
}
void Act_PdUAddHud(void){
	float upper_limit;
	if(PD_Unit == UNIT_PA){
		upper_limit = ADC_UPPER_LIMIT*UNIT_CONV_PA;
		if(PD_Upper_Limit+100<=upper_limit)
		PD_Upper_Limit +=100;
	}
	else{
		upper_limit = ADC_UPPER_LIMIT*UNIT_CONV_H2O;
		if(PD_Upper_Limit+10<=upper_limit)
		PD_Upper_Limit +=10;
	}
}
void Act_PdUDecHud(void){
	float lower_limit;
	if(PD_Unit == UNIT_PA){
		lower_limit = PD_Lower_Limit;
		if(PD_Upper_Limit-100>=lower_limit)
		PD_Upper_Limit -=100;
	}
	else{
		lower_limit = PD_Lower_Limit;
		if(PD_Upper_Limit-10>=lower_limit)
		PD_Upper_Limit -=10;
	}
}

void Act_PdDAddHud(void){
	float upper_limit;
	if(PD_Unit == UNIT_PA){
		upper_limit = PD_Upper_Limit;
		if(PD_Lower_Limit+100<=upper_limit)
		PD_Lower_Limit+=100;
	}
	else{
		upper_limit = PD_Upper_Limit;
		if(PD_Lower_Limit+10<=upper_limit)
		PD_Lower_Limit +=10;
	}
	
}
void Act_PdDDecHud(void){
	float lower_limit;
	if(PD_Unit == UNIT_PA){
		lower_limit = ADC_LOWER_LIMIT*UNIT_CONV_PA;
		if(PD_Lower_Limit-100>=lower_limit)
		PD_Lower_Limit -=100;
	}
	else{
		lower_limit = ADC_LOWER_LIMIT*UNIT_CONV_H2O;
		if(PD_Lower_Limit-10>=lower_limit)
		PD_Lower_Limit -=10;
	}
}
void Act_SwitchUnit(void){
	if(PD_Unit == UNIT_PA){
		PD_Unit = UNIT_MMH2O;
		PD_Upper_Limit /= UNIT_CONV_PA;
		PD_Upper_Limit *= UNIT_CONV_H2O;
		PD_Lower_Limit /= UNIT_CONV_PA;
		PD_Lower_Limit *= UNIT_CONV_H2O;
	}
	else{
		PD_Unit = UNIT_PA; 
		PD_Upper_Limit /= UNIT_CONV_H2O;
		PD_Upper_Limit *= UNIT_CONV_PA;
		PD_Lower_Limit /= UNIT_CONV_H2O;
		PD_Lower_Limit *= UNIT_CONV_PA;
		
	}
	
}

void Act_InitSystem(void){
	uint8_t i;

	UpdateLine("系统启动... ",3);
	delay_ms(1000);

	UpdateLine("卸灰阀启动...",3);
	DustValve(IO_ON);
	for(i=Delay_DustvavleToFan;i>0;i--){
	lcd12864_set_pos(7,3);
	lcd12864_write_int(i);
	delay_ms(1000);
	}

	UpdateLine("风机启动STAR ",3);
	Airfan(STAR);
	for(i=Delay_FanStarToDelta;i>0;i--){
	lcd12864_set_pos(7,3);
	lcd12864_write_int(i);
	delay_ms(1000);
	}
	Airfan(DELTA);

	UpdateLine("风机启动DELTA",3);
	delay_ms(2000);

	swtich_monitoring = true;
	State_Update();
	DrawScreen();
		
}

void Act_TerminatSystem(void){
	uint8_t i;
	if(Blowing_State){
	stop_sequence();
	Blowing_State = 0;
	}
	lcd12864_set_pos(0,3);
	UpdateLine("风机停机...",3);
	swtich_monitoring = false;
	Airfan(STOP);
	delay_ms(1000);
	for(i=Delay_FantoDustvavle;i>0;i--){
	lcd12864_set_pos(7,3);
	lcd12864_write_int(i);
	delay_ms(1000);
	}

	UpdateLine("卸灰阀停止！",3);
	DustValve(IO_OFF);
	delay_ms(3000);
	UpdateLine("系统停机",3);	
	switch_start = false;
	
	
}

void UpdateLine(char *str, uint8_t line){
	lcd12864_set_pos(0,line);
	lcd12864_write_str(Display_Strings[0]);
	lcd12864_set_pos(0,line);
	lcd12864_write_str(str);
	
}