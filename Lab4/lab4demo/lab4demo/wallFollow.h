void wallFollower(){
	float frontIR, rightIR, leftIR;
	char lowerLimit = 4;
	char higherLimit = 6;
	char BTW, SLR, SLL, FRD, WTL;
	
	frontIR = getFrontIR();
	rightIR = getRightIR();
	leftIR = getLeftIR();
	
	WTL = (rightIR >= lowerLimit || rightIR <= higherLimit|| leftIR >= lowerLimit || leftIR <= higherLimit); // within limits of either sides of the walls
	/*BTW = (((rightIR >= lowerLimit && leftIR >= lowerLimit) && (rightIR <= higherLimit && leftIR <= higherLimit)) || 
		((rightIR >= lowerLimit && leftIR <= higherLimit) && (rightIR <= higherLimit && leftIR >= lowerLimit)) || 
		((rightIR >= lowerLimit && leftIR >= lowerLimit) && (rightIR >= lowerLimit && leftIR <= higherLimit)) || 
		((rightIR >= lowerLimit && leftIR >= lowerLimit) && (rightIR >= lowerLimit && leftIR <= higherLimit)) || 
		());*/
	//FRD = (frontIR <= higherLimit);
	SLR = (rightIR > higherLimit || leftIR < lowerLimit);
	SLL = (leftIR > higherLimit || rightIR < lowerLimit);

	if(frontIR > higherLimit){
		if(WTL > 0){
			STEPPER_move_rn(STEPPER_BOTH,
				STEPPER_FWD, 200, 400,	//Left
				STEPPER_FWD, 200, 400);	//Right
				
			TMRSRVC_delay(1000);
			
			LCD_clear();
			LCD_printf("Is following a wall");
							
		}else{
			if(SLR > 0){
				STEPPER_move_rn(STEPPER_BOTH,
					STEPPER_FWD, 200, 400,	//Left
					STEPPER_FWD, 100, 400);	//Right
					
				TMRSRVC_delay(500);
				
				LCD_clear();
				LCD_printf("Slight right");

			}else if(SLL > 0){
				STEPPER_move_rn(STEPPER_BOTH,
					STEPPER_FWD, 100, 400,	//Left
					STEPPER_FWD, 200, 400);	//Right
					
				TMRSRVC_delay(500);
				
				LCD_clear();
				LCD_printf("Slight Left");
			}
		}
	
	}else{
		STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
	}
	
	/*while(FRD == 0){
		if(SLR > 0){
			Soft_Forward_Right();
		}else if(SLL > 0){
			Soft_Forward_Left();
		}else{
			if(WTL > 0){
				Forward_Move();
			}else if(BTW > 0){
				// Move forward keeping in the center.
				if(rightIR > leftIR){
					go2Angle(-18);
					Forward_Move();
				}else{
					go2Angle(18);
					Forward_Move();
				}
			}
		}
	}*/
	
}

void wallFinder(){
	float frontIR, rightIR, leftIR;
	char sensLimit = 6;
	char TS, FSS, RSS, LSS;
	
	/*while(getFrontIR() > sensLimit || getRightIR() > sensLimit || getLeftIR() > sensLimit){
		Random_Wanderer();
	}*/
	
	frontIR = getFrontIR();
	rightIR = getRightIR();
	leftIR = getLeftIR();
	
	FSS = (sensLimit > frontIR);
	//BSS = (sensLimit > backIR);
	RSS = (sensLimit > rightIR);
	LSS = (sensLimit > leftIR);
	
	TS = FSS + RSS + LSS;
	
	switch(TS){
		case 1: // If only one sensor is triggered
			if ((FSS == 1) && (RSS == 0) &&(LSS == 0)){
				go2Angle(-90); // Turns the robot to the right as default.
				wallFollower();
				
				}
			else if ((FSS == 0) && (RSS == 0) &&(LSS == 1)){
				wallFollower(); // Stick to the wall on the left.
				}
			else if ((FSS == 0) && (RSS == 1) && (LSS == 0)){
				wallFollower(); // Stick to the wall on the right.
				}
			break;
		case 2: // If two sensors are triggered
			if ((FSS == 1) && (RSS == 0) &&(LSS == 1)){
				go2Angle(90);
				wallFollower(); // Stick to the wall on  the left.
				}
			else if ((FSS == 1) && (RSS == 1) &&(LSS == 0)){
				go2Angle(-90);
				wallFollower(); // Stick to the wall on the right
				}
			else if ((FSS == 0) && (RSS == 1) && (LSS == 1)){
				wallFollower(); // Center wall following
				}
			
			break;
		case 3: // If three sensors are triggered
			if ((FSS == 1) && (RSS == 1) &&(LSS == 1)){
				Backward_Move();
				wallFinder();
				}
			/*else {
				Random_Wanderer();
				}*/
			
			break;
		default: // If none of the sensors are triggered
			Random_Wanderer();
			break;
		}
}