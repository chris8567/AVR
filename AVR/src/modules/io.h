/*
 * io.h
 *
 * Created: 2015/5/20 23:29:35
 *  Author: 305031727
 */ 


#ifndef IO_H_
#define IO_H_
#include <asf.h>
#define  ON 1
#define OFF 0

void init_IO(void);
void Alarm(uint8_t state);
void Clean(uint8_t state);



#endif /* IO_H_ */