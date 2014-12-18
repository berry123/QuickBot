#include <stdio.h>
#include <stdlib.h>

void Random_Wanderer(){
	char RightWheelSpeed;
	char LeftWheelSpeed;
	//while(1){
		// Randomly select speed of wheels
	RightWheelSpeed = rand() % 201;
	LeftWheelSpeed = rand() % 201;

	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, LeftWheelSpeed, 400,	//Left
		STEPPER_FWD, RightWheelSpeed, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
		//}
	}

void Shy_Random_Wanderer(){
	char RightWheelSpeed;
	char LeftWheelSpeed;
	//while(1){
	// Randomly select speed of wheels
	RightWheelSpeed = rand() % 201;
	LeftWheelSpeed = rand() % 201;

	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, LeftWheelSpeed, 400,	//Left
		STEPPER_FWD, RightWheelSpeed, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	shy();
		//}
}
