void goes2goal(float Tar_X, float Tar_Y){
	float cur_X = 0;
	float cur_Y = 0;
	float delta_X, delta_Y, tmp;
	char x_or_y = 1;
	float tollarance = 3.75;
	float Ytollarance = 4.5;
	float orientation = 0;
	float s_tol = 7;
	float frontIR, leftIR, rightIR;
	char flag = 0;

	Tar_X = Tar_X*12;
	Tar_Y = Tar_Y*12;

	delta_X = Tar_X - cur_X;
	delta_Y = Tar_Y - cur_Y;

	while((delta_X >= tollarance) || (delta_X <= (-tollarance)) || (delta_Y >= Ytollarance) || (delta_Y <= (-Ytollarance))){
		LCD_clear();
		LCD_printf("%f\n%f", delta_X, delta_Y);
		//TMRSRVC_delay(5000);*/
		frontIR = getFrontIR();
		if(frontIR < s_tol){
			leftIR = getLeftIR();
			rightIR = getRightIR();
			if(rightIR < leftIR){
				
				/*LCD_clear();
				LCD_printf("Right Follow\n");*/
				
				go2Angle(90); // + is left, - is right
				//Update Orientation
				orientation = orientation + 90;

				rightStepFollow(&cur_X, &cur_Y, &orientation, Tar_X, Tar_Y);
			} else {
				
				/*LCD_clear();
				LCD_printf("Left Follow\n");*/
				
				go2Angle(-90); // + is left, - is right
				//Update Orientation
				orientation = orientation - 90;
				
				leftStepFollow(&cur_X, &cur_Y, &orientation, Tar_X, Tar_Y);
			}
			/*count++;
			if(count==2){
				tmp = cur_Y;
				cur_Y = cur_X;
				cur_X = tmp;
			}*/

		} else { 

			/*LCD_clear();
			LCD_printf("Forward Move\n");*/
			
			if((delta_X <= tollarance) && (delta_X >= (-tollarance))){
				
				if(delta_Y > 0 && flag == 0){
					go2Angle(90);
					orientation = orientation + 90;
					flag = 1;
				}else if(delta_Y < 0 && flag == 0){
					go2Angle(-90);
					orientation = orientation - 90;
					flag = 1;
				}
				pseudo_Stepper_Step(150, 150, 0.5);	// (Right Wheel Speed, Left Wheel Speed, Duration)
				cur_Y = sin(orientation)*(75*0.108) + cur_Y;
			}else{
			
				pseudo_Stepper_Step(150, 150, 0.5);	// (Right Wheel Speed, Left Wheel Speed, Duration)			
				// Computations for position
				cur_X = cos(orientation)*(75*0.108) + cur_X;
				cur_Y = sin(orientation)*(75*0.108) + cur_Y;	
				//
			}
		}
		delta_X = Tar_X - cur_X;
		delta_Y = Tar_Y - cur_Y;
		
		
	}

	LCD_clear();
	LCD_printf("Loop Broke\n");

	TMRSRVC_delay(10000);
}