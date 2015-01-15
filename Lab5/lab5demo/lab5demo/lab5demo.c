// lab3demo.c
/* This function contains options for aggressive behavior, shy behavior, random wandering, subsumption and go to point while avoiding obstacles. This file lab3demo.c is the main file where there are a lot of libraries with
	different functions connected to it for the sake of saving memory space in the microcontroller and organization. Each one of these files will have headers like this explaining what each of them do.*/
// Alexandre van der Ven de Freitas
// Peter Richard Olejnik
// December 18, 2014

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "capi324v221.h"
//#include "Capek_Movements.h"	// Free Running functions for each type of movement.
#include "LightSensor.h"
//#include "Movement_Selector.h"	// Sensor reading logic function.
//#include "Random_Wanderer.h"	// Where both the random wanderer and the random wanderer that is affected by sensor readings are defined.
#include "IRlib.h"				// IR sensor reading functions.
//#include "goToPoint.h"			// Go to point functions.
#include "LightActions.h"

// Main function
void CBOT_main(void)
{
	// local main variables:
	signed char cox = 0;
	signed char coy = 0;
	float rightLight, leftLight;

	// Opening LCD subsystem management.
	LCD_open();

	// This information is printed on the LCD display in case this initial setup takes longer.
	LCD_printf("Setting up...");

	// Subsystem open state variable information.
	SUBSYS_OPENSTAT openTiny;

	// Opening ATTINY subsystem management and storing returning value in openTiny that is associated to the struct SUBSYS_OPENSTAT_TYPE.
	openTiny = ATTINY_open();

	// If the state struct from openTiny is different from the expected value, an error occurs.
	if (openTiny.state != SUBSYS_OPEN){
		LCD_clear();
		// The error is then displayed.
		LCD_printf("Error when opening ATTINY!");
	}

	SPKR_open(SPKR_BEEP_MODE);		// Open the speaker in beep mode
	ADC_open();						// Open the ADC module
	ADC_set_VREF( ADC_VREF_AVCC );	// Set the Voltage Reference first so VREF=5V.
	STEPPER_open();					// Open Stepper module.

	// After the initial setup, a "Ready!" message is displayed on the second line of the LCD display.
	LCD_printf("\nReady!");
	LCD_clear();

	// While loop that keeps the micro controller running begins here:
	while(1){
		// Main menu:
		LCD_printf("SW3: Parts 1 & 2");
		LCD_printf("\nSW4: Crush");
		LCD_printf("\nSW5: NA");
		LCD_clear();

		// Press SW3 to select one of the kids.
		if (ATTINY_get_SW_state(ATTINY_SW3)) {
			while(!ATTINY_get_SW_state(ATTINY_SW5)){
				if(ATTINY_get_SW_state(ATTINY_SW3)){
					cox++;
					if(cox > 5){
						cox = 0;
					}
				}else if(ATTINY_get_SW_state(ATTINY_SW4)){
					cox--;
					if(cox < 0){
						cox = 5;
					}
				}
				switch(cox){
					case 1:
						LCD_clear();
						LCD_printf("Select Mode:");
						LCD_printf("\n1 - Fear");
						break;
					case 2:
						LCD_clear();
						LCD_printf("Select Mode:");
						LCD_printf("\n2 - Aggression");
						break;
					case 3:
						LCD_clear();
						LCD_printf("Select Mode:");
						LCD_printf("\n3 - Love");
						break;
					case 4:
						LCD_clear();
						LCD_printf("Select Mode:");
						LCD_printf("\n4 - Explorer");
						break;
					case 5:
						LCD_clear();
						LCD_printf("Select Mode:");
						LCD_printf("\n5 - Read Sensors");
						break;
					default:
						LCD_clear();
						LCD_printf("Select Mode:");
						LCD_printf("\nMode");
						break;	
				}	
			}
			switch(cox){
				case 1:
					light_fear();
					break;
				case 2:
					light_aggression();
					break;
				case 3:
					light_love();
					break;
				case 4:
					light_explorer();
					break;
				case 5:
					while(1){
						rightLight = getVRightLight();
						leftLight = getVLeftLight();
						LCD_clear();
						LCD_printf("%f\n%f", rightLight, leftLight);
						LCD_printf("\nRefresh: 100ms");
						TMRSRVC_delay(100);
					}
					break;
				default:
					// Nothing
					break;
			}
		}else if(ATTINY_get_SW_state(ATTINY_SW4)){
			light_crush();
		}else if(ATTINY_get_SW_state(ATTINY_SW5)){
			//
		}
		// Keeps running.
	}
}
