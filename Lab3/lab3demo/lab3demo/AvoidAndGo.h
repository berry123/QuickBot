void AvoidAndGo(unsigned char TarX, unsigned char TarY){
	#define ResetSpeed 100	
	#define AngleThresh 3
	#define ItterationTiming 0.05
	#define WheelBase 8.25
	#define Tollerance 2

	char oldRS = 100;
	char oldLS = 100;
	char Thresh = 5;
	char frontIR;
	char rightIR;
	char leftIR;
	char RightSpeed = ResetSpeed;
	char LeftSpeed = ResetSpeed;
	char CurX = 0;
	char CurY = 0;
	char CurTheta = atan2(TarY,TarX);
	char DeltaX;
	char DeltaY;
	char DeltaTheta;
	char TarTheta;
	char RightDistance;
	char LeftDistance;
	char Distance;
	char XDistance;
	char YDistance;

	while (1){
		frontIR = getFrontIR();
		rightIR = getRightIR();
		leftIR = getLeftIR();
		DeltaLeftSensor = leftIR - oldLS;
		DeltaRightSensor = rightIR - oldRS;

		if ((CurX > (TarX - Tollerance)) && (CurX < (TarX + Tollerance)) && (CurY > (TarY - Tollerance)) && (CurY < (TarY + Tollerance))){
			//Stay! Good Boy!
			}
		else if (frontIR < Thresh) {
			LeftSpeed++;
			RightSpeed--;
			}
		else if ((DeltaLeftSensor > 0) && (leftIR < Thresh){
			LeftSpeed++;
			}
		else if ((DeltaRightSensor > 0) && (rightIR < Thresh){
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
				RightSpeed = ResetSpeed;
				LeftSpeed = ResetSpeed;
				}
			}
		oldLS = leftIR;
		oldRS = rightIR;
		RightDistance = RightSpeed*ItterationTiming;
		LeftDistance = LeftSpeed*ItterationTiming;
		Distance = (RightDistance + LeftDistance)/2;
		CurTheta = CurTheta - atan2(LeftSpeed-RightSpeed,WheelBase);
		XDistance = cos(CurTheta)*Distance;
		YDistance = sin(CurTheta)*Distance;
		CurX = CurX + XDistance;
		CurY = CurY + YDistance;
		}
