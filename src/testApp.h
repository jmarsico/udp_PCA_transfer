#pragma once

#include "ofMain.h"
#include "PCA9685.h"
#include "ofxNetwork.h"

 // set to -1 to not use the enable pin (its optional)

class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void testLights();
	int curvedMap(int inVal);
	void killallLights();
	
	ofxUDPManager udpConnection;
	
	int numBoards;
	//int val;

	int blankCounter;

	
	PCA9685* pca; //initialize the class with number of boards



	
};
