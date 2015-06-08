#include <asf.h>
#include "modules/rtc.h"

void ds1302_update_time(struct rtc_time *time, uint_8t field){

	ds1302_comms(time, field, 0, READ);

}

void ds1302_set_time(struct rtc_time *time, uint_8t field, uint_8t w_byte){
	
	ds1302_comms(time, field, w_byte, WRITE);

}

void ds1302_comms(struct rtc_time *time, uint_8t field, uint_8t w_byte, uint_8t rw){
	uint_8t temp; 
	if(rw == READ)
	{
		switch(field){
		case SEC:
		
			temp = ds1302_read_byte(sec_r);
			time->second = ((temp&0x0F) + ((temp & 0x70)>>4)*10);
			break;
		
		case MIN:
			temp = ds1302_read_byte(min_r);
			time->minute = ((temp & 0x0F)+((temp & 0x70)>>4)*10);
			break;

		case HOUR:
			temp = ds1302_read_byte(hour_r);
			if(temp & 0x80 == 1)
			{
				if(temp & 0x20 == 1)
					time->hour_format = PM; 
				else
					time->hour_format = AM;
				time->hour = ((temp & 0x0F)+((temp & 0x10)>>4)*10);
			}
			else{
				time->hour_format = H24;
				time->hour = ((temp & 0x0F) + ((temp & 0x30)>>4)*10);
			}
			break;
		
		case DAY:

			temp = ds1302_read_byte(day_r);
			time->day = temp & 0x07;
			break;

		
		case DATE:
			temp = ds1302_read_byte(date_r);
			time->date = ((temp & 0x0F) + ((temp & 0x30 )>>4)*10);
			break;
		case MONTH:
			temp ds1302_read_byte(month_r);
			time->month = ((temp & 0x0F) + ((temp & 0x10)>>4)*10);
			break;
		case YEAR:
			temp = ds1302_read_byte(year_r);
			time->minute = ((temp & 0x0F) + ((temp & 0xF0)>>4)*10);
			break;
		default:
			break;
		}
	}
	else if(rw == WRITE){
		switch(field){
			case SEC:
				ds1302_write_byte(sec_w, (((write_byte/10)<<4) & 0x70 | (write_byte%10));
				break;
			case MIN:
				ds1302_write_byte(min_w, (((write_byte/10)<<4) & 0x70  | (write_byte%10)));
				break;
			case HOUR:
				if(time->hour_format == AM)
				ds1302_write_byte(hour_w, (((write_byte/10)<<4) & 0x10  | (write_byte%10)) | 0x80);			
			else if(time->hour_format == PM)
				ds1302_write_byte(hour_w, (((write_byte/10)<<4) & 0x10  | (write_byte%10)) | 0xA0);
			else if(time->hour_format == H24)
				ds1302_write_byte(hour_w, (((write_byte/10)<<4) & 0x10  | (write_byte%10)));	

				break;
			case DAY:
				ds1302_write_byte(day_w, write_byte & 0x03);

				break;
			case DATE:
				ds1302_write_byte(date_w, (((write_byte/10)<<4) & 0x30  | (write_byte%10)));

				break;
			case MONTH:
				ds1302_write_byte(month_w, (((write_byte/10)<<4) & 0x10 | (write_byte%10)));	

				break;
			case YEAR:
				ds1302_write_byte(year_w, (((write_byte/10)<<4) & 0xF0 | (write_byte%10)));
				break;
			default:
				break;


		}

	}
}