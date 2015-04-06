/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "modules/lcd12864.h"
#include "modules/buttons.h"
#include "modules/timer0.h"

static void toggle_led(void){
	static bool i=true;
	if(i){
		PORTC |=_BV(1);
		i=false;
	}
	else{
		PORTC &=~_BV(1);
		i=true;
	}

	
}


int main (void)
{
	
	/* Insert system clock initialization code here (sysclk_init()). */
	DDRC = 0xff;
	PORTC = 0xff;
	board_init();

	lcd12864_init();
	buttons_init();
	
	lcd12864_set_pos(1,1);
	lcd12864_write_str("Hello, World!");
	Timer0_Init();
	
	if(!Timer0_RegisterCallbackFunction(toggle_led))
	lcd12864_loop("error");
	
	while(1){
		;

	}
		
	
}


