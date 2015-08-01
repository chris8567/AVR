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
#include "modules/menu.h"
#include "modules/io.h"
#include "modules/emv.h"
#include "modules/adc.h"

#include <util/delay.h>


#include "modules/actions.h"


int main (void)
{

	/* Insert system clock initialization code here (sysclk_init()). */
	buttons_init(); 
	lcd12864_init();
	init_IO();
	emv_ports_init();
	Timer0_Init();
	ADC_init();
	Menu_Init();
	

	while(1){
	Menu_Poll();

	}
		
	
}


