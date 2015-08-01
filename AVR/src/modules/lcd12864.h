/*
 * lcd12864.h
 *
 * Created: 3/30/2015 4:07:34 PM
 *  Author: 305031727
 */ 


#ifndef LCD12864_H_
#define LCD12864_H_
#include <asf.h>


 #define LCD_PORT PORTE
 #define LCD_DDR DDRE
 #define LCD_PIN PINE
 #define LCD_CLK 3
 #define LCD_SID 4
 #define LCD_EN 6
 #define LCD_RST 5
 #define LCD_BTL_EN 7
 #define LCD12864_RESET_0 LCD_PORT &= ~_BV(LCD_RST)
 #define LCD12864_RESET LCD_PORT |= _BV(LCD_RST)
 #define LCD12864_BACKLIGHT_ENABLE LCD_PORT &= ~_BV(LCD_BTL_EN)
 

 #define SWITCH_LCD_IO_OUT LCD_DDR |=(_BV(LCD_CLK)|_BV(LCD_SID)|_BV(LCD_EN)|_BV(LCD_RST)|_BV(LCD_BTL_EN))

#define SWITCH_LCD_IO_IN LCD_DDR &= ~_BV(LCD_SID)


#define LCD12864_ENABLE LCD_PORT |= _BV(LCD_EN)
#define LCD12864_DISABLE LCD_PORT &= ~_BV(LCD_EN)

#define LCD12864_CLK_H LCD_PORT |= _BV(LCD_CLK)
#define LCD12864_CLK_L LCD_PORT &= ~_BV(LCD_CLK)

#define LCD12864_SID_1 LCD_PORT |= _BV(LCD_SID)
#define LCD12864_SID_0 LCD_PORT &= ~_BV(LCD_SID)




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
void lcd12864_write_float(float v);
void lcd12864_write_int(int v);
void lcd12864_SetWhite(uint8_t x, uint8_t y, uint8_t width, uint8_t clear);
void lcd12864_send_byte(uint8_t data);
void lcd12864_clrGDRAM(void);
void lcd12864_Focus(uint8_t menu, uint8_t index, uint8_t white);
#endif
 /* LCD12864_H_ */