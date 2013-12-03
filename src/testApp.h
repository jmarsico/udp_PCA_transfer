#pragma once

#include "ofMain.h"
#include "PCA9685.h"

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

	
	int numBoards;

	ofVideoGrabber videoGrabber;
	PCA9685* pca; //initialize the class with number of boards



	
};
