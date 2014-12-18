
void AvoidAndGo(signed char TarX, signed char TarY){

	double AngleThresh = 3;
	float ItterationTiming = 0.05;
	float WheelBase = 8.25;
	char Tollerance = 3;
	float Steps2DistanceConversionFactor = 0.108;
	float oldRS = 100;
	float oldLS = 100;
	char Thresh = 7;
	char sideThresh = 5;
	float frontIR;
	float rightIR;
	float leftIR;
	short RightSpeed = 100;
	short LeftSpeed = 100;
	float CurX = 0;
	float CurY = 0;
	double CurTheta = atan2(TarY,TarX);
	float DeltaX;
	float DeltaY;
	double DeltaTheta;
	double TarTheta;
	float RightDistance;
	float LeftDistance;
	float Distance;
	float XDistance;
	float YDistance;
	float DeltaRightSensor;
	float DeltaLeftSensor;
	char indicator = 0;

	while (CurX < TarX && CurY < TarY){
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		DeltaLeftSensor = leftIR - oldLS;
		DeltaRightSensor = rightIR - oldRS;

		if ((CurX > (TarX - Tollerance)) && (CurX < (TarX + Tollerance)) && (CurY > (TarY - Tollerance)) && (CurY < (TarY + Tollerance))){
			//Stay! Good Boy!
			STEPPER_stop(STEPPER_BOTH, STEPPER_BRK_OFF);
		}else if (frontIR < Thresh) {
			indicator = 1;
		}else if ((DeltaLeftSensor > 0) && (leftIR < sideThresh)){
			LeftSpeed = LeftSpeed + 15;
			RightSpeed = RightSpeed - 15;
		}else if ((DeltaRightSensor > 0) && (rightIR < sideThresh)){
			RightSpeed = RightSpeed + 15;
			LeftSpeed = LeftSpeed - 15;
		}else{
			DeltaX = TarX - CurX;
			DeltaY = TarY - CurY;
			TarTheta = atan2(DeltaY,DeltaX);
			DeltaTheta = TarTheta - CurTheta;
			if (DeltaTheta > AngleThresh){
				LeftSpeed = LeftSpeed + 15;
			}else if (DeltaTheta < -AngleThresh){
				RightSpeed = RightSpeed + 15;
			}else{
				RightSpeed = 100;
				LeftSpeed = 100;
			}
		}
		// Forward Movement		
		if (indicator == 1){
			STEPPER_move_rn(STEPPER_BOTH,
				STEPPER_FWD, 200, 400,	//Left
				STEPPER_REV, 200, 400);	//Right
			LeftSpeed = 200;
			RightSpeed = -200;
			}
		else {
			STEPPER_move_rn(STEPPER_BOTH,
				STEPPER_FWD, LeftSpeed, 400,	//Left
				STEPPER_FWD, RightSpeed, 400);	//Right
			}
		TMRSRVC_delay(50); //50 mSec duration
		oldLS = leftIR;
		oldRS = rightIR;
		RightDistance = RightSpeed*ItterationTiming*Steps2DistanceConversionFactor;
		LeftDistance = LeftSpeed*ItterationTiming*Steps2DistanceConversionFactor;
		Distance = (RightDistance + LeftDistance)/2;
		CurTheta = CurTheta + atan2(LeftSpeed-RightSpeed,WheelBase);
		XDistance = cos(CurTheta)*Distance;
		YDistance = sin(CurTheta)*Distance;
		CurX = CurX + XDistance;
		CurY = CurY + YDistance;
		LCD_clear();
		LCD_printf("%f\n%f", CurX, CurY);
		if (indicator == 1){
			RightSpeed = 100;
			LeftSpeed = 100;
			indicator =0;
			}
	}
}
