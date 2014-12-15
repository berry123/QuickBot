	//Desc:  RangeSensors.c
	//A demo application to test robot locomotion
	//CEENBoT peripherals and effectors
	//Carlotta A. Berry
	//Dane Bennington
	//Jose Santos
	//created: 8/9/11
	//revised: 11/20/14+

	// *peripherals list*
	//ADC3 - PA3
	//ADC4 - PA4
	//ADC5 - PA5
	//ADC6 - PA6
	//ADC7 - PA7

	//sensors
	//IR - left [PA4], right [PA3] , back [PA5], front [PA7] on J3
	//photocells - left [PA6] on J3, right [PA5]* on J3
	//thermopile - SCL[PC0], SDA [PC1]
	//	*note:  BACK IR AND RIGHT PHOTOCELL SHARE THE SAME PINS
	//	*note:	pins left to right = ground(blk), +5V (yellow), signal (green)


	#include <avr/io.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "capi324v221.h"

	//global declarations here
	extern signed int samplevar;

	// IR Channels mapped to ADC inputs
	#define IRRIGHT_CHAN ADC_CHAN3
	#define IRLEFT_CHAN ADC_CHAN4
	#define IRFRONT_CHAN ADC_CHAN7
	#define IRBACK_CHAN ADC_CHAN5

	// Desc: The TPA81's I2C address (See datasheet).
	#define __TPA81_ADDR	0x68

	// Desc: The following macro-constants define the accessible registers
	//	     of the TPA81.
	#define __TPA81_REVISION 0
	#define __TPA81_AMBIENT	 1
	#define __TPA81_PIX1	 2
	#define __TPA81_PIX2	 3
	#define __TPA81_PIX3	 4
	#define __TPA81_PIX4	 5
	#define __TPA81_PIX5	 6
	#define __TPA81_PIX6	 7
	#define __TPA81_PIX7	 8
	#define __TPA81_PIX8	 9
	
	//Light channels mapped to ADC input (see *note above)
	#define	RIGHT_LIGHT_CHAN ADC_CHAN5
	#define	LEFT_LIGHT_CHAN ADC_CHAN6

	// --------------------------- Prototypes:
	I2C_STATUS get_revision( unsigned char *revision );
	I2C_STATUS get_ambient_temp( unsigned char *ambient_temp );
	I2C_STATUS read_pixel_1( unsigned char *pixel_1);
	I2C_STATUS read_pixel_2( unsigned char *pixel_2);
	I2C_STATUS read_pixel_3( unsigned char *pixel_3);
	I2C_STATUS read_pixel_4( unsigned char *pixel_4);
	I2C_STATUS read_pixel_5( unsigned char *pixel_5);
	I2C_STATUS read_pixel_6( unsigned char *pixel_6);
	I2C_STATUS read_pixel_7( unsigned char *pixel_7);
	I2C_STATUS read_pixel_8( unsigned char *pixel_8);
	
	//IR functions
	float getLeftIR();
	float getRightIR();
	float getFrontIR();
	float getBackIR();

	//photocells functions
	float getLeftLight();
	float getRightLight();

	//functions
	int WaitButton();//button function
	void MoveBot();//move the robot in a square

	//open status variables
	SUBSYS_OPENSTAT ATopstat;//ATTINY open status
	SUBSYS_OPENSTAT LEopstat;//LED open status
	SUBSYS_OPENSTAT LCopstat;//LCD open status

	// =================- Functions:
	// get temperatures
	I2C_STATUS get_revision( unsigned char *revision )
	{

		I2C_STATUS i2c_stat;

		// Begin a transaction as master transmitter so that
		// we can tell the sensor the register we want to read from
		// before we _actually_ read it.
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );

		// If successful...
		if( i2c_stat == I2C_STAT_OK )
		{

			// Send the register value (being 0).  This is
			// the register that contains the software revision.
			i2c_stat = I2C_MSTR_send( __TPA81_REVISION );

			// If successful...
			if( i2c_stat == I2C_STAT_OK )
			{

				// Now switch to master receiver so we can
				// read the data in register 0 of the sensor.
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );

				// If successful...
				if( i2c_stat == I2C_STAT_OK )
				{

					// Read the data...
					i2c_stat = I2C_MSTR_get( revision, FALSE );

					// If NOT successful...
					if ( i2c_stat != I2C_STAT_OK )

					// Overwrite it with 0.
					*revision = 0;
					
				} // end if()

			} // end if()

		} // end if()

		// I'm going to assume the transaction was successful,
		// so we need to stop it.
		I2C_MSTR_stop();

		// Also, return the status, regardless.
		return i2c_stat;

	} // end get_revision()
	I2C_STATUS get_ambient_temp( unsigned char *ambient_temp )
	{

		I2C_STATUS i2c_stat;

		// Begin a transaction as master transmitter so that
		// we can tell the sensor the register we want to read from
		// before we _actually_ read it.
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );

		// If successful...
		if( i2c_stat == I2C_STAT_OK )
		{

			// Send the register value (being 1).  This is
			// the register that contains the ambient temperature.
			i2c_stat = I2C_MSTR_send( __TPA81_AMBIENT );

			// If successful...
			if( i2c_stat == I2C_STAT_OK )
			{

				// Now switch to master receiver so we can
				// read the data in register 0 of the sensor.
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );

				// If successful...
				if( i2c_stat == I2C_STAT_OK )
				{

					// Read the data...
					i2c_stat = I2C_MSTR_get( ambient_temp, FALSE );

					// If NOT successful...
					if ( i2c_stat != I2C_STAT_OK )

					// Overwrite it with 0.
					*ambient_temp = 0;
					
				} // end if()

			} // end if()

		} // end if()

		// I'm going to assume the transaction was successful,
		// so we need to stop it.
		I2C_MSTR_stop();

		// Also, return the status, regardless.
		return i2c_stat;

	} // end get_ambient_temp()
	// get pixel one
	I2C_STATUS read_pixel_1( unsigned char *pixel_1)
	{
		I2C_STATUS i2c_stat;
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );
		if( i2c_stat == I2C_STAT_OK )
		{
			i2c_stat = I2C_MSTR_send(__TPA81_PIX1 );
			if( i2c_stat == I2C_STAT_OK )
			{
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );
				if( i2c_stat == I2C_STAT_OK )
				{
					i2c_stat = I2C_MSTR_get( pixel_1, FALSE );
					if ( i2c_stat != I2C_STAT_OK )
					*pixel_1 = 0;
				}
			}
		}
		I2C_MSTR_stop();
		return i2c_stat;
	}
	// get pixel two
	I2C_STATUS read_pixel_2( unsigned char *pixel_2)
	{
		I2C_STATUS i2c_stat;
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );
		if( i2c_stat == I2C_STAT_OK )
		{
			i2c_stat = I2C_MSTR_send(__TPA81_PIX2 );
			if( i2c_stat == I2C_STAT_OK )
			{
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );
				if( i2c_stat == I2C_STAT_OK )
				{
					i2c_stat = I2C_MSTR_get( pixel_2, FALSE );
					if ( i2c_stat != I2C_STAT_OK )
					*pixel_2 = 0;
				}
			}
		}
		I2C_MSTR_stop();
		return i2c_stat;
	}
	// get pixel three
	I2C_STATUS read_pixel_3( unsigned char *pixel_3)
	{
		I2C_STATUS i2c_stat;
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );
		if( i2c_stat == I2C_STAT_OK )
		{
			i2c_stat = I2C_MSTR_send(__TPA81_PIX3 );
			if( i2c_stat == I2C_STAT_OK )
			{
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );
				if( i2c_stat == I2C_STAT_OK )
				{
					i2c_stat = I2C_MSTR_get( pixel_3, FALSE );
					if ( i2c_stat != I2C_STAT_OK )
					*pixel_3 = 0;
				}
			}
		}
		I2C_MSTR_stop();
		return i2c_stat;
	}
	// get pixel four
	I2C_STATUS read_pixel_4( unsigned char *pixel_4)
	{
		I2C_STATUS i2c_stat;
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );
		if( i2c_stat == I2C_STAT_OK )
		{
			i2c_stat = I2C_MSTR_send(__TPA81_PIX4 );
			if( i2c_stat == I2C_STAT_OK )
			{
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );
				if( i2c_stat == I2C_STAT_OK )
				{
					i2c_stat = I2C_MSTR_get( pixel_4, FALSE );
					if ( i2c_stat != I2C_STAT_OK )
					*pixel_4 = 0;
				}
			}
		}
		I2C_MSTR_stop();
		return i2c_stat;
	}
	// get pixel five
	I2C_STATUS read_pixel_5( unsigned char *pixel_5)
	{
		I2C_STATUS i2c_stat;
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );
		if( i2c_stat == I2C_STAT_OK )
		{
			i2c_stat = I2C_MSTR_send(__TPA81_PIX5 );
			if( i2c_stat == I2C_STAT_OK )
			{
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );
				if( i2c_stat == I2C_STAT_OK )
				{
					i2c_stat = I2C_MSTR_get( pixel_5, FALSE );
					if ( i2c_stat != I2C_STAT_OK )
					*pixel_5 = 0;
				}
			}
		}
		I2C_MSTR_stop();
		return i2c_stat;
	}
	// get pixel six
	I2C_STATUS read_pixel_6( unsigned char *pixel_6)
	{
		I2C_STATUS i2c_stat;
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );
		if( i2c_stat == I2C_STAT_OK )
		{
			i2c_stat = I2C_MSTR_send(__TPA81_PIX6 );
			if( i2c_stat == I2C_STAT_OK )
			{
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );
				if( i2c_stat == I2C_STAT_OK )
				{
					i2c_stat = I2C_MSTR_get( pixel_6, FALSE );
					if ( i2c_stat != I2C_STAT_OK )
					*pixel_6 = 0;
				}
			}
		}
		I2C_MSTR_stop();
		return i2c_stat;
	}
	// get pixel seven
	I2C_STATUS read_pixel_7( unsigned char *pixel_7)
	{
		I2C_STATUS i2c_stat;
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );
		if( i2c_stat == I2C_STAT_OK )
		{
			i2c_stat = I2C_MSTR_send(__TPA81_PIX7 );
			if( i2c_stat == I2C_STAT_OK )
			{
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );
				if( i2c_stat == I2C_STAT_OK )
				{
					i2c_stat = I2C_MSTR_get( pixel_7, FALSE );
					if ( i2c_stat != I2C_STAT_OK )
					*pixel_7 = 0;
				}
			}
		}
		I2C_MSTR_stop();
		return i2c_stat;
	}
	// get pixel eight
	I2C_STATUS read_pixel_8( unsigned char *pixel_8)
	{
		I2C_STATUS i2c_stat;
		i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MT );
		if( i2c_stat == I2C_STAT_OK )
		{
			i2c_stat = I2C_MSTR_send(__TPA81_PIX8 );
			if( i2c_stat == I2C_STAT_OK )
			{
				i2c_stat = I2C_MSTR_start( __TPA81_ADDR, I2C_MODE_MR );
				if( i2c_stat == I2C_STAT_OK )
				{
					i2c_stat = I2C_MSTR_get( pixel_8, FALSE );
					if ( i2c_stat != I2C_STAT_OK )
					*pixel_8 = 0;
				}
			}
		}
		I2C_MSTR_stop();
		return i2c_stat;
	}

	//get the button state and check LEDs
	int WaitButton( void )
	{
		BOOL btnState1, btnState2, btnState3;//local variables - button states
		int rtnValue=0;//return the button value

		if((ATopstat.state=SUBSYS_OPEN))
		{
			// Get switch states.
			btnState1 = ATTINY_get_SW_state( ATTINY_SW3 );
			btnState2 = ATTINY_get_SW_state( ATTINY_SW4 );
			btnState3 = ATTINY_get_SW_state( ATTINY_SW5 );
			//LCD_printf("btnStates: %d %d %d \n", btnState1, btnState2, btnState3);

			if( btnState1 == TRUE )
			{
				LCD_printf( "SW1: Pushed\n");
				TMRSRVC_delay(1000);//wait 1 s

				// Assume the LED subsystem opened successfully.
				LED_set_pattern( 0b00100000 );//turn the red LED on
				TMRSRVC_delay(2000);//wait 2 seconds
				LED_clr_pattern( 0b01000000 );//turn the green LED off
				LED_clr_pattern( 0b00100000 );//turn the red LED off
				rtnValue=1;
			}//end if button 1 state open

			if( btnState2 == TRUE )
			{
				LCD_printf( "SW2: Pushed\n");
				TMRSRVC_delay(1000);//wait 1 s

				// Assume the LED subsystem opened successfully.
				LED_set_pattern( 0b01000000 );//turn the green LED on
				TMRSRVC_delay(2000);//wait 2 seconds
				LED_clr_pattern( 0b01000000 );//turn the green LED off
				LED_clr_pattern( 0b00100000 );//turn the red LED off
				rtnValue=2;
			}//end if btn 2 open

			if ( btnState3 == TRUE )
			{
				LCD_printf( "SW3: Pushed\n");
				TMRSRVC_delay(1000);//wait 1 s

				// Assume the LED subsystem opened successfully.
				LED_set_pattern( 0b01000000 );//turn the green LED on
				LED_set_pattern( 0b00100000 );//turn the red LED on
				TMRSRVC_delay(2000);//wait 2 seconds
				LED_clr_pattern( 0b01000000 );//turn the green LED off
				LED_clr_pattern( 0b00100000 );//turn the red LED off
				rtnValue=3;
			}//end if btn 3 open
			LCD_clear();
			return rtnValue;
		}//end AT while

	}//end the WaitButton() function

	// getLeftLight() converts ADC voltage to value inverse proportional to left light
	float getLeftLight(){

		float voltage;
		ADC_SAMPLE adcsample;
		ADC_set_VREF( ADC_VREF_AVCC );
		ADC_set_channel( LEFT_LIGHT_CHAN );
		adcsample = ADC_sample();
		LCD_printf( "ADC: %i\n",adcsample);
		voltage = adcsample * (5.0/ 1024.0 );
		LCD_printf( "voltage: %f\n",voltage);
		return voltage;
	}

	// getRightLight() converts ADC voltage to value inverse proportional to left light
	float getRightLight(){
		ADC_SAMPLE adcsample;
		float voltage;
		ADC_set_VREF( ADC_VREF_AVCC );
		ADC_set_channel( RIGHT_LIGHT_CHAN );
		adcsample = ADC_sample();
		LCD_printf( "ADC: %i\n",adcsample);
		voltage = adcsample * ( 5.0 / 1024 );
		LCD_printf( "right: %f\n",voltage);
		return voltage;
	}

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
		LCD_printf( "ADC: %i\n",adcsample);
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

	//main function to run the robot
	void CBOT_main(void)
	{
		int btnValue=0;//value of button pushed
		int i=0;//loop counter

		BOOL	ltContact;//left contact sensor
		BOOL	rtContact;//right contact sensor

		float	ltIR = 0;//left IR sensor
		float	rtIR = 0;//right IR sensor
		float	ftIR = 0;//front IR sensor
		float 	bkIR = 0;//back IR sensor

		float	ltLght;//left light sensor
		float	rtLght;//right light sensor

		//temperature sensor data
		unsigned char data;
		unsigned char pixel1 = 0;
		unsigned char pixel2 = 0;
		unsigned char pixel3 = 0;
		unsigned char pixel4 = 0;
		unsigned char pixel5 = 0;
		unsigned char pixel6 = 0;
		unsigned char pixel7 = 0;
		unsigned char pixel8 = 0;

		ATopstat = ATTINY_open();//open the tiny microcontroller
		LEopstat = LED_open(); //open the LED module
		SPKR_open(SPKR_BEEP_MODE);//open the speaker in beep mode
		LCopstat = LCD_open(); //open the LCD module
		LED_open();//open the LED
		I2C_open();//open the I2C
		ADC_open();//open the ADC module
		ADC_set_VREF( ADC_VREF_AVCC );// Set the Voltage Reference first so VREF=5V.

		
		//keep the microcontroller running
		while(1)
		{
			//LCD_printf_PGM( PSTR( "SENSOR TEST\n" ));
			//LCD_printf_PGM( PSTR( "Push S3: Contact and Light Sensors\n" ));
			//LCD_printf_PGM( PSTR( "Push S4: Infrared Sensors\n" ));
			//LCD_printf_PGM( PSTR( "Push S5: Temperature Sensor\n" ));
			LCD_printf( PSTR( "SENSOR TEST\n" ));
			//TMRSRVC_delay(1000);
			LCD_printf( PSTR( "S3: Ct & Lt\n" ));
			LCD_printf( PSTR( "S4: IR\n" ));
			LCD_printf( PSTR( "S5: Temp\n" ));
					
			btnValue=WaitButton();
			if (btnValue==1)
			{
				//Check Light Sensors
				//beep once
				SPKR_play_beep( 500,500,100);//500 Hz for 500 ms
				i = 0;
				for(i = 0;i<25;i++)
				{
					//read the contact sensors
					ltContact = ATTINY_get_IR_state(ATTINY_IR_LEFT);
					rtContact = ATTINY_get_IR_state(ATTINY_IR_RIGHT);
					LCD_printf("ltCt: %d  rtCt: %d\n",ltContact, rtContact);//print contact sensors status

					//read the photocells
					ltLght = getLeftLight();//get left light
					rtLght = getRightLight();//get right light
					LCD_printf("ltLt: %3.2f rtLt: %3.2f\n\n",ltLght, rtLght);//print photocell status

					TMRSRVC_delay(1000);//wait 1 secs
				}
			}
			else if (btnValue==2)
			{
				//Check IR Sensors
				//beep twice
				SPKR_play_beep(250, 500, 50);//250 Hz for 250 ms
				SPKR_play_beep(250, 500, 50);//250 Hz for 250 ms
				//LCD_printf("get the IR sensors\n");//print left IR

				//read the IR sensors
				i = 0;
				for(i = 0;i<100;i++)
				{
					//get IR data
					ltIR = getLeftIR();
					rtIR = getRightIR();
					ftIR = getFrontIR();
					bkIR = getBackIR();

					//print IR data
					LCD_printf("ftIR: %3.2f\n", ftIR);
					LCD_printf("bkIR: %3.2f\n", bkIR);
					LCD_printf("ltIR: %3.2f\n", ltIR);
					LCD_printf("rtIR: %3.2f\n", rtIR);
					//wait 1 sec
					TMRSRVC_delay(1000);
				}
			}
			else if (btnValue==3)
			{
				//Check temperature sensor
				//beep three times
				SPKR_play_beep(125, 250, 50);//125 Hz for 1250 ms
				SPKR_play_beep(125, 250, 50);//125 Hz for 1250 ms
				SPKR_play_beep(125, 250, 50);//125 Hz for 1250 ms
				
				LED_set( LED_Green );
				//read the IR sensors
				i = 0;
				for(i = 0;i<25;i++)
				{
					// read the 8 pixels
					read_pixel_1(&pixel1);
					read_pixel_2(&pixel2);
					read_pixel_3(&pixel3);
					read_pixel_4(&pixel4);
					read_pixel_5(&pixel5);
					read_pixel_6(&pixel6);
					read_pixel_7(&pixel7);
					read_pixel_8(&pixel8);

					if( read_pixel_1(&pixel1) == I2C_STAT_OK )
					{

						// Display the sensor values:
						LCD_printf_PGM( PSTR( "Sensor Pixels: \n" ));

						// The first four pixels.
						LCD_printf_PGM( PSTR( "%3d, %3d, %3d, %3d\n" ),
						pixel1, pixel2, pixel3,pixel4);

						// The last four pixels.
						LCD_printf_PGM( PSTR( "%3d, %3d, %3d, %3d\n" ),
						pixel5, pixel6, pixel7, pixel8);

						// Let's read the ambient temperature also...
						if( get_ambient_temp( &data ) == I2C_STAT_OK )
						{

							LCD_printf_PGM( PSTR( "Ambient: %3d\t" ), data );

						} // end if()
						else
						LCD_printf_PGM( PSTR( "Ambient: ?\t" ) );

					} // end if()

					else

					//LCD_printf_PGM( PSTR( "ERROR: Reading!\n" ) );

					LED_clr( LED_Green );

					// Wait a bit
					TMRSRVC_delay_sec(1);

					// Clear the display for the next iteration.
					//LCD_clear();
				}

			}//end read the temperature sensor
			//LCD_clear();//clear the LCD
		}//end the while loop
	}// end the CBOT_main()
