float getLeftLight(void){
	float Light_Percentage, V_in;
	
	//Sensor stuff
	
	Light_Percentage = Light_Calculator(V_in)
	
	return Light_Percentage;
}

float getRightLight(void){
	float Light_Percentage, V_in;
		
		//Sensor stuff
		
		Light_Percentage = Light_Calculator(V_in)
		
		return Light_Percentage;	
}

float Light_Calculator(float V_in){
	float Light_Percentage;
	
	Light_Percentage = (V_in-1.667)*60
	
	return Light_Percentage;
}