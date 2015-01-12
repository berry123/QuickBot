
void go2Goal(signed char x, signed char y){
	float angle, deltax, deltay, frontIR, rightIR, leftIR, leftFrontIR, rightFrontIR, distance, targetX, targetY, toGoalX, toGoalY;
	int deltaTheta, theta, originalAngle, currAngle;
	char goal = 0;
	x = x*12;
	y = y*12;
	
	deltax = x - xo;
	deltay = y - yo;
	targetX = deltax;
	targetY = deltaY;
	
	theta = atan2(deltay,deltax) * (180/M_PI);
	deltaTheta = theta - thetao;
	
	// Calculating the length of the vector.
	distance = sqrt((deltax*deltax)+(deltay*deltay)); // this is the main vector
	
	// Converting it into steps.
	steps = distance/0.108;
	
	// Call for go to angle function.
	go2Angle(deltaTheta);
	// Stores the previous angle
	orignalAngle = deltaTheta;
	
	while(goal == 0){ // Condition where the goal is not met.
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		// Remember to use: currAngle = currAngle + originalAngle;
		
		if(frontIR > 6){
			moveForward(100,200);
			
			if(currAngle != originalAngle){
				// Calculates estimation:
				deltax = deltax -(100*0.108)*sin(currAngle);
				deltay = deltay -(100*0.108)*cos(currAngle);
								
				if(deltax == 0 && deltay == 0){
					goal = 1;
				}
				
			}else{
				distance = distance - (100*0.108);
				deltax = distance*sin(currAngle);
				deltay = distance*cos(currAngle);
			}
			
		}else{
			toGoalX = targetX - deltax*sin(currAngle);
			toGoalY = targetY - deltay*cos(currAngle);
			
			if(toGoalX > (targetX/2)){
				if(toGoalY > (targetY/2)){
					// Turn oppsite direction to the target
					// Follow any of the walls towards the target.
				}else{
					// Turn towards the target.
					// Stick to any wall towards the target.
				}
			}else{
				if(toGoalY > (targetY/2)){
					// Turn towards the direction of the target
					// Follow any of the walls towards the target.
				}else{
					// Turn towards the direction of the target
					// Follow any of the walls towards the target and away from it.
				}
			}
			
		}
	}
	
}