/*
 * buttons.h
 *
 * Created: 4/2/2015 3:22:29 PM
 *  Author: 305031727
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#define BUTTON1_INTRRUPT INT4
#define BUTTON2_INTRRUPT INT5
#define BUTTON3_INTRRUPT INT6
#define BUTTON4_INTRRUPT INT7

#define BUTTON_PORT PORTE
#define BUTTON_DDR DDRE

#define BUTTON_SWITCH_IO_IN BUTTON_DDR = _BV(4)|_BV(5)|_BV(6)|_BV(7)
#define BUTTON_PULLUP BUTTON_PORT |= _BV(4)|_BV(5)|_BV(6)|_BV(7)

void buttons_init(void);
void button_interrupt(uint8_t num);


#endif /* BUTTONS_H_ */