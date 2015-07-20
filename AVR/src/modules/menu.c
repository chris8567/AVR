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
#include "modules/actions.h"
#include "modules/buttons.h"

Type_State *SYS_State=NULL;
Type_Screen_Buffer SYS_Screen_Buffer;
TIMER_CALLBACK_FUNC Current_TimerFunc = NULL;
uint8_t PD_Mode = 1;
uint8_t Alarm_State = 0;
uint8_t Blowing_State = 0;
uint16_t BlowPresureUpperLimit=800;
uint16_t BlowPresureLowerLimit=600;

char *Display_Strings[DISPLAY_STR_LENGTH] = {\
	"            ",\
	"��ǰѹ��:",\
	"ʱ��:",\
	"״̬  �˵�  ����",\
	"����",\
	"> ϵͳ״̬",\
	"> ����ģʽ",\
	"> �紵����",\
	"> ��������",\
	"> �˳��˵�",\
	"> ϵͳ����ʱ��",\
	"> �紵����",\
	"> ���ڱ���",\
	"> ��������",\
	"> ��λ����",\
	"> ��չ��",\
	"> ѹ��ģʽһ",\
	"> ѹ��ģʽ��",\
	"> ѹ��ģʽ��",\
	"> ʱ�����ģʽ",\
	"> ����紵ģʽ",\
	"> ��������",\
	"> �ر���",\
	"> ѹ������",\
	"> ѹ������",\
	"> ѹ�����ްٷֱ�",\
	"> ��С�紵Ƶ��",\
	"> �紵ʱ����",\
	"����  ȷ��  ����"\
};


Type_State State_List[STATE_LIST_LENGTH]={\
	{MENU_STATE_MAIN,			MENU_STATE_MAIN,		MENU_STATE_MAIN,				MENU_STATE_MAIN,			MENU_STATE_MAIN,			MENU_STATE_ITEMLIST_P1,		NULL,			NULL,			NULL,			NULL,			NULL,			Act_Update_Main},\
	{MENU_STATE_ITEMLIST_P1,	MENU_STATE_ITEMLIST_P1,	MENU_STATE_ITEMLIST_P2,			MENU_STATE_MAIN,			MENU_STATE_ITEMLIST_P1,		MENU_STATE_SYS_P1,			NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_ITEMLIST_P2,	MENU_STATE_ITEMLIST_P1,	MENU_STATE_ITEMLIST_P3,			MENU_STATE_MAIN,			MENU_STATE_ITEMLIST_P2,		MENU_STATE_MODESEL_P1,		NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_ITEMLIST_P3,	MENU_STATE_ITEMLIST_P2,	MENU_STATE_ITEMLIST_P4,			MENU_STATE_MAIN,			MENU_STATE_ITEMLIST_P3,		MENU_STATE_ITEMLIST_P3,		NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_ITEMLIST_P4,	MENU_STATE_ITEMLIST_P3,	MENU_STATE_ITEMLIST_P5,			MENU_STATE_MAIN,			MENU_STATE_ITEMLIST_P4,		MENU_STATE_ITEMLIST_P4,		NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_ITEMLIST_P5,	MENU_STATE_ITEMLIST_P4,	MENU_STATE_ITEMLIST_P5,			MENU_STATE_MAIN,			MENU_STATE_ITEMLIST_P5,		MENU_STATE_MAIN,			NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_SYS_P1,			MENU_STATE_SYS_P1,		MENU_STATE_SYS_P2,				MENU_STATE_ITEMLIST_P1,		MENU_STATE_SYS_P1,			MENU_STATE_SYS_P1,			NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_SYS_P2,			MENU_STATE_SYS_P1,		MENU_STATE_SYS_P3,				MENU_STATE_ITEMLIST_P1,		MENU_STATE_SYS_P2,			MENU_STATE_SYS_P2,			NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_SYS_P3,			MENU_STATE_SYS_P2,		MENU_STATE_SYS_P4,				MENU_STATE_ITEMLIST_P1,		MENU_STATE_SYS_P3,			MENU_STATE_SYS_P3,			NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_SYS_P4,			MENU_STATE_SYS_P3,		MENU_STATE_SYS_P5,				MENU_STATE_ITEMLIST_P1,		MENU_STATE_SYS_P4,			MENU_STATE_SYS_P4,			NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_SYS_P5,			MENU_STATE_SYS_P4,		MENU_STATE_SYS_P5,				MENU_STATE_ITEMLIST_P1,		MENU_STATE_SYS_P5,			MENU_STATE_SYS_P5,			NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_MODESEL_P1,		MENU_STATE_MODESEL_P1,	MENU_STATE_MODESEL_P2,			MENU_STATE_ITEMLIST_P2,		MENU_STATE_MODESEL_P1,		MENU_STATE_PD_MODE1_P1,		NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_MODESEL_P2,		MENU_STATE_MODESEL_P1,	MENU_STATE_MODESEL_P3,			MENU_STATE_ITEMLIST_P2,		MENU_STATE_MODESEL_P2,		MENU_STATE_PD_MODE2_P1,		NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_MODESEL_P3,		MENU_STATE_MODESEL_P2,	MENU_STATE_MODESEL_P4,			MENU_STATE_ITEMLIST_P2,		MENU_STATE_MODESEL_P3,		MENU_STATE_PD_MODE3_P1,		NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_MODESEL_P4,		MENU_STATE_MODESEL_P3,	MENU_STATE_MODESEL_P4,			MENU_STATE_ITEMLIST_P2,		MENU_STATE_MODESEL_P4,		MENU_STATE_MODESEL_P4,		NULL,			NULL,			NULL,			NULL,			NULL,			NULL	},\
	{MENU_STATE_PD_MODE1_P1,	MENU_STATE_PD_MODE1_P1,	MENU_STATE_PD_MODE1_P2,			MENU_STATE_MODESEL_P1,		MENU_STATE_PD_MODE1_P1,		MENU_STATE_PD_MODE1_P1,		NULL,			NULL,			NULL,			NULL,			NULL,			Act_pressure_setting1_display    },\
	{MENU_STATE_PD_MODE1_P2,	MENU_STATE_PD_MODE1_P1,	MENU_STATE_PD_MODE1_P3,			MENU_STATE_MODESEL_P1,		MENU_STATE_PD_MODE1_P2,		MENU_STATE_PD_MODE1_P2,		NULL,			NULL,			NULL,			NULL,			NULL,			Act_pressure_setting1_display    },\
	{MENU_STATE_PD_MODE1_P3,	MENU_STATE_PD_MODE1_P2,	MENU_STATE_PD_MODE1_P3,			MENU_STATE_MODESEL_P1,		MENU_STATE_PD_MODE1_P3,		MENU_STATE_PD_MODE1_P3,		NULL,			NULL,			NULL,			NULL,			NULL,			Act_pressure_setting1_display    }\
	
	};
//	CurrentState				UP_NEXT					DOWN_NEXT						LEFT_NEXT					RIGHT_NEXT					ENT_NEXT					UP_ACTION		DOWN_ACTION			LEFT_ACTION		RIGHT_ACTION		ENT_ACTION		TIMER_ACTI
	  

uint8_t Get_Workmode(void){
	return PD_Mode;
}

	void DrawScreen(void){
		lcd12864_clear();
		lcd12864_set_pos(0,1);
		lcd12864_write_str(SYS_Screen_Buffer.line[0]);
		lcd12864_set_pos(0,2);
		lcd12864_write_str(SYS_Screen_Buffer.line[1]);
		lcd12864_set_pos(0,3);
		lcd12864_write_str(SYS_Screen_Buffer.line[2]);
		lcd12864_set_pos(0,4);
		lcd12864_write_str(SYS_Screen_Buffer.line[3]);
		switch(SYS_Screen_Buffer.white_index){
			case 1:
				lcd12864_set_pos(0,1); 
				lcd12864_write_char('*');
				break;
			case 2:
				lcd12864_set_pos(0,2);
				lcd12864_write_char('*');
				break;
			case 3:
				lcd12864_set_pos(0,3);
				lcd12864_write_char('*');
				break;
			default:
				break;	
		}
		lcd12864_send_cmd(0x36);
		lcd12864_send_cmd(0x30);
		
	}
	
Type_State *FindState(uint16_t statename){
		for(uint8_t i=0; i<STATE_LIST_LENGTH;i++){
			if(State_List[i].Current_State == statename)
			return &State_List[i];
		}
		return NULL;
		
	}
	
	void Menu_Init(void){
		SYS_State = FindState(MENU_STATE_MAIN);
	
		Current_TimerFunc = SYS_State->Timer_Action;
		Current_TimerFunc();
		Timer0_RegisterCallbackFunction(SYS_State->Timer_Action,1000);
		State_Update();
		DrawScreen();
		lcd12864_SetWhite(0,4,4,0);
		lcd12864_SetWhite(6,4,4,0);
		lcd12864_SetWhite(12,4,4,0);
	}
	
	void State_Update(void){
		switch(SYS_State->Current_State){
			case MENU_STATE_MAIN:
				SYS_Screen_Buffer.line[0] = Display_Strings[0];
				SYS_Screen_Buffer.line[1] = Display_Strings[1];
				SYS_Screen_Buffer.line[2] = Display_Strings[2];
				SYS_Screen_Buffer.line[3] = Display_Strings[3];
				SYS_Screen_Buffer.white_index = 0;
				break;
			case MENU_STATE_ITEMLIST_P1:
				SYS_Screen_Buffer.line[0] = Display_Strings[5]; 
				SYS_Screen_Buffer.line[1] = Display_Strings[6];
				SYS_Screen_Buffer.line[2] = Display_Strings[7];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 1;
				break;
			case MENU_STATE_ITEMLIST_P2:
				SYS_Screen_Buffer.line[0] = Display_Strings[5];
				SYS_Screen_Buffer.line[1] = Display_Strings[6];
				SYS_Screen_Buffer.line[2] = Display_Strings[7];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 2;
				break;
			case MENU_STATE_ITEMLIST_P3:
				SYS_Screen_Buffer.line[0] = Display_Strings[5];
				SYS_Screen_Buffer.line[1] = Display_Strings[6];
				SYS_Screen_Buffer.line[2] = Display_Strings[7];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 3;
				break;
			case MENU_STATE_ITEMLIST_P4:
				SYS_Screen_Buffer.line[0] = Display_Strings[8];
				SYS_Screen_Buffer.line[1] = Display_Strings[9];
				SYS_Screen_Buffer.line[2] = Display_Strings[0];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 1;
				break;
			case MENU_STATE_ITEMLIST_P5:
				SYS_Screen_Buffer.line[0] = Display_Strings[8];
				SYS_Screen_Buffer.line[1] = Display_Strings[9];
				SYS_Screen_Buffer.line[2] = Display_Strings[0];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 2;
				break;
			case MENU_STATE_SYS_P1:
				SYS_Screen_Buffer.line[0] = Display_Strings[10];
				SYS_Screen_Buffer.line[1] = Display_Strings[11];
				SYS_Screen_Buffer.line[2] = Display_Strings[12];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 1;
				break;
			case MENU_STATE_SYS_P2:
				SYS_Screen_Buffer.line[0] = Display_Strings[10];
				SYS_Screen_Buffer.line[1] = Display_Strings[11];
				SYS_Screen_Buffer.line[2] = Display_Strings[12];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 2;
				break;
			case MENU_STATE_SYS_P3:
				SYS_Screen_Buffer.line[0] = Display_Strings[10];
				SYS_Screen_Buffer.line[1] = Display_Strings[11];
				SYS_Screen_Buffer.line[2] = Display_Strings[12];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 3;
				break;
			case MENU_STATE_SYS_P4:
				SYS_Screen_Buffer.line[0] = Display_Strings[13];
				SYS_Screen_Buffer.line[1] = Display_Strings[14];
				SYS_Screen_Buffer.line[2] = Display_Strings[15];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 1;
				break;
			case MENU_STATE_SYS_P5:
				SYS_Screen_Buffer.line[0] = Display_Strings[13];
				SYS_Screen_Buffer.line[1] = Display_Strings[14];
				SYS_Screen_Buffer.line[2] = Display_Strings[15];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 2;
				break;
			case MENU_STATE_SYS_P6:
				SYS_Screen_Buffer.line[0] = Display_Strings[13];
				SYS_Screen_Buffer.line[1] = Display_Strings[14];
				SYS_Screen_Buffer.line[2] = Display_Strings[15];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 3;
				break;
			case MENU_STATE_MODESEL_P1:
				SYS_Screen_Buffer.line[0] = Display_Strings[16];
				SYS_Screen_Buffer.line[1] = Display_Strings[17];
				SYS_Screen_Buffer.line[2] = Display_Strings[18];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 1; 
				break;
			case MENU_STATE_MODESEL_P2:
				SYS_Screen_Buffer.line[0] = Display_Strings[16];
				SYS_Screen_Buffer.line[1] = Display_Strings[17];
				SYS_Screen_Buffer.line[2] = Display_Strings[18];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 2;
				break;
			case MENU_STATE_MODESEL_P3:
				SYS_Screen_Buffer.line[0] = Display_Strings[16];
				SYS_Screen_Buffer.line[1] = Display_Strings[17];
				SYS_Screen_Buffer.line[2] = Display_Strings[18];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 3;
				break;
			case MENU_STATE_MODESEL_P4:
				SYS_Screen_Buffer.line[0] = Display_Strings[19];
				SYS_Screen_Buffer.line[1] = Display_Strings[20];
				SYS_Screen_Buffer.line[2] = Display_Strings[0];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 1;
				break;
			case MENU_STATE_MODESEL_P5:
				SYS_Screen_Buffer.line[0] = Display_Strings[19];
				SYS_Screen_Buffer.line[1] = Display_Strings[20];
				SYS_Screen_Buffer.line[2] = Display_Strings[0];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index = 2;
				break;
			case MENU_STATE_PD_MODE1_P1:
				if(PD_Mode == 1) 
					SYS_Screen_Buffer.line[0] = Display_Strings[21];
				else
					SYS_Screen_Buffer.line[0] = Display_Strings[22];
				SYS_Screen_Buffer.line[1] = Display_Strings[23];
				SYS_Screen_Buffer.line[2] = Display_Strings[24];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index=1;
				break;
			case MENU_STATE_PD_MODE1_P2:
				if(PD_Mode == 1)
				SYS_Screen_Buffer.line[0] = Display_Strings[21];
				else
				SYS_Screen_Buffer.line[0] = Display_Strings[22];
				SYS_Screen_Buffer.line[1] = Display_Strings[23];
				SYS_Screen_Buffer.line[2] = Display_Strings[24];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index=2;
				break;
			case MENU_STATE_PD_MODE1_P3:
				if(PD_Mode == 1)
				SYS_Screen_Buffer.line[0] = Display_Strings[21];
				else
				SYS_Screen_Buffer.line[0] = Display_Strings[22];
				SYS_Screen_Buffer.line[1] = Display_Strings[23];
				SYS_Screen_Buffer.line[2] = Display_Strings[24];
				SYS_Screen_Buffer.line[3] = Display_Strings[28];
				SYS_Screen_Buffer.white_index=3;
				break;
			default:
				break;
			
		}
			
	}
	
	void Menu_Poll(void){
		uint8_t key = getkey();
		switch(key){
			case BUTTON_RIGHT:
				if(SYS_State->Right_Action!=NULL)
					SYS_State->Right_Action();
				SYS_State = FindState(SYS_State->Right_Next_State);
				State_Update();
				DrawScreen();
				break;
			case BUTTON_LEFT:
				if(SYS_State->Left_Action!= NULL)
					SYS_State->Left_Action();
				SYS_State = FindState(SYS_State->Left_Next_State);
				State_Update();
				DrawScreen();
				break;
			case BUTTON_UP:
				if(SYS_State->Up_Action!= NULL)
				SYS_State->Up_Action();
				SYS_State = FindState(SYS_State->Up_Next_State);
				State_Update();
				DrawScreen();
				break;
			case BUTTON_DOWN:
				if(SYS_State->Down_Action!= NULL)
				SYS_State->Down_Action();
				SYS_State = FindState(SYS_State->Down_Next_State);
				State_Update();
				DrawScreen();
				break;
			case BUTTON_ENTER:
				if(SYS_State->Ent_Action!= NULL)
				SYS_State->Ent_Action();
				SYS_State = FindState(SYS_State->Ent_Next_State);
				State_Update();
				DrawScreen();
				break;
			default:

				break;
		}
	if(key != KEY_NULL){
			Timer0_RemoveCallbackFunction(Current_TimerFunc);
			Current_TimerFunc = SYS_State->Timer_Action;
			if(Current_TimerFunc != NULL){
			Current_TimerFunc();
			Timer0_RegisterCallbackFunction(Current_TimerFunc,1000);}
			
		
	}
	
	}