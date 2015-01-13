void pseudo_Stepper_Step(int Right_Wheel_Speed, int Left_Wheel_Speed, int Duration){
	
	STEPPER_move_stwt(STEPPER_BOTH,
			STEPPER_FWD, Left_Wheel_Speed*Duration, Left_Wheel_Speed, 400, STEPPER_BRK_OFF,	//Left wheel
			STEPPER_FWD, Right_Wheel_Speed*Duration, Right_Wheel_Speed, 400, STEPPER_BRK_OFF);	// Right wheel
}