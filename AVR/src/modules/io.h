/*
 * io.h
 *
 * Created: 2015/5/20 23:29:35
 *  Author: 305031727
 */ 


#ifndef IO_H_
#define IO_H_
#include <asf.h>
#define  ON true
#define OFF false

void init_IO(void);
void Alarm(bool state);
void Clean(bool state);




#endif /* IO_H_ */