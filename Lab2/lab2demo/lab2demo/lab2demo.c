// demoLab1.c
/* Program description.*/
// Alexandre van der Ven de Freitas
// Peter Richard Olejnik
// December 3, 2014

#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include "capi324v221.h"

// Global variables:
//Permanent variables:
char xo = 0;
char yo = 0;
short thetao = 0;

// Used function prototypes.
void moveForward(int);
//float distance(float, float);
void go2Angle(short);
void go2Point(char, char);

// Main function
void CBOT_main(void)
{
	// Temporary variables:
	double dist;
	
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
	
	// While loop that keeps the micro controller running begins here:
    while(1)
    {
		// If the S3 button is pressed "Square path." is displayed and the robot performs the action.
		if (ATTINY_get_SW_state(ATTINY_SW3)){
			LCD_clear();
			dist = atan2(4,4) * (180/M_PI); // This works!
			LCD_printf("Robot is moving at %f.", dist);
			go2Point(1,1);
			go2Point(1,2);
			go2Point(2,2);
			//moveForward(570);
			//go2Angle(332);
			
			LCD_clear();
		}
		/*// If the S4 button is pressed "Circle path." is displayed and the robot performs the action.
		else if (ATTINY_get_SW_state(ATTINY_SW4)){
			LCD_clear();
			LCD_printf("Circle path.");
			moveCircle();
			LCD_clear();
		}
		// If the S5 button is pressed "Eight path." is displayed and the robot performs the action.
		else if (ATTINY_get_SW_state(ATTINY_SW5)){
			LCD_clear();
			LCD_printf("Eight path.");
			moveEight();
			LCD_clear();
		}*/
		// Keeps running.
    }
}

void moveForward(int steps){
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
		STEPPER_FWD, steps, 200, 400, STEPPER_BRK_OFF,	//Left wheel
		STEPPER_FWD, steps, 200, 400, STEPPER_BRK_OFF);	//Right wheel
}

void go2Angle(short angle){
	int steps;
	//short newAngle;
	
	LCD_clear();
	LCD_printf("%d", angle);
	
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	// Calculation of steps to turn:
	//newAngle = angle * (-1);
	//steps = (4/3) * newAngle;
	
	if (angle > 0){
		steps = angle*130/90;
		STEPPER_move_stwt(STEPPER_BOTH,
			STEPPER_REV, steps, 400, 800, STEPPER_BRK_ON,	//Left wheel
			STEPPER_FWD, steps, 400, 800, STEPPER_BRK_ON);	//Right wheel
	}else if(angle < 0){
		angle = angle * (-1);
		steps = angle*130/90;
		STEPPER_move_stwt(STEPPER_BOTH,
			STEPPER_FWD, steps, 400, 800, STEPPER_BRK_ON,	//Left wheel
			STEPPER_REV, steps, 400, 800, STEPPER_BRK_ON);	//Right wheel
	}else{
		// does nothing
	}
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_ON);
	STEPPER_close();
}

void go2Point(char x, char y){ //input in foot
	float deltax, deltay, distance, steps;
	short theta, deltaTheta;

	x = x*12;
	y = y*12;
	
	deltax = x - xo;
	deltay = y - xo;
	theta = atan2(deltay,deltax) * (180/M_PI);
	deltaTheta = theta - thetao;
	
	distance = hypot(deltax, deltay);
	
	steps = distance/0.108;
	
	go2Angle(deltaTheta);
	TMRSRVC_delay(500);
	moveForward(steps);
	
	xo = x;
	yo = y;
	thetao = theta;
}

/*// This function makes the robot move in a square path.
void moveSquare(void){
	
	// To be used in a for loop. unsigned char was used to make the variable take the smallest amount of memory possible.
	unsigned char i;
	
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	// The for loop in this case is used to make the robot move straight and turn right 90 degrees 4 times.
	for (i=0;i<4;i++){
		
		// Moving both wheels forward.
		STEPPER_move_stwt(STEPPER_BOTH,
			STEPPER_FWD, 570, 200, 400, STEPPER_BRK_OFF,	//Left wheel
			STEPPER_FWD, 570, 200, 400, STEPPER_BRK_OFF);	//Right wheel
		
		// Turning robot to the right 90 degrees.
		STEPPER_move_stwt(STEPPER_BOTH,
			STEPPER_REV, 120, 200, 400, STEPPER_BRK_OFF,	//Left wheel
			STEPPER_FWD, 120, 200, 400, STEPPER_BRK_OFF);	//Right wheel
	}
	
	// The stepper subsystem is closed when not used anymore.
	STEPPER_close();
}

// This function makes the robot move in a square path.
void moveCircle(void){
	
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	// Robot performs the circular CW path.
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, 2050, 205, 400, STEPPER_BRK_OFF,		//Left wheel
		STEPPER_FWD, 1100, 110, 400, STEPPER_BRK_OFF);	//Right wheel
	
	// The stepper subsystem is closed when not used anymore.
	STEPPER_close();
}

// This function makes the robot move in an eight-shaped path.
void moveEight(void){
	
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	// Robot performs the circular CW path.
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, 2050, 205, 400, STEPPER_BRK_OFF,		//Left wheel
		STEPPER_FWD, 1100, 110, 400, STEPPER_BRK_OFF);	//Right wheel
		
	// The delay here is used to let the robot lose its momentum. - 2 seconds delay or 2000ms.
	TMRSRVC_delay(2000);
	
	// Robot performs the circular CCW path.
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, 1100, 110, 400, STEPPER_BRK_OFF,		//Left wheel
		STEPPER_FWD, 2050, 205, 400, STEPPER_BRK_OFF);	//Right wheel
		
	// The stepper subsystem is closed when not used anymore.
	STEPPER_close();
}*/