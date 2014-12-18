// lab2demo.c
/* This code contains multiple motion functions in order to allow the robot travel to a given location in cartesian points in the x-y plane that is spaced in feet. When the robot is ready after being booted.
	Pressing SW3 allows the user to set an angle the robot can move itself to. By pressing SW4 allows the user to set a point in space the robot should go to. Once in the angle sub menu, the SW3 button increments
	the angle by a factor of 15 degrees. SW4 button decrements the angle by a factor of 15 also. SW5 enters and allows the robot to perform the action. When selecting the go to goal sub menu, the system works in a
	similar manner by first incrementing/decrementing the x value by a factor of 1, then by pressing SW5 selecting the value of y and then pressing SW5 to enter your selection and allow the robot to perform the
	desired action.*/
// Alexandre van der Ven de Freitas
// Peter Richard Olejnik
// December 9, 2014

#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include "capi324v221.h"
#include "Capek_Movements.h"
#include "Movement_Selector.h"
#include "Random_Wanderer.h"
#include "IRlib.h"
#include "AvoidAndGo.h"

// Global variables:
char xo = 0;
char yo = 0;
short thetao = 0;

// Used function prototypes.
void moveShy(char,char,char,char,char);
void aggressive();
void shy();
void goToGoal(signed char, signed char);
/*//IR functions
float getLeftIR();
float getRightIR();
float getFrontIR();
float getBackIR();*/

// Main function
void CBOT_main(void)
{
	// local main variables:
	int deg = 0;
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
	
	SPKR_open(SPKR_BEEP_MODE);//open the speaker in beep mode
	ADC_open();//open the ADC module
	ADC_set_VREF( ADC_VREF_AVCC );// Set the Voltage Reference first so VREF=5V.
	STEPPER_open();
	
	// After the initial setup, a "Ready!" message is displayed on the second line of the LCD display.
	LCD_printf("\nReady!");
	LCD_clear();
	
	// While loop that keeps the micro controller running begins here:
    while(1)
    {
		LCD_printf("SW3: Kids");
		//LCD_clear();
		LCD_printf("\nSW4: Randoms");
		LCD_printf("\nSW5: Go to goal");
		LCD_clear();
		//LCD_printf("SW4 - Go to Point | -");
		//LCD_printf("SW5 - Joke | Enter");
		
		// Press SW3 to select the angle function.
		if (ATTINY_get_SW_state(ATTINY_SW3)){
			while(!ATTINY_get_SW_state(ATTINY_SW5)){
				LCD_clear();
				LCD_printf("SW3: Aggressive");
				LCD_printf("\nSW4: Shy");
				LCD_printf("\nSW5: Back");
				if(ATTINY_get_SW_state(ATTINY_SW3)){
					while(1){
						aggressive();
					}
				}else if(ATTINY_get_SW_state(ATTINY_SW4)){
					while(1){
						shy();
					}
				}
			}
		}else if(ATTINY_get_SW_state(ATTINY_SW4)){
			LCD_clear();
			LCD_printf("SW3: Random.");
			LCD_printf("\nSW4: Subsumption.");
			LCD_printf("\nSW5: Back");
			while(!ATTINY_get_SW_state(ATTINY_SW5)){
				if(ATTINY_get_SW_state(ATTINY_SW3)){
					while(1){
						Random_Wanderer();
					}
				}else if(ATTINY_get_SW_state(ATTINY_SW4)){
					while(1){
						Shy_Random_Wanderer();
					}
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
			AvoidAndGo(cox,coy);
			// Clears the variables up.
			cox = 0;
			coy = 0;
			LCD_clear();
		}
		// Keeps running.
    }
}

void aggressive(){
	
	float frontIR = 0;
	
	frontIR = getFrontIR();
	
	LCD_printf("%f", frontIR);
	LCD_clear();
	
	if(frontIR >= 5){
		STEPPER_move_rn(STEPPER_BOTH,
			STEPPER_FWD, 200, 400,	//Left
			STEPPER_FWD, 200, 400);	//Right
	}else{
		STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}
}

void shy(){
	char sensLimit = 5;
	char TS;
	char genRand;
	float frontIR = 0;
	float backIR = 0;
	float rightIR = 0;
	float leftIR = 0;
	char FSS;
	char BSS;
	char RSS;
	char LSS;
	
	frontIR = getFrontIR();
	backIR = getBackIR();
	rightIR = getRightIR();
	leftIR = getLeftIR();

	LCD_clear();
	LCD_printf("%f, %f, %f, %f", frontIR, backIR, rightIR, leftIR);

	FSS = (sensLimit > frontIR);
	BSS = (sensLimit > backIR);
	RSS = (sensLimit > rightIR);
	LSS = (sensLimit > leftIR);

	TS = FSS + BSS + RSS + LSS;
		
	Movement_Selector_Excecutor(FSS, BSS, RSS, LSS, TS);
}



