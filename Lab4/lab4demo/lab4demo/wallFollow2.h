void rightFollow(void){
	char lowerLimit = 4.75;
	char higherLimit = 5.25;
	char ICT = 12;
	float LP, RP, LI, RI, LWS, RWS, frontIR, rightIR, leftIR;
	char base = 120;
	char KP = 20;
	char KI = 2;
	while(1){
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		if(!(frontIR < ICT) && (rightIR < ICT)){
			if (rightIR < lowerLimit){
				LCD_clear();
				LCD_printf("Inside Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = lowerLimit - rightIR;
				LI = 0;
				RI = RI++;
			}else if(rightIR > higherLimit){
				LCD_clear();
				LCD_printf("Outside Target\n");
				LCD_printf("Range\n");

				LP = rightIR - higherLimit;
				RP = 0;
				LI = LI++;
				RI = 0;
			}else{
				LCD_clear();
				LCD_printf("At Target\n");
				LCD_printf("Range\n");

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
		
		}else if((frontIR < ICT) && (rightIR < ICT)){
			LCD_clear();
			LCD_printf("Wall in Front\n");
			LCD_printf("Turning Left\n");

			TMRSRVC_delay(2000);
			STEPPER_move_rn(STEPPER_BOTH,
					STEPPER_REV, 200, 400,	//Left
					STEPPER_FWD, 200, 400);	//Right
			TMRSRVC_delay(500);
			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;
		}else if(!(frontIR < ICT) && !(rightIR < ICT)){
			LCD_clear();
			LCD_printf("Lack of Wall\n");
			LCD_printf("Turning Right\n");

			TMRSRVC_delay(2000);
			rightIR = getRightIR();
			if (!(frontIR < ICT) && !(rightIR < ICT)){
				STEPPER_move_rn(STEPPER_BOTH,
						STEPPER_FWD, 200, 400,	//Left
						STEPPER_REV, 200, 400);	//Right
				TMRSRVC_delay(500);
				STEPPER_move_rn(STEPPER_BOTH,
						STEPPER_FWD, 200, 400,	//Left
						STEPPER_FWD, 200, 400);	//Right
				while(!(rightIR < ICT)){
					rightIR = getRightIR();
					TMRSRVC_delay(100);
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
	char lowerLimit = 4.75;
	char higherLimit = 5.25;
	char ICT = 12;
	float LP, RP, LI, RI, LWS, RWS, frontIR, rightIR, leftIR;
	char base = 120;
	char KP = 20;
	char KI = 2;
	while(1){
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		if(!(frontIR < ICT) && (leftIR < ICT)){
			if (leftIR < lowerLimit){
				LCD_clear();
				LCD_printf("Inside Target\n");
				LCD_printf("Range\n");

				LP = lowerLimit - leftIR;
				RP = 0;
				LI = LI++;
				RI = 0;
			}else if(leftIR > higherLimit){
				LCD_clear();
				LCD_printf("Outside Target\n");
				LCD_printf("Range\n");

				LP = 0;
				RP = leftIR - higherLimit;
				LI = 0;
				RI = RI++;
			}else{
				LCD_clear();
				LCD_printf("At Target\n");
				LCD_printf("Range\n");

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
		
		}else if((frontIR < ICT) && (leftIR < ICT)){
			LCD_clear();
			LCD_printf("Wall in Front\n");
			LCD_printf("Turning Right\n");

			TMRSRVC_delay(2000);
			STEPPER_move_rn(STEPPER_BOTH,
					STEPPER_FWD, 200, 400,	//Left
					STEPPER_REV, 200, 400);	//Right
			TMRSRVC_delay(500);
			LP = 0;
			RP = 0;
			LI = 0;
			RI = 0;	
		}else if(!(frontIR < ICT) && !(leftIR < ICT)){
			LCD_clear();
			LCD_printf("Lack of Wall\n");
			LCD_printf("Turning Left\n");

			TMRSRVC_delay(2000);
			leftIR = getLeftIR();
			if (!(frontIR < ICT) && !(leftIR < ICT)){
				STEPPER_move_rn(STEPPER_BOTH,
						STEPPER_REV, 200, 400,	//Left
						STEPPER_FWD, 200, 400);	//Right
				TMRSRVC_delay(500);
				STEPPER_move_rn(STEPPER_BOTH,
						STEPPER_FWD, 200, 400,	//Left
						STEPPER_FWD, 200, 400);	//Right
				while(!(leftIR < ICT)){
					leftIR = getLeftIR();
					TMRSRVC_delay(100);
				}
				LP = 0;
				RP = 0;
				LI = 0;
				RI = 0;	
			}
		}
	}
}
