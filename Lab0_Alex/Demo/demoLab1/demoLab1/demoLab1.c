/*
 * demoLab1.c
 *
 * Created: 12/3/2014 2:11:00 PM
 *  Author: vaddera
 */ 


#include <avr/io.h>
#include "capi324v221.h"

//void square(void);
//void circle(void);
//void eight(void);

void CBOT_main(void)
{
	LCD_open(); // Opening LCD Subsystem management.
	
	SUBSYS_OPENSTAT openTiny; // Here you can add multiple variables as you open subsystems.
	
	openTiny = ATTINY_open();
	
	if (openTiny.state != SUBSYS_OPEN){ // state comes from the struct SUBSYS_OPENSTAT_TYPE
		LCD_printf("Error when opening ATTINY!");
	}
	
    while(1)
    {
        if (ATTINY_get_SW_state(ATTINY_SW3)){
			LCD_printf("Square path.");
			//square();
		}
		else if (ATTINY_get_SW_state(ATTINY_SW4)){
			LCD_printf("Circle path.");
			//circle();
		}
		else if (ATTINY_get_SW_state(ATTINY_SW5)){
			LCD_printf("Eight path.");
			//eight();
		}
    }
}

/*void square(){
	
	
	
}*/