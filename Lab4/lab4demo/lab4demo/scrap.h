
void go2Goal(signed char x, signed char y){
	float angle, deltax, deltay, frontIR, rightIR, leftIR, leftFrontIR, rightFrontIR;
	int deltaTheta, theta, prevAngle;
	char goal = 0;
	x = x*12;
	y = y*12;
	
	deltax = x - xo;
	deltay = y - yo;
	
	theta = atan2(deltay,deltax) * (180/M_PI);
	deltaTheta = theta - thetao;
	
	// Calculating the length of the vector.
	distance = sqrt((deltax*deltax)+(deltay*deltay)); // this is the main vector
	
	// Converting it into steps.
	steps = distance/0.108;
	
	// Call for go to angle function.
	go2Angle(deltaTheta);
	// Stores the previous angle
	prevAngle = deltaTheta;
	
	while(goal != 1){
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		
		if(frontIR < 6){
			go2Angle(45);
			leftFrontIR = getFrontIR();
			go2Angle(-90);
			rightFrontIR = getFrontIR();
			go2Angle(45);
			
			if(leftFrontIR > rightFrontIR){
				// Turn left and follow right wall
			}else{
				//Turn right and follow left wall.
			}
			
		}else{
		
		}
	}
	
}