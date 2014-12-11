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

// Global variables:
char xo = 0;
char yo = 0;
short thetao = 0;

// Used function prototypes.
void moveForward(int, int);
void sTurnLeft(int, int);
void sTurnRight(int, int);
void go2Angle(int);
void go2Point(signed char, signed char);

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
	
	// After the initial setup, a "Ready!" message is displayed on the second line of the LCD display.
	LCD_printf("\nReady!");
	LCD_clear();
	
	// While loop that keeps the micro controller running begins here:
    while(1)
    {
		LCD_printf("SW3 - Angle | + ");
		LCD_printf("SW4 - Go to Point | -");
		LCD_printf("SW5 - Joke | Enter");
		
		// Press SW3 to select the angle function.
		if (ATTINY_get_SW_state(ATTINY_SW3)){
			// While SW5 is not pressed...
			while(!ATTINY_get_SW_state(ATTINY_SW5)){
				LCD_clear();
				LCD_printf("Angle: %d", deg); // Displays the angle selection.
				// If SW3 is pressed, the angle selection is increments by 15 degrees.
				if(ATTINY_get_SW_state(ATTINY_SW3)){
					deg = deg + 15;
					// If the angle is  > 180, it goes back to -180.
					if (deg > 360){
						deg = -360;
					}
				// If SW4 is pressed, the angle selection decrements by 15 degrees.
				}else if(ATTINY_get_SW_state(ATTINY_SW4)){
					deg = deg - 15;
					// If the angle is < -180, it goes back to -180.
					if(deg < -360){
						deg = 360;
					}
				}
			}
			// Calls go to angle function.
			go2Angle(deg);
			// The setup variable is cleared.
			deg = 0;
			LCD_clear();
		}
		// Press SW4 to go to goal function.
		else if (ATTINY_get_SW_state(ATTINY_SW4)){
			// While SW5 is not pressed...
			while(!ATTINY_get_SW_state(ATTINY_SW5)){
				LCD_clear();
				LCD_printf("( %d , %d )", cox, coy); // Displays the angle selection.
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
		}
		// If the SW5 button is pressed a silly message is displayed.
		else if (ATTINY_get_SW_state(ATTINY_SW5)){
			LCD_clear();
			LCD_printf("I'm useless...");
			TMRSRVC_delay(500);
			LCD_clear();
		}
		// Keeps running.
    }
}

// Moves the robot forward for a given number of steps.
void moveForward(int steps, int speed){
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	// Moving both wheels forward.
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, steps, speed, 400, STEPPER_BRK_OFF,	//Left wheel
		STEPPER_FWD, steps, speed, 400, STEPPER_BRK_OFF);	//Right wheel
}

// Rotates the robot to the required functions.
void go2Angle(int angle){
	
	// If the angle is positive, rotate the robot in a certain angle that is converted in steps to the left.
	if (angle > 0){
		if (angle <= 180){
			sTurnLeft(angle, 400);
		}else if(angle > 180){
			angle = angle/2;
			sTurnLeft(angle, 400);
			sTurnLeft(angle, 400);
		}
	// If the angle is negative, rotate the robot in a certain angle that is converted in steps to the right.
	}else if(angle < 0){
		angle = angle * (-1); //Make the angle positive to calculate the amount of steps.
		if (angle <= 180){
			sTurnRight(angle, 400);
		}else if (angle > 180){
			angle = angle/2;
			sTurnRight(angle, 400);
			sTurnRight(angle, 400);
		}
	}else{
		// does nothing
	}
}

// Guides the robot to the desired input point.
void go2Point(signed char x, signed char y){ //input in feet
	float deltax, deltay, distance, steps;
	int theta, deltaTheta;

	// Since the whole software was developed with an inches scale in mind, here the conversion to feet occurs.
	x = x*12;
	y = y*12;
	
	// Calculations:
	deltax = x - xo;
	deltay = y - yo;
	// Obtaining the theta in degrees since the function from math.h returns in radians.
	theta = atan2(deltay,deltax) * (180/M_PI);
	deltaTheta = theta - thetao;
	// This is for the sake of debugging:
	//LCD_clear();
	//LCD_printf("%d - %d = %d", theta, thetao, deltaTheta);
	//LCD_printf("x = %d, y = %d",x,y);
	
	// Calculating the length of the vector.
	distance = hypot(deltax, deltay);
	
	// Converting it into steps.
	steps = distance/0.108;
	
	// Call for go to angle function.
	go2Angle(deltaTheta);
	TMRSRVC_delay(500); //0.5 seconds delay.
	// Call for the go to goal point function.
	moveForward(steps, 200);
	
	// Updating the original values.
	xo = x;
	yo = y;
	thetao = theta;
}

// Given an angle and a speed, this function makes the robot turn/spin to the left.
void sTurnLeft(int angle, int speed){
	int steps;
	
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	steps = angle*130/90;
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_REV, steps, speed, 800, STEPPER_BRK_OFF,	//Left wheel
		STEPPER_FWD, steps, speed, 800, STEPPER_BRK_OFF);	//Right wheel
		
	STEPPER_close();
}

// Given an angle and a speed, this function makes the robot turn/spin to the right.
void sTurnRight(int angle, int speed){
	int steps;
	
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	steps = angle*130/90;
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, steps, speed, 800, STEPPER_BRK_OFF,	//Left wheel
		STEPPER_REV, steps, speed, 800, STEPPER_BRK_OFF);	//Right wheel
		
	STEPPER_close();
}