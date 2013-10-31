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
	void runLights(int br[]);

	int val;
	int valInc;


	int br[48];
	int cellSize;
	float cellSizeFl;

	int	cameraWidth;
	int	cameraHeight;

	PWM* pwm;
	ofVideoGrabber videoGrabber;


	

		
	
		//Adafruit_TLC5947* tlc; 
	
};
