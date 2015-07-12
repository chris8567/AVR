#ifndef _RTC_H_
#define _RTC_H_
#include <asf.h>

#define DS1304_PORT PORTC
#define DS1304_DDR DDRC
#define DS1304_PIN PINC
#define RTC_CLK 4
#define RTC_IO 5
#define RTC_CE 6


#define DS1304_SET_IO_OUT DS1302_DDR |= _BV(RTC_CE)|_BV(RTC_IO)|_BV(RTC_CLK); 
#define DS1302_SET_IO_IN DS1302_DDR &= ~(_BV(RTC_CE)|_BV(RTC_CLK)|_BV(RTC_IO));
#define DS1304_CLK_HIGH DS1302_PORT |= _BV(RTC_CLK);
#define DS1304_CLK_LOW DS1302_PORT &= ~(_BV(RTC_CLK)）;
#define DS1304_IO_HIGH DS1302_PORT |= _BV(RTC_IO);
#define DS1304_IO_LOW DS1302_PORT &= ~(_BV(RTC_IO));
#define DS1304_RST_HIGH DS1302_PORT |= _BV(RTC_CE);
#define DS1304_RST_LOW DS1302_PORT &= ~(_BV(RTC_CE));

#define AM 		10
#define PM		11
#define H24		12
#define READ	15
#define WRITE	16

#define mon		1
#define tue		2
#define wed 	3
#define thu		4
#define fri		5
#define sat		6
#define sun		7

#define sec_w 0x80
#define sec_r 0x81
#define min_w 0x82
#define min_r 0x83
#define hour_w 0x84
#define hour_r 0x85
#define date_w 0x86
#define date_r 0x87
#define month_w 0x88
#define month_r 0x89
#define day_w 0x8a
#define day_r 0x8b
#define year_w 0x8c
#define year_r 0x8d 

#define SEC 20
#define MIN 21
#define HOUR 22
#define DAY 23
#define DATE 24
#define MONTH 25
#define YEAR 26

#define w_project 0x8e 

struct rtc_time{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t hour_format;
};


void ds1302_update_time(struct rtc_time *time, uint8_t field);
void ds1302_set_time(struct rtc_time *time, uint8_t field, uint8_t w_byte);
void ds1302_comms(struct rtc_time *time, uint8_t field, uint8_t w_byte, uint8_t rw);
void ds1302_update(struct rtc_time *time);
void ds1302_init(void);
void ds1302_reset(void);
uint8_t ds1302_read_byte(uint8_t w_byte);
void ds1302_write_byte(uint8_t w_byte, uint8_t w_2_byte);
void write(uint8_t w_byte);
uint8_t read(void);





#endif //_RTC_H_
