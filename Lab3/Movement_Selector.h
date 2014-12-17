void Movement_Selector_Excecutor(signed char FSS, signed char BSS, signed char RSS, signed char LSS, signed char TS){
/* where:
	FSS = Forward Sensor State
	BSS = Backward Sensor State
	RSS = Right Sensor State
	LSS = Left Sensor State
	TS = Triggered Sensors, which is the total number of sensors which have exceded the IR sensor threashhold
*/

	switch(TS){
		case 1: // If only one sensor is triggered
			if ((FSS == 1) && (BSS == 0) && (RSS == 0) &&(LSS == 0)){
				Backward_Move();
				}
			else if ((FSS == 0) && (BSS == 1) && (RSS == 0) &&(LSS == 0)){
				Forward_Move();
				}
			else if ((FSS == 0) && (BSS == 0) && (RSS == 0) &&(LSS == 1)){
				Soft_Forward_Right();
				}
			else {
				Soft_Forward_Left();
				}
			break;
		case 2: // If two sensors are triggered
			if ((FSS == 1) && (BSS == 0) && (RSS == 0) &&(LSS == 1)){
				Soft_Backward_Right();
				}
			else if ((FSS == 1) && (BSS == 0) && (RSS == 1) &&(LSS == 0)){
				Soft_Backward_Left();;
				}
			else if ((FSS == 0) && (BSS == 1) && (RSS == 0) &&(LSS == 1)){
				Soft_Forward_Right();
				}
			else if ((FSS == 0) && (BSS == 1) && (RSS == 1) &&(LSS == 0)){
				Soft_Forward_Left();
				}
			else if ((FSS == 1) && (BSS == 1) && (RSS == 0) &&(LSS == 0)){
				Hard_Right();
				}
			else {
				Forward_Move();
				}
			
			break;
		case 3: // If three sensors are triggered
			if ((FSS == 1) && (BSS == 1) && (RSS == 0) &&(LSS == 1)){
				Hard_Right();
				}
			else if ((FSS == 1) && (BSS == 1) && (RSS == 1) &&(LSS == 0)){
				Hard_Left();
				}
			else if ((FSS == 1) && (BSS == 0) && (RSS == 1) &&(LSS == 1)){
				Backward_Move();
				}
			else {
				Forward_Move();
				}
			
			break;
		case 4: // If all four sensors are triggered
			Cry();
			break;
		default: // If none of the sensors are triggered
			// just stay and chill!
			break;
		}
	}
