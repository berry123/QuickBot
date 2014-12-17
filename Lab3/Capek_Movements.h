void Forward_Move(){
	// Forward Movement
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, 200, 400,	//Left
		STEPPER_FWD, 200, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}

void Backward_Move(){
	// Backward Movement
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_REV, 200, 400,	//Left
		STEPPER_REV, 200, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}

void Hard_Right(){
	// Excecutes a 90 degree turn
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, 130, 200, 800, STEPPER_BRK_OFF,	//Left wheel
		STEPPER_REV, 130, 200, 800, STEPPER_BRK_OFF);	//Right wheel
	// Forward Movement
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, 200, 400,	//Left
		STEPPER_FWD, 200, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}

void Hard_Left(){
	// Excecutes a 90 degree turn
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_REV, 130, 200, 800, STEPPER_BRK_OFF,	//Left wheel
		STEPPER_FWD, 130, 200, 800, STEPPER_BRK_OFF);	//Right wheel
	// Forward Movement
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, 200, 400,	//Left
		STEPPER_FWD, 200, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}

void Soft_Forward_Right(){
	// Forward Movement
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, 200, 400,	//Left
		STEPPER_FWD, 150, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}

void Soft_Forward_Left(){
	// Forward Movement
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, 150, 400,	//Left
		STEPPER_FWD, 200, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}

void Soft_Backward_Right(){
	// Forward Movement
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_REV, 200, 400,	//Left
		STEPPER_REV, 150, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}

void Soft_Backward_Left(){
	// Forward Movement
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_REV, 150, 400,	//Left
		STEPPER_REV, 200, 400);	//Right
	TMRSRVC_delay(500); //5 Sec duration
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}

void Cry(){
	char count;
	count = 0;
	// Capek is confused and crys from frustration
	while (count < 20){
		SPKR_play_beep(250, 500, 50);//500 Hz for 250 ms
		count++;
		}
	}
	

