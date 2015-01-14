void goes2goal(float Tar_X, float Tar_Y){
	float cur_X = 0;
	float cur_Y = 0;
	float delta_X, delta_Y;
	char x_or_y = 1;
	float tollarance = 3;
	float orientation = 0;
	float s_tol = 7;
	float frontIR, leftIR, rightIR;

	Tar_X = Tar_X*12;
	Tar_Y = Tar_Y*12;

	delta_X = Tar_X - cur_X;
	delta_Y = Tar_Y - cur_Y;

	while((delta_X <= tollarance) && (delta_X >= (-tollarance)) && (delta_Y <= tollarance) && (delta_Y >= (-tollarance))){
		frontIR = getFrontIR();
		if(frontIR < s_tol){
			leftIR = getLeftIR();
			rightIR = getRightIR();
			if(rightIR < leftIR){
				go2Angle(90); // + is left, - is right
				//Update Orientation
				orientation = orientation + 90;

				rightStepFollow(&cur_X, &cur_Y, &orientation, Tar_X, Tar_Y);
			} else {
				go2Angle(-90); // + is left, - is right
				//Update Orientation
				orientation = orientation - 90;
				
				leftStepFollow(&cur_X, &cur_Y, &orientation, Tar_X, Tar_Y);
			}

		} else { 
			pseudo_Stepper_Step(150, 150, 0.5);	// (Right Wheel Speed, Left Wheel Speed, Duration)			
			// Computations for position
			cur_X = cos(orientation)*(75*0.108) + cur_X;
			cur_Y = sin(orientation)*(75*0.108) + cur_Y;	
			//
		}
		delta_X = Tar_X - cur_X;
		delta_Y = Tar_Y - cur_Y;
	}
}