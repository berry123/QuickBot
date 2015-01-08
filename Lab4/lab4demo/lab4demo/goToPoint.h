// goToPoint.h
/* This header contains the functions used for the go To Point task while avoiding obstacles.*/
// Alexandre van der Ven de Freitas
// Peter Richard Olejnik
// December 18, 2014


// Global variables:
signed char xo = 0;
signed char yo = 0;
short thetao = 0;

// Moves the robot forward for a given number of steps.
void moveForward(int steps, int speed){
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	// Moving both wheels forward.
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, steps, speed, 400, STEPPER_BRK_OFF,	//Left wheel
		STEPPER_FWD, steps, speed, 400, STEPPER_BRK_OFF);	//Right wheel
}

// Rotates the robot to the required functions.
void go2Angle(int angle){
	
	// If the angle is positive, rotate the robot in a certain angle that is converted in steps to the left.
	if (angle > 0){
		if (angle <= 180){
			sTurnLeft(angle, 400);
		}else if(angle > 180){
			angle = angle/2;
			sTurnLeft(angle, 400);
			sTurnLeft(angle, 400);
		}
	// If the angle is negative, rotate the robot in a certain angle that is converted in steps to the right.
	}else if(angle < 0){
		angle = angle * (-1); //Make the angle positive to calculate the amount of steps.
		if (angle <= 180){
			sTurnRight(angle, 400);
		}else if (angle > 180){
			angle = angle/2;
			sTurnRight(angle, 400);
			sTurnRight(angle, 400);
		}
	}else{
		// does nothing
	}
}

// Guides the robot to the desired input point.
void go2Point(signed char x, signed char y){ //input in feet
	float deltax, deltay, distance, steps, divSteps, frontIR, rightIR, leftIR;
	int theta, deltaTheta;
	char flag = 0;

	// Since the whole software was developed with an inches scale in mind, here the conversion to feet occurs.
	x = x*12;
	y = y*12;
	
	// Calculations:
	deltax = x - xo;
	deltay = y - yo;
	// Obtaining the theta in degrees since the function from math.h returns in radians.
	theta = atan2(deltay,deltax) * (180/M_PI);
	deltaTheta = theta - thetao;
	// This is for the sake of debugging:
	//LCD_clear();
	//LCD_printf("%d - %d = %d", theta, thetao, deltaTheta);
	//LCD_printf("x = %d, y = %d",x,y);
	
	// Calculating the length of the vector.
	distance = sqrt((deltax*deltax)+(deltay*deltay));
	
	// Converting it into steps.
	steps = distance/0.108;
	
	// Call for go to angle function.
	go2Angle(deltaTheta);
	TMRSRVC_delay(500); //0.5 seconds delay.
	
	// Divides the number of steps to be run by moveForward()
	divSteps = steps/20;
	
	// While the steps value is bigger than zero:
	while(steps>0){
		// Read the sensors
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		
		// If the front IR is reading values larger than 7 inches...
		if (frontIR > 7){
			// If the internal flag is 1...
			if (flag>0){
				// If either of the side IRs are reading values smaller than 10 inches...
				if(rightIR < 10 || leftIR < 10){
					moveForward(divSteps,200); // Move forward with the given number of fractioned steps
					steps = steps - divSteps; // Decrements the number of steps
					LCD_clear();
					LCD_printf("Side obstacle detected.");
					//LCD_clear();
				}else{ // If the sides are reading values larger than 10 inches...
					moveForward(200, 200); // Move forward a little to avoid the edge of the box.
					go2Angle(-90); // Turn -90 degrees
					TMRSRVC_delay(500);
					moveForward(250, 200); // Move forward for centralizing the path.
					go2Angle(90); // Turn 90 degrees
					flag = 0; // Changes flag back to zero.
				}
			}else{ // If the flag is zero...
				moveForward(divSteps, 200); // Move forward with the given number of fractioned steps
				steps = steps - divSteps; // Decrements the number of steps
			}
		}else{ // If the front IR reading is smaller than 7 inches...
			LCD_clear();
			LCD_printf("Front obstacle detected.");
			go2Angle(90); // Turn 90 degrees
			TMRSRVC_delay(500);
			moveForward(250, 200); // Move forward away from the box edge
			go2Angle(-90); // Turn -90 degrees
			moveForward(200, 200); // Move forward to align the side IR sensors with the box.
			flag = 1; // Flags to 1
		}
		LCD_clear();
		//LCD_printf("%f", steps);
	}
	// Updating the original values.
	xo = x;
	yo = y;
	thetao = theta;
}

// Given an angle and a speed, this function makes the robot turn/spin to the left.
void sTurnLeft(int angle, int speed){
	int steps;
	
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	steps = angle*130/90;
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_REV, steps, speed, 800, STEPPER_BRK_OFF,	//Left wheel
		STEPPER_FWD, steps, speed, 800, STEPPER_BRK_OFF);	//Right wheel
		
	STEPPER_close();
}

// Given an angle and a speed, this function makes the robot turn/spin to the right.
void sTurnRight(int angle, int speed){
	int steps;
	
	// Performs the same error detection procedure for the Stepper subsystem as it was performed with ATTINY.
	SUBSYS_OPENSTAT openStepper;
	
	// Stepper subsystem is opened.
	openStepper = STEPPER_open();
	
	// Displays an error message if the returned value for the opened stepper subsystem is unexpected.
	if (openStepper.state != SUBSYS_OPEN){
		LCD_printf("\nError when opening STEPPER subsystem!");
	}
	
	steps = angle*130/90;
	STEPPER_move_stwt(STEPPER_BOTH,
		STEPPER_FWD, steps, speed, 800, STEPPER_BRK_OFF,	//Left wheel
		STEPPER_REV, steps, speed, 800, STEPPER_BRK_OFF);	//Right wheel
		
	STEPPER_close();
}

void go2ContAngle(char angle, int speed){
	STEPPER_move_rn(STEPPER_BOTH,
		STEPPER_FWD, speed, 400,	//Left
		STEPPER_REV, speed, 400);	//Right
	TMRSRVC_delay(500);
	STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
}