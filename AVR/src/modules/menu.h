/*
 * menu.h
 *
 * Created: 2015/5/24 22:55:12
 *  Author: 305031727
 */ 


#ifndef MENU_H_
#define MENU_H_

#define BLOWING_SYM 0x0F
#define ALARM_SYM 0x21

#define DISPLAY_STR_LENGTH	28
#define STATE_LIST_LENGTH	2

extern uint16_t Current_State; 
extern char *Display_Strings[DISPLAY_STR_LENGTH];

typedef struct StateList{
	uint16_t	Current_State;
	uint16_t	Up_Next_State;
	uint16_t	Down_Next_State;
	uint16_t	Left_Next_State;
	uint16_t	Right_Next_State;
	uint16_t	Ent_Next_State;
	void		(*Up_Action)(void);
	void		(*Down_Action)(void);
	void		(*Left_Action)(void);
	void		(*Right_Action)(void);
	void		(*Timer_Action)(void);
	void		(*Ent_Action)(void);
	}Type_StateList;

typedef struct ScreenContent{
	char *lines[3];
	uint8_t white_index;
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

#define MENU_STATE_MODESEL_P1		0x3001
#define MENU_STATE_MODESEL_P2		0x3002
#define MENU_STATE_MODESEL_P3		0x3003
#define MENU_STATE_MODESEL_P4		0x3004
#define MENU_STATE_PD_MODE1_P1		0x3101
#define MENU_STATE_PD_MODE1_P2		0x3102
#define MENU_STATE_PD_MODE1_P3		0x3103
#define	MENU_STATE_PD_M1ADJ_UP		0x3112
#define	MENU_STATE_PD_M1ADJ_DN		0x3113
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








void draw_main_page(void);
void refresh_page(void);
#endif /* MENU_H_ */