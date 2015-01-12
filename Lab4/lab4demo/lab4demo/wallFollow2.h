void rightFollow(void){
	// code that powers the right wall following routine
	char lowerLimit = 4.75;
	char higherLimit = 5.25;
	char ICT = 12;
	float LP, RP, LWS, RWS, frontIR, rightIR, leftIR;
	float oLWS = 0;
	float oRWS = 0;
	float LI = 0;
	float RI = 0;
	char base = 120;
	
	// Gains
	
	char KP = 1.5;
	char KI = 0.75;
	char KD = 0;

	while(1){
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		if((frontIR > ICT) && (rightIR < ICT)){ // Condition for simple wall following
			if (rightIR < lowerLimit){ // Too close to wall
				LCD_clear();
				LCD_printf("Right Follow\n");
				LCD_printf("Inside Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = lowerLimit - rightIR;
				LI = 0;
				RI = RI++;
			}else if(rightIR > higherLimit){ // Too far from wall
				LCD_clear();
				LCD_printf("Right Follow\n");
				LCD_printf("Outside Target\n");
				LCD_printf("Range\n");

				LP = rightIR - higherLimit;
				RP = 0;
				LI = LI++;
				RI = 0;
			}else{ // Proper range from wall
				LCD_clear();
				LCD_printf("Right Follow\n");
				LCD_printf("At Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = 0;
				LI = 0;
				RI = 0;
			}
			
			// PID lopp
			
			LWS = KP*LP + KI*LI + base; // Proportinal and Integral
			RWS = KP*RP + KI*RI + base;
			if (oLWS == 0){ // Case to prevent weird stuff on first run
				oLWS = LWS;
				oRWS = RWS;
			}
			LWS = LWS + KD*(oLWS-LWS); // Derivative component
			RWS = RWS + KD*(oRWS-RWS);

			STEPPER_move_rn(STEPPER_BOTH, // Forward Movement
					STEPPER_FWD, LWS, 400,	//Left
					STEPPER_FWD, RWS, 400);	//Right

			oLWS = LWS; // Remember previous speeds for derivative component
			oRWS = RWS;

		}else if((frontIR < ICT) && (rightIR < ICT)){ // Condition for if wall is in front
			LCD_clear();
			LCD_printf("Right Follow\n");
			LCD_printf("Wall in Front\n");
			LCD_printf("Turning Left\n");
			
			STEPPER_move_rn(STEPPER_BOTH, // Forward movement
					STEPPER_FWD, 150, 400,	//Left
					STEPPER_FWD, 150, 400);	//Right
			TMRSRVC_delay(500); // 0.5 sec delay
			go2ContAngle(-90, 100); // Left 90 Turn
			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;
		}else if((frontIR > ICT) && (rightIR > ICT)){ // Condition for is no wall to follow or in front
			LCD_clear();
			LCD_printf("Right Follow\n");
			LCD_printf("Lack of Wall\n");
			LCD_printf("Turning Right\n");
			
			STEPPER_move_rn(STEPPER_BOTH, // Forward movement
					STEPPER_FWD, 150, 400,	//Left
					STEPPER_FWD, 150, 400);	//Right
			TMRSRVC_delay(500); // 0.5 Sec delay
			rightIR = getRightIR();
			if ((frontIR > ICT) && (rightIR > ICT)){
				go2ContAngle(90, 100); // Right 90 Turn
				STEPPER_move_rn(STEPPER_BOTH, // Forward movement
						STEPPER_FWD, 150, 400,	//Left
						STEPPER_FWD, 150, 400);	//Right
				rightIR = getRightIR();
				while(rightIR > ICT){
					TMRSRVC_delay(100); // 0.1 sec delay
					rightIR = getRightIR();
				}
				LP = 0;
				RP = 0;
				LI = 0;
				RI = 0;	
			}
		}
	}
}

void leftFollow(void){
	// code that powers the left wall following routine
	char lowerLimit = 4.75;
	char higherLimit = 5.25;
	char ICT = 12;
	float LP, RP, LWS, RWS, frontIR, rightIR, leftIR;
	float oLWS = 0;
	float oRWS = 0;
	float LI = 0;
	float RI = 0;
	char base = 120;
	char KP = 1.5;
	char KI = 0.75;
	char KD = 0;

	while(1){
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		if((frontIR > ICT) && (leftIR < ICT)){ // Condition for simple wall following
			if (leftIR < lowerLimit){ // Too close to wall
				LCD_clear();
				LCD_printf("Left Follow\n");
				LCD_printf("Inside Target\n");
				LCD_printf("Range\n");

				LP = lowerLimit - leftIR;
				RP = 0;
				LI = LI++;
				RI = 0;
			}else if(leftIR > higherLimit){ // Too far from wall
				LCD_clear();
				LCD_printf("Left Follow\n");
				LCD_printf("Outside Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = leftIR - higherLimit;
				LI = 0;
				RI = RI++;
			}else{ // Proper range from wall
				LCD_clear();
				LCD_printf("Left Follow\n");
				LCD_printf("At Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = 0;
				LI = 0;
				RI = 0;
			}

			// PID lopp
									
			LWS = KP*LP + KI*LI + base; // Proportinal and Integral
			RWS = KP*RP + KI*RI + base;
			if (oLWS == 0){ // Case to prevent weird stuff on first run
				oLWS = LWS;
				oRWS = RWS;
			}
			LWS = LWS + KD*(oLWS-LWS); // Derivative component
			RWS = RWS + KD*(oRWS-RWS);

			STEPPER_move_rn(STEPPER_BOTH, // Forward Movement
					STEPPER_FWD, LWS, 400,	//Left
					STEPPER_FWD, RWS, 400);	//Right

			oLWS = LWS; // Remember previous speeds for derivative component
			oRWS = RWS;

		}else if((frontIR < ICT) && (leftIR < ICT)){ // Condition for if wall is in front
			LCD_clear();
			LCD_printf("Left Follow\n");
			LCD_printf("Wall in Front\n");
			LCD_printf("Turning Right\n");

			STEPPER_move_rn(STEPPER_BOTH, // Forward movement
					STEPPER_FWD, 150, 400,	//Left
					STEPPER_FWD, 150, 400);	//Right
			TMRSRVC_delay(500); // 0.5 sec delay
			go2ContAngle(90, 100); // Right 90 Turn
			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;	
		}else if((frontIR > ICT) && (leftIR > ICT)){ // Condition for is no wall to follow or in front
			LCD_clear();
			LCD_printf("Left Follow\n");
			LCD_printf("Lack of Wall\n");
			LCD_printf("Turning Left\n");

			STEPPER_move_rn(STEPPER_BOTH, // Forward movement
					STEPPER_FWD, 150, 400,	//Left
					STEPPER_FWD, 150, 400);	//Right
			TMRSRVC_delay(500); // 0.5 sec delay
			leftIR = getLeftIR();
			if ((frontIR > ICT) && (leftIR > ICT)){
				go2ContAngle(-90, 100); // Left 90 Turn
				STEPPER_move_rn(STEPPER_BOTH, // Forward movement
						STEPPER_FWD, 150, 400,	//Left
						STEPPER_FWD, 150, 400);	//Right
				leftIR = getLeftIR();
				while(leftIR > ICT){
					TMRSRVC_delay(100); // 0.1 sec delay
					leftIR = getLeftIR();
				}
				LP = 0;
				RP = 0;
				LI = 0;
				RI = 0;	
			}
		}
	}
}
void centerFollow(void){
	char tollerance_band = 0;
	float LP, RP, LWS, RWS, frontIR, rightIR, leftIR, avrageIR;
	float oLWS = 0;
	float oRWS = 0;
	float LI = 0;
	float RI = 0;
	char base = 120;
	char KP = 1.5;
	char KI = 0.75;
	char ICT = 12;
	char KD = 0;

	rightIR = getRightIR();
	leftIR = getLeftIR();
	while ((leftIR < ICT) && (rightIR < ICT)){
		rightIR = getRightIR();
		leftIR = getLeftIR();
		avrageIR = (rightIR + leftIR)/2;
		if ((rightIR - avrageIR) > tollerance_band){
			//means left of center
			LCD_clear();
			LCD_printf("Center Follow\n");
			LCD_printf("Left of\n");
			LCD_printf("Center\n");

			LP = rightIR - avrageIR;
			RP = 0;
			LI = LI++;
			RI = 0;
		} else if ((avrageIR - rightIR) > (tollerance_band)) {
			//means right of center
			LCD_clear();
			LCD_printf("Center Follow\n");
			LCD_printf("Right of\n");
			LCD_printf("Center\n");

			LP = 0;
			RP = leftIR - avrageIR;
			LI = 0;
			RI = RI++;
		} else {
			//means center of center
			LCD_clear();
			LCD_printf("I shall\n");
			LCD_printf("fear no\n");
			LCD_printf("evil\n");

			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;
		}
		LWS = KP*LP + KI*LI + KD*oLWS + base;
		RWS = KP*RP + KI*RI + KD*oRWS + base;
		if (oLWS == 0){
			oLWS = LWS;
			oRWS = RWS;
		}
		LWS = LWS + KD*(oLWS-LWS);
		RWS = RWS + KD*(oRWS-RWS);

		// Forward Movement
		STEPPER_move_rn(STEPPER_BOTH,
				STEPPER_FWD, LWS, 400,	//Left
				STEPPER_FWD, RWS, 400);	//Right

		oLWS = LWS;
		oRWS = RWS;
	}	
}

//
//
/* ---------------- Underneath are functions that use stepping: ---------------- */
//
//

void rightStepFollow(void){
	char lowerLimit = 5;
	char higherLimit = 5;
	char ICT = 12;
	float LP, RP, LWS, RWS, frontIR, rightIR, leftIR;
	float oLWS = 0;
	float oRWS = 0;
	float LI = 0;
	float RI = 0;
	char base = 120;
	char KP = 1;
	char KI = 0;
	char KD = 0;

	while(1){
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		if((frontIR > ICT) && (rightIR < ICT)){
			if (rightIR < lowerLimit){
				LCD_clear();
				LCD_printf("Right Follow\n");
				LCD_printf("Inside Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = lowerLimit - rightIR;
				LI = 0;
				RI = RI++;
			}else if(rightIR > higherLimit){
				LCD_clear();
				LCD_printf("Right Follow\n");
				LCD_printf("Outside Target\n");
				LCD_printf("Range\n");

				LP = rightIR - higherLimit;
				RP = 0;
				LI = LI++;
				RI = 0;
			}else{
				LCD_clear();
				LCD_printf("Right Follow\n");
				LCD_printf("At Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = 0;
				LI = 0;
				RI = 0;
			}

			LWS = KP*LP + KI*LI + base;
			RWS = KP*RP + KI*RI + base;
			if (oLWS == 0){
				oLWS = LWS;
				oRWS = RWS;
			}
			LWS = LWS + KD*(oLWS-LWS);
			RWS = RWS + KD*(oRWS-RWS);

			// Forward Movement
			STEPPER_move_stwt(STEPPER_BOTH,
				STEPPER_FWD, 200, LWS, 400, STEPPER_BRK_OFF,	//Left wheel
				STEPPER_FWD, 200, RWS, 400, STEPPER_BRK_OFF);	// Right wheel

			oLWS = LWS;
			oRWS = RWS;

		}else if((frontIR < ICT) && (rightIR < ICT)){
			LCD_clear();
			LCD_printf("Right Follow\n");
			LCD_printf("Wall in Front\n");
			LCD_printf("Turning Left\n");

			STEPPER_move_stwt(STEPPER_BOTH,
					STEPPER_FWD, 200, 150, 400, STEPPER_BRK_OFF,	//Left
					STEPPER_FWD, 200, 150, 400, STEPPER_BRK_OFF);	//Right
			//TMRSRVC_delay(500);
			go2Angle(90);
			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;
		}else if((frontIR > ICT) && (rightIR > ICT)){
			LCD_clear();
			LCD_printf("Right Follow\n");
			LCD_printf("Lack of Wall\n");
			LCD_printf("Turning Right\n");

			STEPPER_move_rn(STEPPER_BOTH,
					STEPPER_FWD, 150, 400,	//Left
					STEPPER_FWD, 150, 400);	//Right
			TMRSRVC_delay(500);
			rightIR = getRightIR();
			if ((frontIR > ICT) && (rightIR > ICT)){
				go2Angle(90);
				STEPPER_move_stwt(STEPPER_BOTH,
						STEPPER_FWD, 200, 150, 400, STEPPER_BRK_OFF,	//Left
						STEPPER_FWD, 200, 150, 400, STEPPER_BRK_OFF);	//Right
				rightIR = getRightIR();
				while(rightIR > ICT){
					TMRSRVC_delay(100);
					rightIR = getRightIR();
				}
				LP = 0;
				RP = 0;
				LI = 0;
				RI = 0;	
			}
		}
	}
}

void leftStepFollow(void){
	char lowerLimit = 4.75;
	char higherLimit = 5.25;
	char ICT = 12;
	float LP, RP, LWS, RWS, frontIR, rightIR, leftIR;
	float oLWS = 0;
	float oRWS = 0;
	float LI = 0;
	float RI = 0;
	char base = 120;
	char KP = 1.5;
	char KI = 0.75;
	char KD = 0;

	while(1){
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		if((frontIR > ICT) && (leftIR < ICT)){
			if (leftIR < lowerLimit){
				LCD_clear();
				LCD_printf("Left Follow\n");
				LCD_printf("Inside Target\n");
				LCD_printf("Range\n");

				LP = lowerLimit - leftIR;
				RP = 0;
				LI = LI++;
				RI = 0;
			}else if(leftIR > higherLimit){
				LCD_clear();
				LCD_printf("Left Follow\n");
				LCD_printf("Outside Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = leftIR - higherLimit;
				LI = 0;
				RI = RI++;
			}else{
				LCD_clear();
				LCD_printf("Left Follow\n");
				LCD_printf("At Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = 0;
				LI = 0;
				RI = 0;
			}

			LWS = KP*LP + KI*LI + base;
			RWS = KP*RP + KI*RI + base;
			if (oLWS == 0){
				oLWS = LWS;
				oRWS = RWS;
			}
			LWS = LWS + KD*(oLWS-LWS);
			RWS = RWS + KD*(oRWS-RWS);

			// Forward Movement
			STEPPER_move_stwt(STEPPER_BOTH,
					STEPPER_FWD, 200, LWS, 400, STEPPER_BRK_OFF,	//Left
					STEPPER_FWD, 200, RWS, 400, STEPPER_BRK_OFF);	//Right

			oLWS = LWS;
			oRWS = RWS;

		}else if((frontIR < ICT) && (leftIR < ICT)){
			LCD_clear();
			LCD_printf("Left Follow\n");
			LCD_printf("Wall in Front\n");
			LCD_printf("Turning Right\n");

			STEPPER_move_rn(STEPPER_BOTH,
					STEPPER_FWD, 150, 400,	//Left
					STEPPER_FWD, 150, 400);	//Right
			TMRSRVC_delay(500);
			go2ContAngle(90, 100);
			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;	
		}else if((frontIR > ICT) && (leftIR > ICT)){
			LCD_clear();
			LCD_printf("Left Follow\n");
			LCD_printf("Lack of Wall\n");
			LCD_printf("Turning Left\n");

			STEPPER_move_stwt(STEPPER_BOTH,
					STEPPER_FWD, 200, 150, 400, STEPPER_BRK_OFF,	//Left
					STEPPER_FWD, 200, 150, 400, STEPPER_BRK_OFF);	//Right
			TMRSRVC_delay(500);
			leftIR = getLeftIR();
			if ((frontIR > ICT) && (leftIR > ICT)){
				go2ContAngle(90);
				STEPPER_move_stwt(STEPPER_BOTH,
						STEPPER_FWD, 200, 150, 400, STEPPER_BRK_OFF,	//Left
						STEPPER_FWD, 200, 150, 400, STEPPER_BRK_OFF);	//Right
				leftIR = getLeftIR();
				while(leftIR > ICT){
					TMRSRVC_delay(100);
					leftIR = getLeftIR();
				}
				LP = 0;
				RP = 0;
				LI = 0;
				RI = 0;	
			}
		}
	}
}

void centerStepFollow(void){
	char tollerance_band = 0;
	float LP, RP, LWS, RWS, frontIR, rightIR, leftIR, avrageIR;
	float oLWS = 0;
	float oRWS = 0;
	float LI = 0;
	float RI = 0;
	char base = 120;
	char KP = 1.5;
	char KI = 0.85;
	char ICT = 12;
	char KD = 0;

	rightIR = getRightIR();
	leftIR = getLeftIR();
	while ((leftIR < ICT) && (rightIR < ICT)){
		rightIR = getRightIR();
		leftIR = getLeftIR();
		avrageIR = (rightIR + leftIR)/2;
		if ((rightIR - avrageIR) > tollerance_band){
			//means left of center
			LCD_clear();
			LCD_printf("Center Follow\n");
			LCD_printf("Left of\n");
			LCD_printf("Center\n");

			LP = rightIR - avrageIR;
			RP = 0;
			LI = LI++;
			RI = 0;
		} else if ((avrageIR - rightIR) > (tollerance_band)) {
			//means right of center
			LCD_clear();
			LCD_printf("Center Follow\n");
			LCD_printf("Right of\n");
			LCD_printf("Center\n");

			LP = 0;
			RP = leftIR - avrageIR;
			LI = 0;
			RI = RI++;
		} else {
			//means center of center
			LCD_clear();
			LCD_printf("I shall\n");
			LCD_printf("fear no\n");
			LCD_printf("evil\n");

			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;
		}
		LWS = KP*LP + KI*LI + KD*oLWS + base;
		RWS = KP*RP + KI*RI + KD*oRWS + base;
		if (oLWS == 0){
			oLWS = LWS;
			oRWS = RWS;
		}
		LWS = LWS + KD*(oLWS-LWS);
		RWS = RWS + KD*(oRWS-RWS);

		// Forward Movement
		STEPPER_move_stwt(STEPPER_BOTH,
				STEPPER_FWD, 200, LWS, 400, STEPPER_BRK_OFF	//Left
				STEPPER_FWD, 200, RWS, 400, STEPPER_BRK_OFF);	//Right

		oLWS = LWS;
		oRWS = RWS;
	}	
}