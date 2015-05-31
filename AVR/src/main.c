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

#include <util/delay.h>





int main (void)
{

	
	
	/* Insert system clock initialization code here (sysclk_init()). */
	buttons_init(); 
	lcd12864_init();
	init_IO();
	Timer0_Init();
	draw_main_page();
	
	
	

	
	while(1){
;

	}
		
	
}


