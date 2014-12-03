/*
 * HelloDolly.c
 *
 * Created: 12/1/2014 12:36:16 AM
 *  Author: vaddera
 */ 


#include <avr/io.h>

#include "capi324v221.h"
void CBOT_main(void)
{
	LCD_open(); //allows use of the LCD
	LCD_printf("Hello, Dolly!"); //print to the LCD screen
	// Create a delay function. 5 seconds.
	STEPPER_open(); // Open STEPPER module for use. (1)

	// Move BOTH wheels forward.
	STEPPER_move_stwt( STEPPER_BOTH,
	STEPPER_FWD, 1000, 200, 400, STEPPER_BRK_OFF, // Left
	STEPPER_FWD, 1000, 200, 400, STEPPER_BRK_OFF ); // Right

	// Then TURN RIGHT (~90-degrees)...
	STEPPER_move_stwt( STEPPER_BOTH,
	STEPPER_FWD, 150, 200, 400, STEPPER_BRK_OFF, // Left
	STEPPER_REV, 150, 200, 400, STEPPER_BRK_OFF ); // Right

	// Move BOTH wheels forward.
	STEPPER_move_stwt( STEPPER_BOTH,
	STEPPER_FWD, 1000, 200, 400, STEPPER_BRK_OFF, // Left
	STEPPER_FWD, 1000, 200, 400, STEPPER_BRK_OFF ); // Right

	// Infinite loop!
	while(1)
	{
		//do nothing!!!
	}
}