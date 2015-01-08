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
#include "Capek_Movements.h"	// Free Running functions for each type of movement.
//#include "Movement_Selector.h"	// Sensor reading logic function.
#include "Random_Wanderer.h"	// Where both the random wanderer and the random wanderer that is affected by sensor readings are defined.
#include "IRlib.h"				// IR sensor reading functions.
#include "goToPoint.h"			// Go to point functions.
//#include "wallFollow.h"
#include "wallFollow2.h"

// Used function prototypes.
//void aggressive();
//void shy();

// Main function
void CBOT_main(void)
{
	// local main variables:
	signed char cox = 0;
	signed char coy = 0;
	
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
		LCD_printf("SW3: Right Follow\n");
		LCD_printf("\nSW4: Left Follow\n");
		LCD_printf("\nSW5: ");
		LCD_clear();
		
		// Press SW3 to select one of the kids.
		if (ATTINY_get_SW_state(ATTINY_SW3)){
			rightFollow();
			//wallFinder();
			/*while(!ATTINY_get_SW_state(ATTINY_SW5)){ // SW5 returns to main menu
				LCD_clear();
				LCD_printf("SW3: Aggressive");
				LCD_printf("\nSW4: Shy");
				LCD_printf("\nSW5: Back");
				if(ATTINY_get_SW_state(ATTINY_SW3)){
					while(1){
						// Selects the aggressive kid
						aggressive();
					}
				}else if(ATTINY_get_SW_state(ATTINY_SW4)){
					while(1){
						// Selects the shy kid
						shy();
					}
				}
			}*/
		}else if(ATTINY_get_SW_state(ATTINY_SW4)){
			leftFollow();

			/*
			LCD_clear();
			LCD_printf("SW3: Random.");
			LCD_printf("\nSW4: Subsumption.");
			LCD_printf("\nSW5: Back");
			while(!ATTINY_get_SW_state(ATTINY_SW5)){ // SW5 returns to main menu
				if(ATTINY_get_SW_state(ATTINY_SW3)){
					while(1){
						// Selects the random wanderer
						Random_Wanderer();
					}
				}else if(ATTINY_get_SW_state(ATTINY_SW4)){
					while(1){
						// Selects Subsumption
						Shy_Random_Wanderer();
					}
				}
			}
		*/}/*else if(ATTINY_get_SW_state(ATTINY_SW5)){
			// While SW5 is not pressed...
			while(!ATTINY_get_SW_state(ATTINY_SW5)){
				LCD_clear();
				LCD_printf("( %d , %d )", cox, coy); // Displays the angle selection.
				LCD_printf("\nSW3 + | SW4 - \nSW5 To y");
				// If SW3 is pressed, the coordinate x is incremented.
				if(ATTINY_get_SW_state(ATTINY_SW3)){
					cox++;
					// If the x value is > 5, it goes back to -5.
					if (cox > 5){
						cox = -5;
					}
					// If SW4 is pressed, the coordinate x is decremented.
					}else if(ATTINY_get_SW_state(ATTINY_SW4)){
					cox--;
					// If the x value is < -5, it goes back to 5.
					if(cox < -5){
						cox = 5;
					}
				}
			}
			// After choosing the value of the coordinate x, the user must choose the value of the coordinate y:
			// While SW5 is not pressed...
			while(!ATTINY_get_SW_state(ATTINY_SW5)){
				LCD_clear();
				LCD_printf("( %d , %d )", cox, coy);
				LCD_printf("\nSW3 + | SW4 - \nSW5 Enter");
				// If SW3 is pressed, the coordinate y is incremented.
				if(ATTINY_get_SW_state(ATTINY_SW3)){
					coy++;
					// If the x value is > 5, it goes back to -5.
					if (coy > 5){
						coy = -5;
					}
					// If SW4 is pressed, the coordinate y is decremented.
					}else if(ATTINY_get_SW_state(ATTINY_SW4)){
						coy--;
					// If the x value is < -5, it goes back to 5
					if(coy < -5){
						coy = 5;
					}
				}
			}
			// Calls go to goal point function.
			go2Point(cox,coy);
			// Clears the variables up.
			cox = 0;
			coy = 0;
			LCD_clear();
		}*/
		// Keeps running.
    }
}


// Function for the aggressive kid.
/*void aggressive(){
	
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
}*/

// Function for the shy kid.
/*void shy(){
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
}*/
