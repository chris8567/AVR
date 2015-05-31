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


#define  STR_PRESSURE_DIFF		 "压差:"
#define STR_MENU_FOOTER1		 "状态  菜单  报警"
#define STR_MENU_FOOTER2		 "返回  确定  帮助"
#define  STR_TIME				 "运行时间:"


void draw_main_page(void);
void refresh_page(void);
#endif /* MENU_H_ */