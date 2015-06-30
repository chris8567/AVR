/*
 * emv.h
 *
 * Created: 2015/6/1 19:38:18
 *  Author: 305031727
 */ 


#ifndef EMV_H_
#define EMV_H_
#include <asf.h>
/*
DRV_DATA :	PB5 
DRV_OEn:	PB6
DRV_RCK:	PB7
DRV_SCK:	PG3
DRV_SCLR:	PG4
*/
#define DATA_HIGH PORTB|=_BV(5)
#define DATA_LOW PORTB &=~_BV(5)
#define OEn_HIGH PORTB |= _BV(6)
#define OEn_LOW PORTB &=~_BV(6)
#define RCK_HIGH PORTB |= _BV(7)
#define RCK_LOW PORTB &=~_BV(7)
#define SCK_HIGH PORTG|=_BV(3)
#define SCK_LOW PORTG &=~_BV(3)
#define MR_HIGH PORTG |=_BV(4)
#define MR_LOW PORTG &=~_BV(4)


void emv_ports_init(void);
void set_emv_channel(uint8_t channel);
void unset_emv_channel(uint8_t channel);
void set_emv_ctrl_word(uint16_t emv_word);
uint8_t start_sequence(void);
void emv_refresh(void);
void set_blower_interval(uint8_t intv_s);
void set_blower_on_time(uint8_t time_ms);

void blow_seq(void);



#endif /* EMV_H_ */