void light_fear(void){
	float Left_Light, Right_Light, Callibration;
	int basespeed = 250;

	LCD_clear();
	LCD_printf("ARGG!!\n");
	LCD_printf("IT BURNS!!\n");
	LCD_printf("IT BURNS US!!\n");
	Callibration = ALC();

	while(1){
		Left_Light = getLeftLight(Callibration);
		Right_Light = getRightLight(Callibration);
		STEPPER_move_rn(STEPPER_BOTH,
				STEPPER_REV, (Right_Light*basespeed), 400,	//Left
				STEPPER_REV, (Left_Light*basespeed), 400);	//Right
		TMRSRVC_delay(100); // 0.1 Sec duration
	}
}

void light_aggression(void){
	float Left_Light, Right_Light, Callibration;
	int basespeed = 250;

	LCD_clear();
	LCD_printf("RAAAAAA...\n");
	LCD_printf("AAAAAAA...\n");
	LCD_printf("AAAAAAA...\n");
	LCD_printf("AAAWWR\n");
	Callibration = ALC();

	while(1){
		Left_Light = getLeftLight(Callibration);
		Right_Light = getRightLight(Callibration);
		STEPPER_move_rn(STEPPER_BOTH,
				STEPPER_FWD, (Left_Light*basespeed), 400,	//Left
				STEPPER_FWD, (Right_Light*basespeed), 400);	//Right
		TMRSRVC_delay(100); // 0.1 Sec duration
	}	
}

void light_love(void){
	float Left_Light, Right_Light, Callibration;
	int basespeed = 250;

	LCD_clear();
	LCD_printf("mmmmmmm...\n");
	LCD_printf("light...\n");
	Callibration = ALC();

	while(1){
		Left_Light = getLeftLight(Callibration);
		Right_Light = getRightLight(Callibration);
		STEPPER_move_rn(STEPPER_BOTH,
				STEPPER_FWD, ((1-Left_Light)*basespeed), 400,	//Left
				STEPPER_FWD, ((1-Right_Light)*basespeed), 400);	//Right
		TMRSRVC_delay(100); // 0.1 Sec duration
	}
}

void light_explorer(void){
	float Left_Light, Right_Light, Callibration;
	int basespeed = 250;

	LCD_clear();
	LCD_printf("Ola!\n");
	LCD_printf("Me lamo Dora!\n");
	Callibration = ALC();

	while(1){
		Left_Light = getLeftLight(Callibration);
		Right_Light = getRightLight(Callibration);
		STEPPER_move_rn(STEPPER_BOTH,
				STEPPER_FWD, ((1-Right_Light)*basespeed), 400,	//Left
				STEPPER_FWD, ((1-Left_Light)*basespeed), 400);	//Right
		TMRSRVC_delay(100); // 0.1 Sec duration
	}
}

void light_crush(void){
	float Left_Light, Right_Light, Callibration, frontIR, rightIR, leftIR;
	char FSS, RSS, LSS, TS;
	int basespeed = 250;
	char sensLimit = 5;

	LCD_clear();
	LCD_printf("I like you...\n");
	LCD_printf("...but PIC's\n");
	LCD_printf("scare me!\n");
	Callibration = ALC();

	while(1){
		Left_Light = getLeftLight(Callibration);
		Right_Light = getRightLight(Callibration);
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();

		FSS = (sensLimit > frontIR);
		RSS = (sensLimit > rightIR);
		LSS = (sensLimit > leftIR);

		TS = FSS + RSS + LSS;

		if (TS > 0){
			Movement_Selector_Excecutor(FSS, 0, RSS, LSS, TS);
		}

		STEPPER_move_rn(STEPPER_BOTH,
				STEPPER_FWD, ((1-Left_Light)*basespeed), 400,	//Left
				STEPPER_FWD, ((1-Right_Light)*basespeed), 400);	//Right
		TMRSRVC_delay(100); // 0.1 Sec duration
	}

}
/*void light_return(void){
	float Left_Light, Right_Light, Calibration;
	while(1){
		Left_Light = getLeftLight(0);
		Right_Light = getRightLight(0);
		Calibration = ALC();
		LCD_clear();
		LCD_printf("Left:  %f1.5\n");
		LCD_printf("Right: %f1.5\n");
		LCD_printf("Cal:   %f1.5\n");
		TMRSRVC_delay(100); // 0.1 Sec duration		
	}
}*/
