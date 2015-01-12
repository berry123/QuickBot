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
#include "wallFollow2.h"		// Functions that power the wall following procedures

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
			while(1){ // Logic that determins what conditions the robot starts at and what to demo
				frontIR = getFrontIR();
				rightIR = getRightIR();
				leftIR = getLeftIR();
				if ((leftIR < ICT) && (rightIR < ICT)) { // near both walls so use center follow
					centerFollow();
				} else if (rightIR < ICT){ // Walls to the right so follows on the right side
					rightFollow();
				} else if (leftIR < ICT) { // Walls to the left so follows on the left side
					leftFollow();
				} else if (frontIR < ICT) { // Sees something to the front of it
					LCD_clear();
					LCD_printf("Forward,");
					LCD_printf("\nthen Follow");

					STEPPER_move_rn(STEPPER_BOTH, // Move a tad forward to get closer to the wall
							STEPPER_FWD, 150, 400,	//Left
							STEPPER_FWD, 150, 400);	//Right
					TMRSRVC_delay(500); // 0.5 sec delay
					rightIR = getRightIR();
					leftIR = getLeftIR();
					if (leftIR > rightIR){ // determins what side the robot is closer to the wall. Essentialy random when perpendicular
						//turn right
						go2ContAngle(-90, 100); // Left 90 turn
						leftFollow();
					}else {
						//turn left
						go2ContAngle(90, 100); // Right 90 turn
						rightFollow();
					}
				} else { // If sensors don't detect anything, random wanderer is engaged
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
				if ((leftIR < ICT) && (rightIR < ICT)) { // near both walls so use center follow
					centerFollow();
				} else if (rightIR < ICT){ // Walls to the right so follows on the right side
					rightFollow();
				} else if (leftIR < ICT) { // Walls to the left so follows on the left side
					leftFollow();
				} else if (frontIR < ICT) { // Sees something to the front of it
					STEPPER_move_rn(STEPPER_BOTH, // Move a tad forward to get closer to the wall
							STEPPER_FWD, 0, 400,	//Left
							STEPPER_FWD, 0, 400);	//Right
					go2ContAngle(45, 100); // Right 45 degree turn

					frontIR = getFrontIR();
					if (frontIR < ICT){ // test if object or wall
						IsWall = IsWall++;
					}
					go2ContAngle(-90, 100); // Left 90 degree turn
					frontIR = getFrontIR();
					if (frontIR < ICT){  // test if object or wall
						IsWall = IsWall++;
					}
					go2ContAngle(45, 100); // Right 45 degree turn
					if (IsWall > 0){ // avoid object
						go2point(5,0);
					} else { // follow the wall
						LCD_clear();
						LCD_printf("Forward,");
						LCD_printf("\nthen Follow");

						STEPPER_move_rn(STEPPER_BOTH,
								STEPPER_FWD, 150, 400,	//Left
								STEPPER_FWD, 150, 400);	//Right
						TMRSRVC_delay(500); // 0.5 sec delay
						rightIR = getRightIR();
						leftIR = getLeftIR();
						if (leftIR > rightIR){
							//turn 90 degree right
							go2ContAngle(-90, 100);
							leftFollow();
						}else {
							//turn 90 degree left
							go2ContAngle(90, 100);
							rightFollow();
						}					

					} }else { // If sensors don't detect anything, random wanderer is engaged
						LCD_clear();
						LCD_printf("Random\n");
						LCD_printf("Wanderer\n");

						Random_Wanderer();
					}
				}


			}else if(ATTINY_get_SW_state(ATTINY_SW5)){
				// While SW5 is not pressed...
				while(!ATTINY_get_SW_state(ATTINY_SW5)){
					LCD_clear();
					LCD_printf("( %d , %d )", cox, coy); // Displays the angle selection.
					LCD_printf("\nSW3 + | SW4 - \nSW5 To y");
					// If SW3 is pressed, the coordinate x is incremented.
					if(ATTINY_get_SW_state(ATTINY_SW3)){
						cox++;
						// If the x value is > 5, it goes back to -5.
						if (cox > 20){
							cox = -20;
						}
						// If SW4 is pressed, the coordinate x is decremented.
						}else if(ATTINY_get_SW_state(ATTINY_SW4)){
						cox--;
						// If the x value is < -5, it goes back to 5.
						if(cox < -20){
							cox = 20;
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
						if (coy > 20){
							coy = -20;
						}
						// If SW4 is pressed, the coordinate y is decremented.
						}else if(ATTINY_get_SW_state(ATTINY_SW4)){
						coy--;
						// If the x value is < -5, it goes back to 5
						if(coy < -20){
							coy = 20;
						}
					}
				}
				// Calls go to goal point function.
				go2Goal(cox,coy);
				// Clears the variables up.
				cox = 0;
				coy = 0;
				LCD_clear();

			}
			// Keeps running.
		}
	}
