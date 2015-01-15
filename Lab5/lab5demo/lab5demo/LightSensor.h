<<<<<<< HEAD
#define RIGHT_PHOTO ADC_CHAN5
#define LEFT_PHOTO ADC_CHAN6

float getLeftLight(){

	float voltage, percent;
	ADC_SAMPLE adcsample;
	ADC_set_VREF( ADC_VREF_AVCC );
	ADC_set_channel( LEFT_PHOTO );
	adcsample = ADC_sample();
	//LCD_printf( "ADC: %i\n",adcsample);
	voltage = adcsample * (5.0/ 1024.0 );
	//LCD_printf( "voltage: %f\n",voltage);
	//percent = (voltage-1.67)*60;
	//return percent;
	return voltage*20;
}

// getRightLight() converts ADC voltage to value inverse proportional to left light
float getRightLight(){
	ADC_SAMPLE adcsample;
	float voltage, percent;
	ADC_set_VREF( ADC_VREF_AVCC );
	ADC_set_channel( RIGHT_PHOTO );
	adcsample = ADC_sample();
	//LCD_printf( "ADC: %i\n",adcsample);
	voltage = adcsample * ( 5.0 / 1024 );
	//LCD_printf( "right: %f\n",voltage);
	//percent = (voltage-1.67)*60;
	//return percent;
	return voltage*20;
}
