/*
 * demoLab1.c
 *
 * Created: 12/3/2014 2:11:00 PM
 *  Author: vaddera
 */ 


#include <avr/io.h>
#include "capi324v221.h"

void moveSquare(void);
void moveCircle(void);
void moveEight(void);

void CBOT_main(void)
{
	//unsigned char flag = 0;
	LCD_open(); // Opening LCD Subsystem management.
	LCD_printf("Setting up...");
	
	SUBSYS_OPENSTAT openTiny; // Here you can add multiple variables as you open subsystems.
	
	openTiny = ATTINY_open();
	
	if (openTiny.state != SUBSYS_OPEN){ // state comes from the struct SUBSYS_OPENSTAT_TYPE
		LCD_clear();
		LCD_printf("Error when opening ATTINY!");
	}
	LCD_printf("\nReady!");
	
	
    while(1)
    {
		/*if (flag==0){
			LCD_clear();
			flag = 1;
		}
		
		LCD_printf("SW3 - Square path.\nSW4 - Circle path.\nSW5 - Eight path.");*/
        
		if (ATTINY_get_SW_state(ATTINY_SW3)){
			LCD_clear();
			LCD_printf("Square path.");
			moveSquare();
			LCD_clear();
		}
		else if (ATTINY_get_SW_state(ATTINY_SW4)){
			LCD_clear();
			LCD_printf("Circle path.");
			moveCircle();
			LCD_clear();
		}
		else if (ATTINY_get_SW_state(ATTINY_SW5)){
			LCD_clear();
			LCD_printf("Eight path.");
			moveEight();
			LCD_clear();
		}
    }
}

void moveSquare(void){
	unsigned char i;
	SUBSYS_OPENSTAT openStepper;
	
	openStepper = STEPPER_open();
	
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	for (i=0;i<4;i++){ // Runs the same routine twice in order to make the robot move in a square fashion.
		// Moving both wheels forward.
		STEPPER_move_stwt(STEPPER_BOTH,
			STEPPER_FWD, 570, 200, 400, STEPPER_BRK_OFF,	//Left wheel
			STEPPER_FWD, 570, 200, 400, STEPPER_BRK_OFF);	//Right wheel
		
		// Turning robot to the right.
		STEPPER_move_stwt(STEPPER_BOTH,
			STEPPER_FWD, 120, 200, 400, STEPPER_BRK_OFF,	//Left wheel
			STEPPER_REV, 120, 200, 400, STEPPER_BRK_OFF);	//Right wheel
	}
	
	STEPPER_close();
}

void moveCircle(void){
	SUBSYS_OPENSTAT openStepper;
	
	openStepper = STEPPER_open();
	
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, 2050, 205, 400, STEPPER_BRK_OFF,		//Left wheel
		STEPPER_FWD, 1100, 110, 400, STEPPER_BRK_OFF);	//Right wheel
	
	STEPPER_close();
}

void moveEight(void){
	SUBSYS_OPENSTAT openStepper;
	
	openStepper = STEPPER_open();
	
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, 2050, 205, 400, STEPPER_BRK_OFF,		//Left wheel
		STEPPER_FWD, 1100, 110, 400, STEPPER_BRK_OFF);	//Right wheel
		
	TMRSRVC_delay(2000);
	
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, 1100, 110, 400, STEPPER_BRK_OFF,		//Left wheel
		STEPPER_FWD, 2050, 205, 400, STEPPER_BRK_OFF);	//Right wheel
		
	STEPPER_close();
}