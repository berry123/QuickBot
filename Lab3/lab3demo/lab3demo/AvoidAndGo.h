
//#define ResetSpeed 100
//#define AngleThresh 3
//#define ItterationTiming 0.05
//#define WheelBase 8.25
//#define Tollerance 2
//#define Steps2DistanceConversionFactor 0.108


void AvoidAndGo(signed char TarX, signed char TarY, float frontIR, float rightIR, float leftIR){

	float AngleThresh = 3;
	float ItterationTiming = 0.05;
	float WheelBase = 8.25;
	char Tollerance = 2;
	float Steps2DistanceConversionFactor = 0.108;
	float oldRS = 100;
	float oldLS = 100;
	float Thresh = 5;
	//float frontIR;
	//float rightIR;
	//float leftIR;
	short RightSpeed = 100;
	short LeftSpeed = 100;
	char CurX = 0;
	char CurY = 0;
	float CurTheta = atan2(TarY,TarX);
	float DeltaX;
	float DeltaY;
	float DeltaTheta;
	float TarTheta;
	float RightDistance;
	float LeftDistance;
	float Distance;
	float XDistance;
	float YDistance;
	float DeltaRightSensor;
	float DeltaLeftSensor;

	while (1){
		//frontIR = getFrontIR();
		//rightIR = getRightIR();
		//leftIR = getLeftIR();
		DeltaLeftSensor = leftIR - oldLS;
		DeltaRightSensor = rightIR - oldRS;

		if ((CurX > (TarX - Tollerance)) && (CurX < (TarX + Tollerance)) && (CurY > (TarY - Tollerance)) && (CurY < (TarY + Tollerance))){
			//Stay! Good Boy!
			}
		else if (frontIR < Thresh) {
			LeftSpeed++;
			RightSpeed--;
			}
		else if ((DeltaLeftSensor > 0) && (leftIR < Thresh)){
			LeftSpeed++;
			}
		else if ((DeltaRightSensor > 0) && (rightIR < Thresh)){
			RightSpeed++;
			}
		else  {
			DeltaX = TarX - CurX;
			DeltaY = TarY - CurY;
			TarTheta = atan2(DeltaY,DeltaX);
			DeltaTheta = TarTheta - CurTheta;
			if (DeltaTheta > AngleThresh){
				LeftSpeed++;
			}
			else if (DeltaTheta < -AngleThresh){
				RightSpeed++;
			}
			else {
				RightSpeed = 100;
				LeftSpeed = 100;
				}
			}
		// Forward Movement
		STEPPER_move_rn(STEPPER_BOTH,
			STEPPER_FWD, LeftSpeed, 400,	//Left
			STEPPER_FWD, RightSpeed, 400);	//Right
		TMRSRVC_delay(50); //50 mSec duration
		oldLS = leftIR;
		oldRS = rightIR;
		RightDistance = RightSpeed*ItterationTiming*Steps2DistanceConversionFactor;
		LeftDistance = LeftSpeed*ItterationTiming*Steps2DistanceConversionFactor;
		Distance = (RightDistance + LeftDistance)/2;
		CurTheta = CurTheta - atan2(LeftSpeed-RightSpeed,WheelBase);
		XDistance = cos(CurTheta)*Distance;
		YDistance = sin(CurTheta)*Distance;
		CurX = CurX + XDistance;
		CurY = CurY + YDistance;
		}
}
