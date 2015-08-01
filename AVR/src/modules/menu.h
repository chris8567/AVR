/*
 * menu.h
 *
 * Created: 2015/5/24 22:55:12
 *  Author: 305031727
 */ 


#ifndef MENU_H_
#define MENU_H_
#include "modules/timer0.h"

#define BLOWING_SYM 0x0F
#define ALARM_SYM 0x21

#define DISPLAY_STR_LENGTH	34
#define STATE_LIST_LENGTH	29
typedef void (*ACTION_CALLBACK_FUNC) (void);


extern char *Display_Strings[DISPLAY_STR_LENGTH];


typedef struct State{
	uint16_t	Current_State;
	uint16_t	Up_Next_State;
	uint16_t	Down_Next_State;
	uint16_t	Left_Next_State;
	uint16_t	Right_Next_State;
	uint16_t	Ent_Next_State;
	
	ACTION_CALLBACK_FUNC Up_Action;
	ACTION_CALLBACK_FUNC Down_Action;
	ACTION_CALLBACK_FUNC Left_Action;
	ACTION_CALLBACK_FUNC Right_Action;
	ACTION_CALLBACK_FUNC Ent_Action;
	TIMER_CALLBACK_FUNC	Timer_Action;
	}Type_State;
	
extern Type_State *SYS_State;

typedef struct ScreenContent{
	char *line[4];
	uint8_t menu;
	uint8_t index;
	uint8_t focus;
	}Type_Screen_Buffer;
	


//define states 
#define MENU_STATE_MAIN				0x0000
#define MENU_STATE_SHOWSTATUS_P1	0x0011
#define MENU_STATE_SHOWSTATUS_P2	0x0012
#define MENU_STATE_SHOWALARMS_P1	0x0021
#define MENU_STATE_SHOWALARMS_P2	0x0022

#define MENU_STATE_ITEMLIST_P1		0x1001
#define	MENU_STATE_ITEMLIST_P2		0x1002
#define	MENU_STATE_ITEMLIST_P3		0x1003
#define	MENU_STATE_ITEMLIST_P4		0x1004
#define	MENU_STATE_ITEMLIST_P5		0x1005

#define MENU_STATE_SYS_P1			0x2001
#define MENU_STATE_SYS_P2			0x2002
#define MENU_STATE_SYS_P3			0x2003
#define MENU_STATE_SYS_P4			0x2004
#define MENU_STATE_SYS_P5			0x2005
#define MENU_STATE_SYS_P6			0x2006

#define MENU_STATE_MODESEL_P1		0x3001
#define MENU_STATE_MODESEL_P2		0x3002
#define MENU_STATE_MODESEL_P3		0x3003
#define MENU_STATE_MODESEL_P4		0x3004
#define MENU_STATE_MODESEL_P5		0x3005

#define MENU_STATE_PD_MODE1_P1		0x3101
#define MENU_STATE_PD_MODE1_P2		0x3102
#define MENU_STATE_PD_MODE1_P3		0x3103
#define MENU_STATE_PD_MODE1_P4		0x3104   //unit
#define	MENU_STATE_PD_M1ADJ_UP1		0x3111
#define MENU_STATE_PD_M1ADJ_UP2		0x3112
#define MENU_STATE_PD_M1ADJ_UP3		0x3113
#define	MENU_STATE_PD_M1ADJ_DN1		0x3114
#define	MENU_STATE_PD_M1ADJ_DN2		0x3115
#define	MENU_STATE_PD_M1ADJ_DN3		0x3116
#define MENU_STATE_PD_MODE2_P1		0x3201
#define MENU_STATE_PD_MODE2_P2		0x3202
#define MENU_STATE_PD_MODE2_P3		0x3203
#define MENU_STATE_PD_M2ADJ_UP		0x3211
#define MENU_STATE_PD_M2ADJ_DN		0x3221
#define MENU_STATE_PD_MODE3_P1		0x3301
#define MENU_STATE_PD_MODE3_P2		0x3302
#define MENU_STATE_PD_MODE3_P3		0x3303
#define MENU_STATE_PD_MDADJ_UP		0x3311
#define MENU_STATE_PD_MDADJ_DN		0x3321






void Menu_Init(void);
void Menu_Poll(void);
void DrawScreen(void);

Type_State *FindState(uint16_t statename);
void State_Update(void); 



#endif /* MENU_H_ */