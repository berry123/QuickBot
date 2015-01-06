// Random_Wanderer.h
/* This header file contains functions for the random wanderer behavior and subsumption defined.*/
// Alexandre van der Ven de Freitas
// Peter Richard Olejnik
// December 18, 2014

// Random wanderer function
void Random_Wanderer(){
	char RightWheelSpeed;
	char LeftWheelSpeed;
	
	// Randomly select speed of wheels
	RightWheelSpeed = rand() % 201;
	LeftWheelSpeed = rand() % 201;

	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, LeftWheelSpeed, 400,	//Left
		STEPPER_FWD, RightWheelSpeed, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	}

// Subsumption function
void Shy_Random_Wanderer(){
	char RightWheelSpeed;
	char LeftWheelSpeed;

	// Randomly select speed of wheels
	RightWheelSpeed = rand() % 201;
	LeftWheelSpeed = rand() % 201;

	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, LeftWheelSpeed, 400,	//Left
		STEPPER_FWD, RightWheelSpeed, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	shy();
}
