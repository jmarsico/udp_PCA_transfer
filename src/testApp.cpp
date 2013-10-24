#include "testApp.h"

//Often I have to run 
// $sudo amixer cset numid=3 1
//


//--------------------------------------------------------------
void testApp::setup(){
	//ofSetFrameRate(15);
	
	pwm = new PWM(0x40, true);
	pwm ->setPWMFreq(60);
	
	//exit(1);
	/*int fd = wiringPiI2CSetup(0x40);
	if(fd == -1)
	{
		ofLogVerbose("setup failed");
	} else
	{
		printf("%d\n", fd);
	}
	*/

}


//--------------------------------------------------------------
void testApp::update(){

	/*
	pwm->setPWM(0,0,1);
	sleep(1);
	pwm->setPWM(0,0,4095);
	sleep(1);
	*/

	for(int val = 1; val < 4096; val+=10)
	{
		for(int i = 0; i < 16; i++)
		{
			pwm->setPWM(i,0,val);
		}
	}

}

//--------------------------------------------------------------
void testApp::draw(){

	
    
}

