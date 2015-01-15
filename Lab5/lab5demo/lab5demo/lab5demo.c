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
    while(1)
    {
		// Main menu:
		LCD_printf("SW3: Kids");
		LCD_printf("\nSW4: Randoms");
		LCD_printf("\nSW5: Go to goal");
		LCD_clear();
		
		// Press SW3 to select one of the kids.
		if (ATTINY_get_SW_state(ATTINY_SW3)){
			
				rightLight = getRightLight();
				leftLight = getLeftLight();
			
				LCD_clear();
				LCD_printf("%f\n%f", rightLight, leftLight);
				TMRSRVC_delay(2000);
				
		}else if(ATTINY_get_SW_state(ATTINY_SW4)){
			//
		}else if(ATTINY_get_SW_state(ATTINY_SW5)){
			//
		}
		// Keeps running.
    }
}


/*// Function for the aggressive kid.
void aggressive(){
	
	float frontIR = 0;
	
	// Obtains the front IR sensor reading
	frontIR = getFrontIR();
	
	//LCD_printf("%f", frontIR);
	//LCD_clear();
	
	// If front IR sensor reads values larger or equal to five, move forward else stop. 
	if(frontIR >= 5){
		STEPPER_move_rn(STEPPER_BOTH,
			STEPPER_FWD, 200, 400,	//Left
			STEPPER_FWD, 200, 400);	//Right
	}else{
		STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
		LCD_clear();
		LCD_printf("RAWR!");
	}
}

// Function for the shy kid.
void shy(){
	char sensLimit = 5;
	char TS;
	float frontIR = 0;
	float backIR = 0;
	float rightIR = 0;
	float leftIR = 0;
	char FSS;
	char BSS;
	char RSS;
	char LSS;
	
	
	// Reads the sensors.
	frontIR = getFrontIR();
	backIR = getBackIR();
	rightIR = getRightIR();
	leftIR = getLeftIR();

	LCD_clear();
	LCD_printf("%f, %f, %f, %f", frontIR, backIR, rightIR, leftIR);

	// Checks which of the sensors are being read
	FSS = (sensLimit > frontIR);
	BSS = (sensLimit > backIR);
	RSS = (sensLimit > rightIR);
	LSS = (sensLimit > leftIR);

	// Makes the sum for switch case in Movement_Selector_Executor()
	TS = FSS + BSS + RSS + LSS;
		
	// Calls the Movement_Selector_Executor
	Movement_Selector_Excecutor(FSS, BSS, RSS, LSS, TS);
}

*/

