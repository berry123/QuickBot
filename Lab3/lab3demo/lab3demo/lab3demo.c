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

// IR Channels mapped to ADC inputs
#define IRRIGHT_CHAN ADC_CHAN3
#define IRLEFT_CHAN ADC_CHAN4
#define IRFRONT_CHAN ADC_CHAN7
#define IRBACK_CHAN ADC_CHAN5

// Global variables:
char xo = 0;
char yo = 0;
short thetao = 0;

// Used function prototypes.
//void moveForward();
void moveShy(char,char,char,char,char);
//void sTurnLeft(int, int);
//void sTurnRight(int, int);
//void go2Angle(int);
//void go2Point(signed char, signed char);
void aggressive();
void shy();
//IR functions
float getLeftIR();
float getRightIR();
float getFrontIR();
float getBackIR();

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
		LCD_printf("\nSW4: Other demos");
		LCD_clear();
		//LCD_printf("SW4 - Go to Point | -");
		//LCD_printf("SW5 - Joke | Enter");
		
		// Press SW3 to select the angle function.
		if (ATTINY_get_SW_state(ATTINY_SW3)){
			//aggressive();
			shy();
		}
		/*// Press SW4 to go to goal function.
		else if (ATTINY_get_SW_state(ATTINY_SW4)){
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
			//go2Point(cox,coy);
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
		}*/
		// Keeps running.
    }
}

// Moves the robot forward for a given number of steps.
/*void moveForward(){
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	//STEPPER_go(STEPPER_BOTH);
	
	//STEPPER_set_mode(BOTH_STEPPERS,STEPPER_FREERUNNING);
	
	//STEPPER_set_dir(BOTH_STEPPERS, STEPPER_FWD);
	
	//STEPPER_set_accel(BOTH_STEPPERS,400);
	
	//STEPPER_set_speed(BOTH_STEPPERS,100);
	
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, 200, 400,	//Left
		STEPPER_FWD, 200, 400);	//Right
	
	// Moving both wheels forward.
	//STEPPER_run(BOTH_STEPPERS,STEPPER_FWD,100);
	//STEPPER_move_stwt(STEPPER_BOTH,
	//	STEPPER_FWD, steps, speed, 400, STEPPER_BRK_OFF,	//Left wheel
	//	STEPPER_FWD, steps, speed, 400, STEPPER_BRK_OFF);	//Right wheel
}*/

// Rotates the robot to the required functions.
/*void go2Angle(int angle){
	
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
}*/

// Guides the robot to the desired input point.
/*void go2Point(signed char x, signed char y){ //input in feet
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
}*/

// Given an angle and a speed, this function makes the robot turn/spin to the left.
/*void sTurnLeft(int angle, int speed){
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
		
	//STEPPER_close();
}*/

// Given an angle and a speed, this function makes the robot turn/spin to the right.
/*void sTurnRight(int angle, int speed){
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
		
	//STEPPER_close();
}*/

// getLeftIR() converts ADC voltage to inches
float getLeftIR(){
	//float voltage;//IR range -0.4 to 5.3 V
	float distance;// (cm) 30 cm = 12 inches = 0.4 V
	float dist;//distance in inches
	ADC_SAMPLE adcsample;
	// Set the Voltage Reference first so VREF=5V.
	ADC_set_VREF( ADC_VREF_AVCC );
	// Set the channel we will sample from.
	ADC_set_channel( IRLEFT_CHAN );
	// Now sample it!
	adcsample = ADC_sample();
	LCD_printf( "ADC: %i\n",adcsample);
	// Convert to meaningful voltage value.
	//voltage = adcsample * ( 5.0 / 1024 );
	// Convert to distance in cm
	distance = (2914/(adcsample+5.0))-1.0;
	//Convert distance to inches
	dist = distance*0.3937;
	return dist;
}

// getRightIR() converts ADC voltage to inches
float getRightIR(){
	//float voltage;//IR range -0.4 to 5.3 V
	float distance;// (cm) 30 cm = 12 inches = 0.4 V
	float dist;//distance in inches
	ADC_SAMPLE adcsample;
	// Set the Voltage Reference first so VREF=5V.
	ADC_set_VREF( ADC_VREF_AVCC );
	// Set the channel we will sample from.
	ADC_set_channel( IRRIGHT_CHAN );
	// Now sample it!
	adcsample = ADC_sample();
	// Convert to meaningful voltage value.
	//voltage = adcsample * ( 5.0 / 1024 );
	// Convert to distance in cm
	distance = (2914/(adcsample+5.0))-1.0;
	//Convert distance to inches
	dist = distance*0.3937;
	return dist;
}

// getFrontIR() simply sets the ADC to the Front IR sensor
// and returns the sampled voltage in inches. Short, nonblocking.
float getFrontIR(){
	//1 inch = 2.54 cm
	//1 cm = 0.3937 inches
	//float voltage;//IR range -0.4 to 5.3 V
	float distance;// (cm) 30 cm = 12 inches = 0.4 V
	float dist;//distance in inches
	ADC_SAMPLE adcsample;
	// Set the Voltage Reference first so VREF=5V.
	ADC_set_VREF( ADC_VREF_AVCC );
	// Set the channel we will sample from.
	ADC_set_channel(IRFRONT_CHAN);
	// Now sample it!
	adcsample = ADC_sample();
	// Convert to meaningful voltage value.
	//voltage = adcsample * ( 5.0 / 1024 );
	// Convert to distance in cm
	distance = (2914/(adcsample+5.0))-1.0;
	//Convert distance to inches
	dist = distance*0.3937;
	return dist;
}

// getBackIR() simply sets the ADC to the Back IR sensor
// and returns the sampled voltage in inches. Short, nonblocking.
float getBackIR(){
	//1 inch = 2.54 cm
	//1 cm = 0.3937 inches
	//float voltage;//IR range -0.4 to 5.3 V
	float distance;// (cm) 30 cm = 12 inches = 0.4 V
	float dist;//distance in inches
	ADC_SAMPLE adcsample;
	// Set the Voltage Reference first so VREF=5V.
	ADC_set_VREF( ADC_VREF_AVCC );
	// Set the channel we will sample from.
	ADC_set_channel(IRBACK_CHAN);
	// Now sample it!
	adcsample = ADC_sample();
	// Convert to meaningful voltage value.
	//voltage = adcsample * ( 5.0 / 1024 );
	// Convert to distance in cm
	distance = (2914/(adcsample+5.0))-1.0;
	//Convert distance to inches
	dist = distance*0.3937;
	return dist;
}


void aggressive(){
	
	float frontIR = 0;
	
	while(1){
	
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
	
	
	while(1){
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
		
		moveShy(FSS,BSS,RSS,LSS,TS);
	}
}

void moveShy(char FSS, char BSS, char RSS, char LSS, char TS){
	switch(TS){
		case 1: // If only one sensor is triggered
		if ((FSS == 1) && (BSS == 0) && (RSS == 0) &&(LSS == 0)){
			Backward_Move();
			}else if ((FSS == 0) && (BSS == 1) && (RSS == 0) &&(LSS == 0)){
			Forward_Move();
			}else if ((FSS == 0) && (BSS == 0) && (RSS == 0) &&(LSS == 1)){
			Soft_Forward_Right();
			}else{
			Soft_Forward_Left();
		}
		break;
		case 2: // If two sensors are triggered
		if ((FSS == 1) && (BSS == 0) && (RSS == 0) &&(LSS == 1)){
			Soft_Backward_Right();
			}else if ((FSS == 1) && (BSS == 0) && (RSS == 1) &&(LSS == 0)){
			Soft_Backward_Left();
			}else if ((FSS == 0) && (BSS == 1) && (RSS == 0) &&(LSS == 1)){
			Soft_Forward_Right();
			}else if ((FSS == 0) && (BSS == 1) && (RSS == 1) &&(LSS == 0)){
			Soft_Forward_Left();
			}else {
			Forward_Move();
		}
		break;
		case 3: // If three sensors are triggered
		if ((FSS == 1) && (BSS == 1) && (RSS == 0) &&(LSS == 1)){
			Hard_Right();
			}else if ((FSS == 1) && (BSS == 1) && (RSS == 1) &&(LSS == 0)){
			Hard_Left();
			}else if ((FSS == 1) && (BSS == 0) && (RSS == 1) &&(LSS == 1)){
			Backward_Move();
			}else {
			Forward_Move();
		}
		break;
		case 4: // If all four sensors are triggered
			Cry();
			break;
		default: // If none of the sensors are triggered
			// just stay and chill!
			break;
	}
}
