/*
 * io.h
 *
 * Created: 2015/5/20 23:29:35
 *  Author: 305031727
 */ 


#ifndef IO_H_
#define IO_H_
#include <asf.h>
#define  IO_ON true
#define IO_OFF false
#define STOP 0
#define STAR 1
#define DELTA 2

void init_IO(void);
void Alarm(bool state);
void Clean(bool state);
void Airfan(uint8_t mode);
void DustValve(uint8_t sw);
bool START_Read(void);
bool RUNNING_Read(void);
bool PROGDISABLE_Read(void);
bool ALARM_RESET_Read(void);



#endif /* IO_H_ */