/*
 * lcd12864.h
 *
 * Created: 3/30/2015 4:07:34 PM
 *  Author: 305031727
 */ 


#ifndef LCD12864_H_
#define LCD12864_H_
#include <asf.h>


#define LCD_PORT PORTG
#define LCD_DDR DDRG
#define LCD_PIN PING
#define LCD_CLK 4
#define LCD_SID 3
#define LCD_EN 2
#define LCD_PSB 1

#define SWITCH_LCD_IO_OUT LCD_DDR |=(_BV(LCD_CLK)|_BV(LCD_SID)|_BV(LCD_EN)|_BV(LCD_PSB))
#define SWITCH_LCD_IO_IN LCD_DDR &= ~_BV(LCD_SID)


#define LCD12864_ENABLE LCD_PORT |= _BV(LCD_EN)
#define LCD12864_DISABLE LCD_PORT &= ~_BV(LCD_EN)

#define LCD12864_CLK_H LCD_PORT |= _BV(LCD_CLK)
#define LCD12864_CLK_L LCD_PORT &= ~_BV(LCD_CLK)

#define LCD12864_SID_1 LCD_PORT |= _BV(LCD_SID)
#define LCD12864_SID_0 LCD_PORT &= ~_BV(LCD_SID)

#define LCD12864_SET_PSB_SERIAL LCD_PORT &=~_BV(LCD_PSB)


void lcd12864_init(void);
void lcd12864_send_data(uint8_t data);
void lcd12864_wait_busy(void);
void lcd12864_send_cmd(uint8_t cmd);
void lcd12864_set_pos(uint8_t x, uint8_t y);
void lcd12864_write_char(char data);
void lcd12864_write_str(char *str);
uint8_t lcd12864_read_data(void);
void lcd12864_clear(void);
void lcd12864_loop(char *str);

#endif /* LCD12864_H_ */