#pragma once

#include "ofMain.h"
//#include "Adafruit_TLC5947.h"
//#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "pwmlib.h"

 // set to -1 to not use the enable pin (its optional)

class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

	int val;
	int valInc;

	PWM* pwm;

	

		
	
		//Adafruit_TLC5947* tlc; 
	
};
