void wallFollower(){
	float frontIR, rightIR, leftIR;
	char lowerLimit = 4;
	char higherLimit = 6;
	char FOL, BTW, SLR, SLL, FRD, WTL;
	
	frontIR = getFrontIR();
	rightIR = getRightIR();
	leftIR = getLeftIR();
	
	WTL = (rightIR >= lowerLimit || rightIR <= higherLimit|| leftIR >= lowerLimit || leftIR <= higherLimit); // within limits of either sides of the walls
	BTW = ((rightIR >= lowerLimit && leftIR >= lowerLimit) || (rightIR <= higherLimit && leftIR <= higherLimit) || (rightIR >= lowerLimit && leftIR <= higherLimit) || (rightIR <= higherLimit && leftIR >= lowerLimit));
	FRD = (frontIR <= higherLimit);
	SLR = (rightIR > higherLimit || leftIR < lowerLimit);
	SLL = (leftIR > higherLimit || rightIR < lowerLimit);
	
	FOL = WTL + BTW;

	if(FRD > 0){
		//
		// Stops the robot and decides where to turn to.
		//
	}else{
		if(SLR > 0){
		//
		// Slight Right turn to follow wall
		//
		}else if(SLL > 0){
			//
			// Slight Left turn to follow wall
			//
		}else{
			if(WTL > 0){
				//
				// Move forward
				//
			}else if(BTW > 0){
				//
				// Move forward keeping in the center.
				//
			}
		}
	}
	
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
				//
				// Turn 90 degrees and stick to the wall on the right
				//
				}
			else if ((FSS == 0) && (RSS == 0) &&(LSS == 1)){
				//
				// Stick to the Left wall
				//
				}
			else {
				//
				// Stick to the right wall
				//
				}
			break;
		case 2: // If two sensors are triggered
			if ((FSS == 1) && (RSS == 0) &&(LSS == 1)){
				//
				// Turn 90 degrees
				// Stick to the wall on the left
				//
				}
			else if ((FSS == 1) && (RSS == 1) &&(LSS == 0)){
				//
				// Turn 90 degrees
				// Stick to the wall on the right
				//
				}
			else {
				//
				// Center wall following
				//
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