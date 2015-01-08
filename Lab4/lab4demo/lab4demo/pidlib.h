float pid(float frontIR, float rightIR, float leftIR){
	char FIC, RIC, LIC;
	char ICT = 9;
	//char higherLimit = 6;
	/*if(!(frontIR < ICT) && rightIR < ICT){
		rightFollow(frontIR,rightIR,leftIR);
	}*/
	
	return rightWheel, leftWheel;
}

void rightFollow(float frontIR, float rightIR, float leftIR){
	char lowerLimit = 4;
	char higherLimit = 6;
	char ICT = 9;
	float LP, RP, LI, RI, LWS, RWS;
	char base = 100;
	char KP = 1;
	char KI = 1;
	if(!(frontIR < ICT) && (rightIR < ICT)){
		if (rightIR < lowerLimit){
			LP = 0;
			RP = lowerLimit - rightIR;
			LI = 0;
			RI = RI++;
		}else if(rightIR > higherLimit){
			LP = rightIR - higherLimit;
			RP = 0;
			LI = LI++;
			RI = 0;
		}else{
			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;
		}
		
		LWS = KP*LP + KI*LI + base;
		RWS = KP*RP + KI*RI + base;
		
		// Forward Movement
		STEPPER_move_rn(STEPPER_BOTH,
			STEPPER_FWD, LWS, 400,	//Left
			STEPPER_FWD, RWS, 400);	//Right
		
	}else if(frontIR < ICT){
		TMRSRVC_delay(2000);
		go2Angle(90);
	}else if(!(rightIR < ICT)){
		TMRSRVC_delay(2000);
		go2Angle(-90);
		Forward_Move();
		while(!(rightIR < ICT)){
			TMRSRVC_delay(100);
		}
	}
	
}

void leftFollow(float frontIR, float rightIR, float leftIR){
	char lowerLimit = 4;
	char higherLimit = 6;
	char ICT = 9;
	float LP, RP, LI, RI, LWS, RWS;
	char base = 100;
	char KP = 1;
	char KI = 1;
	if(!(frontIR < ICT) && (leftIR < ICT)){
		if (leftIR < lowerLimit){
			LP = lowerLimit - leftIR;
			RP = 0;
			LI = LI++;
			RI = 0;
		}else if(leftIR > higherLimit){
			LP = 0;
			RP = leftIR - higherLimit;
			LI = 0;
			RI = RI++;
		}else{
			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;
		}
		
		LWS = KP*LP + KI*LI + base;
		RWS = KP*RP + KI*RI + base;
		
		// Forward Movement
		STEPPER_move_rn(STEPPER_BOTH,
			STEPPER_FWD, LWS, 400,	//Left
			STEPPER_FWD, RWS, 400);	//Right
		
	}else if(frontIR < ICT){
		TMRSRVC_delay(2000);
		go2Angle(-90);
	}else if(!(leftIR < ICT)){
		TMRSRVC_delay(2000);
		go2Angle(90);
		Forward_Move();
		while(!(leftIR < ICT)){
			TMRSRVC_delay(100);
		}
	}
	
}
void leftFollow(float frontIR, float rightIR, float leftIR){
	char lowerLimit = 4;
	char higherLimit = 6;
	char ICT = 9;
	float LP, RP, LI, RI, LWS, RWS;
	char base = 100;
	char KP = 1;
	char KI = 1;
	if(!(frontIR < ICT) && (leftIR < ICT)){
		if (leftIR < lowerLimit){
			LP = lowerLimit - leftIR;
			RP = 0;
			LI = LI++;
			RI = 0;
		}else if(leftIR > higherLimit){
			LP = 0;
			RP = leftIR - higherLimit;
			LI = 0;
			RI = RI++;
		}else{
			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;
		}
		
		LWS = KP*LP + KI*LI + base;
		RWS = KP*RP + KI*RI + base;
		
		// Forward Movement
		STEPPER_move_rn(STEPPER_BOTH,
			STEPPER_FWD, LWS, 400,	//Left
			STEPPER_FWD, RWS, 400);	//Right
		
	}else if(frontIR < ICT){
		TMRSRVC_delay(2000);
		go2Angle(-90);
	}else if(!(leftIR < ICT)){
		TMRSRVC_delay(2000);
		go2Angle(90);
		Forward_Move();
		while(!(leftIR < ICT)){
			TMRSRVC_delay(100);
		}
	}
	
}
