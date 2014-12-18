
// IR Channels mapped to ADC inputs
#define IRRIGHT_CHAN ADC_CHAN3
#define IRLEFT_CHAN ADC_CHAN4
#define IRFRONT_CHAN ADC_CHAN7
#define IRBACK_CHAN ADC_CHAN5

// getLeftIR() converts ADC voltage to inches
float getLeftIR(){
	//float voltage;//IR range -0.4 to 5.3 V
	float distance;// (cm) 30 cm = 12 inches = 0.4 V
	float dist;//distance in inches
	ADC_SAMPLE adcsample;
	// Set the Voltage Reference first so VREF=5V.
	ADC_set_VREF( ADC_VREF_AVCC );
	// Set the channel we will sample from.
	ADC_set_channel( IRLEFT_CHAN );
	// Now sample it!
	adcsample = ADC_sample();
	//LCD_printf( "ADC: %i\n",adcsample);
	// Convert to meaningful voltage value.
	//voltage = adcsample * ( 5.0 / 1024 );
	// Convert to distance in cm
	distance = (2914/(adcsample+5.0))-1.0;
	//Convert distance to inches
	dist = distance*0.3937;
	return dist;
}

// getRightIR() converts ADC voltage to inches
float getRightIR(){
	//float voltage;//IR range -0.4 to 5.3 V
	float distance;// (cm) 30 cm = 12 inches = 0.4 V
	float dist;//distance in inches
	ADC_SAMPLE adcsample;
	// Set the Voltage Reference first so VREF=5V.
	ADC_set_VREF( ADC_VREF_AVCC );
	// Set the channel we will sample from.
	ADC_set_channel( IRRIGHT_CHAN );
	// Now sample it!
	adcsample = ADC_sample();
	// Convert to meaningful voltage value.
	//voltage = adcsample * ( 5.0 / 1024 );
	// Convert to distance in cm
	distance = (2914/(adcsample+5.0))-1.0;
	//Convert distance to inches
	dist = distance*0.3937;
	return dist;
}

// getFrontIR() simply sets the ADC to the Front IR sensor
// and returns the sampled voltage in inches. Short, nonblocking.
float getFrontIR(){
	//1 inch = 2.54 cm
	//1 cm = 0.3937 inches
	//float voltage;//IR range -0.4 to 5.3 V
	float distance;// (cm) 30 cm = 12 inches = 0.4 V
	float dist;//distance in inches
	ADC_SAMPLE adcsample;
	// Set the Voltage Reference first so VREF=5V.
	ADC_set_VREF( ADC_VREF_AVCC );
	// Set the channel we will sample from.
	ADC_set_channel(IRFRONT_CHAN);
	// Now sample it!
	adcsample = ADC_sample();
	// Convert to meaningful voltage value.
	//voltage = adcsample * ( 5.0 / 1024 );
	// Convert to distance in cm
	distance = (2914/(adcsample+5.0))-1.0;
	//Convert distance to inches
	dist = distance*0.3937;
	return dist;
}

// getBackIR() simply sets the ADC to the Back IR sensor
// and returns the sampled voltage in inches. Short, nonblocking.
float getBackIR(){
	//1 inch = 2.54 cm
	//1 cm = 0.3937 inches
	//float voltage;//IR range -0.4 to 5.3 V
	float distance;// (cm) 30 cm = 12 inches = 0.4 V
	float dist;//distance in inches
	ADC_SAMPLE adcsample;
	// Set the Voltage Reference first so VREF=5V.
	ADC_set_VREF( ADC_VREF_AVCC );
	// Set the channel we will sample from.
	ADC_set_channel(IRBACK_CHAN);
	// Now sample it!
	adcsample = ADC_sample();
	// Convert to meaningful voltage value.
	//voltage = adcsample * ( 5.0 / 1024 );
	// Convert to distance in cm
	distance = (2914/(adcsample+5.0))-1.0;
	//Convert distance to inches
	dist = distance*0.3937;
	return dist;
}
