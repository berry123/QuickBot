
void go2Goal(signed char x, signed char y){
	float deltax, deltay, frontIR, rightIR, leftIR, targetX, targetY;
	int currAngle;
	short stepSize = 100;
	char goal = 0;
	x = x*12;
	y = y*12;
	char tollarance = 0.25;
	
	deltax = x - xo;
	deltay = y - yo;
	targetX = deltax;
	targetY = deltay;
	currAngle = 0;
	
	//theta = atan2(deltay,deltax) * (180/M_PI);
	//deltaTheta = theta - thetao;
	
	// Calculating the length of the vector.
	//distance = sqrt((deltax*deltax)+(deltay*deltay)); // this is the main vector
	
	// Converting it into steps.
	//steps = distance/0.108;
	
	// Call for go to angle function.
	//go2Angle(deltaTheta);
	// Stores the previous angle
	//orignalAngle = deltaTheta;
	
	while(goal == 0){ // Condition where the goal is not met.
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		// Remember to use: currAngle = currAngle + originalAngle;
		
		if(frontIR > 6){
			moveForward(stepSize,200);
			
			if(currAngle != 0 || currAngle != 360 || currAngle != -360 || currAngle != 180 || currAngle != -180){
				// Working on the Y axis:
				if(currAngle > 0){// Pointing towards the goal
					deltay = deltay - stepSize*0.108;
				}else{ // Pointing away from the goal.
					deltay = deltay + stepSize*0.108;
				}
				
			}else{
				// Working on the X axis assuming its towards 0 degrees:
				if(currAngle >= 0){// Pointing towards goal
					deltax = deltax - stepSize*0.108;
				}else{// Pointing away from goal.
					deltax = deltax + stepSize*0.108;
				}
				
			}
			
		}else{
			if(rightIR < leftIR){
				if(deltay >= 0){
					currAngle = currAngle + 90;
					go2Angle(currAngle);
					/*LCD_clear();
					LCD_printf("%f", deltax);
					TMRSRVC_delay(2000);*/
					rightStepFollow(&deltax, &deltay, &currAngle, targetX, targetY);
				}else{
					currAngle = currAngle - 90;
					go2Angle(currAngle);
					/*LCD_clear();
					LCD_printf("%f", deltax);
					TMRSRVC_delay(2000);*/
					leftStepFollow(&deltax, &deltay, &currAngle, targetX, targetY);
				}
			}else{
				if(deltay >= 0){
					currAngle = currAngle - 90;
					go2Angle(currAngle);
					/*LCD_clear();
					LCD_printf("%f", deltax);
					TMRSRVC_delay(2000);*/
					leftStepFollow(&deltax, &deltay, &currAngle, targetX, targetY);
				}else{
					currAngle = currAngle + 90;
					go2Angle(currAngle);
					/*LCD_clear();
					LCD_printf("%f", deltax);
					TMRSRVC_delay(2000);*/
					rightStepFollow(&deltax, &deltay, &currAngle, targetX, targetY);
				}
			}
		}
		
		if((deltax >= (targetX-tollarance)) && (deltax <= (targetX+tollarance)) && deltay >= (targetY-tollarance)) && (deltay <= (targetY+tollarance))){ // Might need to set a tolerance
			goal = 1;
			LCD_clear();
			LCD_printf("Reached goal mofo!... not?");
			TMRSRVC_delay(5000);
		}
	}
	
}