/*
 * adc.h
 *
 * Created: 2015/5/24 16:13:26
 *  Author: 305031727
 */ 


#ifndef ADC_H_
#define ADC_H_
#define PRESSURE 1
#define EMV 2
#define VIN 3
#define VPP 4
#define VCC 5

#define ADC_CHANN 6
#define SCALE 1000
void ADC_init(void);
uint16_t ADC_read(uint8_t target);
uint16_t ADC_readonce(void);



#endif /* ADC_H_ */