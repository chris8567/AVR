/*
 * buttons.h
 *
 * Created: 4/2/2015 3:22:29 PM
 *  Author: 305031727
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

 #define BUTTON_INTERRUPT INT1
 #define BUTTON_IO_PORT PORTA
 #define BUTTON_IO_DDR DDRA
 #define BUTTON_IO_PIN PINA
 #define KEY_NULL 255
 #define BUTTON_UP 0
 #define BUTTON_DOWN 1
 #define BUTTON_RIGHT 2
 #define BUTTON_LEFT 3
 #define BUTTON_ENTER 4
 #define BUTTON_DEM 5
 #define BUTTON_MENU 6
 #define BUTTON_ALMRST 7
 #define BUTTON_SWITCH_IO_IN BUTTON_IO_DDR = 0x00;
 #define BUTTON_IO_PULLUP BUTTON_IO_PORT = 0xff;





void buttons_init(void);
void button_interrupt(void);
uint8_t getkey(void);


#endif /* BUTTONS_H_ */