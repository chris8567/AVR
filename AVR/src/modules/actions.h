/*
 * actions.h
 *
 * Created: 2015/6/29 20:56:37
 *  Author: 305031727
 */ 


#ifndef ACTIONS_H_
#define ACTIONS_H_
#include <asf.h>

#define ADC_UPPER_LIMIT 920
#define ADC_LOWER_LIMIT 50
#define UNIT_CONV_PA 3.696
#define UNIT_CONV_H2O 0.37696
#define DEFAULT_PD_UPPER 1200.0
#define DEFAULT_PD_LOWER 500.0
#define DEFAULT_BLOWER_COUNTER_LIMIT 1000000
#define ON 1
#define OFF 0

#define UNIT_MMH2O 0x01
#define UNIT_PA	   0x02

extern uint8_t PD_Mode;
extern uint8_t PD_Unit;
extern bool switch_start;
extern bool swtich_monitoring; 
extern bool Blowing_State;

void Act_Update_Main(void);
void Act_pressure_setting1_display(void);
void Act_PdUAddone(void);
void Act_PdUDecone(void);
void Act_PdDAddone(void);
void Act_PdDDecone(void);
void Act_PdUAddten(void);
void Act_PdDAddten(void);
void Act_PdUDecten(void);
void Act_PdDDecten(void);
void Act_PdUAddHud(void);
void Act_PdDAddHud(void);
void Act_PdUDecHud(void);
void Act_PdDDecHud(void);
void Act_SwitchUnit(void);
void Act_DispUnit(void);

void Act_InitSystem(void);
void Act_TerminatSystem(void);


float Fun_UnitChange(int ADValue);
void UpdateLine(char *str, uint8_t line);



#endif /* ACTIONS_H_ */