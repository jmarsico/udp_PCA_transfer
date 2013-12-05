#pragma once

#include "ofMain.h"
#include "PCA9685.h"

 // set to -1 to not use the enable pin (its optional)

class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
	void runLights(float br[]);

	int val;
	int valInc;


	float br[48];
	unsigned char* pixels;
	int cellSize;
	float cellSizeFl;
	int numPixels;

	int	cameraWidth;
	int	cameraHeight;

	float displayCoeff;

	
	int numBoards;

	ofVideoGrabber videoGrabber;
	//ofTexture pixelTexture;
	PCA9685* pca; //initialize the class with number of boards



	
};
