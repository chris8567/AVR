/*
 * buttons.h
 *
 * Created: 4/2/2015 3:22:29 PM
 *  Author: 305031727
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_
#ifdef DEV_BOARD
 #define BUTTON1_INTRRUPT INT4
 #define BUTTON2_INTRRUPT INT5
 #define BUTTON3_INTRRUPT INT6
 #define BUTTON4_INTRRUPT INT7

 #define BUTTON_PORT PORTE 
 #define BUTTON_DDR DDRE

 #define BUTTON_SWITCH_IO_IN BUTTON_DDR = _BV(4)|_BV(5)|_BV(6)|_BV(7)
 #define BUTTON_IO_PULLUP BUTTON_PORT |= _BV(4)|_BV(5)|_BV(6)|_BV(7)
#else
 #define BUTTON_INTERRUPT INT1
 #define BUTTON_IO_PORT PORTA
 #define BUTOON_IO_DDR DDRA
 #define BUTTON_IO_PIN PINA
 #define BUTTON_UP_P 0
 #define BUTTON_DOWN_P 1
 #define BUTTON_ADD_P 2
 #define BUTTON_SUB 3
 #define BUTTON_ENTER 4
 #define BUTTON_DEM 5
 #define BUTTON_MENU 6
 #define ALARM_RST 7
 #define BUTTON_SWITCH_IO_IN BUTTON_DDR = 0xff;
 #define BUTTON_IO_PULLUP BUTTON_IO_PORT = 0xff;


#endif



void buttons_init(void);
void button_interrupt(uint8_t num);


#endif /* BUTTONS_H_ */