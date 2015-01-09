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
void CBOT_main(void) {
	// local main variables:
	signed char cox = 0;
	signed char coy = 0;
	char ICT = 10;
	char IsWall = 0;
	float frontIR, rightIR, leftIR;

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

	STEPPER_set_mode(STEPPER_BOTH, STEPPER_NORMAL_MODE);

	// While loop that keeps the micro controller running begins here:
	while(1)
	{
		// Main menu:
		LCD_clear();
		LCD_printf("SW3: Wall Follow\n");
		LCD_printf("SW4: AvoidFollow\n");
		LCD_printf("SW5: Target Follow\n");

		// Press SW3 to select one of the kids.
		if (ATTINY_get_SW_state(ATTINY_SW3)){
			while(1){
				frontIR = getFrontIR();
				rightIR = getRightIR();
				leftIR = getLeftIR();
				if ((leftIR < ICT) && (rightIR < ICT)) {
					centerFollow();
				} else if (rightIR < ICT){
					rightFollow();
				} else if (leftIR < ICT) {
					leftFollow();
				} else if (frontIR < ICT) {
					LCD_clear();
					LCD_printf("Forward,");
					LCD_printf("\nthen Follow");

					STEPPER_move_rn(STEPPER_BOTH,
							STEPPER_FWD, 150, 400,	//Left
							STEPPER_FWD, 150, 400);	//Right
					TMRSRVC_delay(500);
					rightIR = getRightIR();
					leftIR = getLeftIR();
					if (leftIR > rightIR){
						//turn right
						go2ContAngle(-90, 100);
						leftFollow();
					}else {
						//turn left
						go2ContAngle(90, 100);
						rightFollow();
					}
				} else {
					LCD_clear();
					LCD_printf("Random\n");
					LCD_printf("Wanderer\n");

					Random_Wanderer();
				}
			}
		}else if(ATTINY_get_SW_state(ATTINY_SW4)){
			while(1){
				frontIR = getFrontIR();
				rightIR = getRightIR();
				leftIR = getLeftIR();
				if ((leftIR < ICT) && (rightIR < ICT)) {
					centerFollow();
				} else if (rightIR < ICT){
					rightFollow();
				} else if (leftIR < ICT) {
					leftFollow();
				} else if (frontIR < ICT) {
					STEPPER_move_rn(STEPPER_BOTH,
						STEPPER_FWD, 0, 400,	//Left
						STEPPER_FWD, 0, 400);	//Right
					go2ContAngle(45, 100);

					frontIR = getFrontIR();
					if (frontIR < ICT){
						IsWall = IsWall++;
					}
					go2ContAngle(-90, 100);
					frontIR = getFrontIR();
					if (frontIR < ICT){
						IsWall = IsWall++;
					}
					go2ContAngle(45, 100);
					if (IsWall > 0){
						go2point(5,0);
					} else {
						LCD_clear();
						LCD_printf("Forward,");
						LCD_printf("\nthen Follow");

						STEPPER_move_rn(STEPPER_BOTH,
								STEPPER_FWD, 150, 400,	//Left
								STEPPER_FWD, 150, 400);	//Right
						TMRSRVC_delay(500);
						rightIR = getRightIR();
						leftIR = getLeftIR();
						if (leftIR > rightIR){
							//turn right
							go2ContAngle(-90, 100);
							leftFollow();
						}else {
							//turn left
							go2ContAngle(90, 100);
							rightFollow();
						}					

					} else {
						LCD_clear();
						LCD_printf("Random\n");
						LCD_printf("Wanderer\n");

						Random_Wanderer();
					}
				}


			}else if(ATTINY_get_SW_state(ATTINY_SW5)){
				// While SW5 is not pressed...
				go2ContAngle(-45, 100);

			}
			// Keeps running.
		}
	}
