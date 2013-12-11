#include "testApp.h"

//Often I have to run 
// $sudo amixer cset numid=3 1
//


//--------------------------------------------------------------
void testApp::setup(){
	//ofSetFrameRate(15);
	
	//construct new PCA9685 object with the number of boards you're using
	numBoards = 2;
	pca = new PCA9685(numBoards);


	ofSetVerticalSync(false);
	cameraWidth		= 320;
	cameraHeight	= 240;
	cellSize = 48;
	cellSizeFl  = (float)cellSize;
	numPixels = (cameraWidth/cellSize) * (cameraHeight/cellSize);

	displayCoeff = 2;
	
	videoGrabber.listDevices();
	videoGrabber.setDesiredFrameRate(60); 
	videoGrabber.initGrabber(cameraWidth, cameraHeight);
	pixels = new unsigned char[numPixels];

    //pixelTexture.allocate(cameraWidth, cameraHeight, GL_LUMINANCE);


}


//--------------------------------------------------------------
void testApp::update(){

	/////////////TEST BLINK FIRST LED/////////////////
/*
	pca->setLED(0,4095);
	pca->setLED(16, 4095);
	sleep(1);

	pca->setLED(0,1);
	pca->setLED(16, 1);
	sleep(1);
*/
	

	///////////// RAMP TEST ////////////////////
    
/*	
	for(int val = 1; val < 4096; val+=100)
	{
		for(int i = 0; i < 16*numBoards; i++)
		{
			pca->setLED(i, val);

		}
	}
*/		
	//////////////////Prod Section //////////////////
	
	
	videoGrabber.update();

	
	if(videoGrabber.isFrameNew())                            //if a new frame is available do this:
    {
        ofPixels pix = videoGrabber.getPixelsRef(); 
        pix.mirror(false, true); 

        for(int i = 0; i < cameraWidth/cellSize; i++)
        {
        	for (int j = 0; j < cameraHeight/cellSize; j++)
			{
				int x = i*cellSize;
				int y = j*cellSize;
				br[(i*cameraHeight/cellSize)+j] = (float)pix.getColor(x,y).getLightness();
			}
        }
    }


    runLights(br); 
}

//--------------------------------------------------------------

void testApp::runLights(float br[])
{
	int lightBright[16*numBoards];
	for(int i = 0; i <16*numBoards; i++)
    {
    	lightBright[i] = ofMap(br[i], 0, 255, 0, 4095);
    	pca->setLED(i, lightBright[i]);

    	//printf("channel: %d,  value: %d\n", i, lightBright[i]);
    }
}
#
	

//--------------------------------------------------------------
void testApp::draw(){
	
	int leftSpace = 100;
	int space = 200-cellSize;
	int height = 230;

	ofBackground(10, 10, 10);

	ofSetColor(255);
	videoGrabber.draw(leftSpace, height, cameraWidth*displayCoeff, cameraHeight*displayCoeff);
	ofDrawBitmapString("Source", leftSpace, height-20);


			
	
		//ofTranslate(cameraWidth+100,100);
		//pixelTexture.draw(0,0);
	
	ofDrawBitmapString("Pixelated and Mirrored", cameraWidth*displayCoeff+leftSpace+space+cellSize, height - 20);

	for(int i = 0; i<cameraWidth/cellSize; i++)
		{
			for(int j = 0; j < cameraHeight/cellSize; j++)
			{
				ofPushMatrix();
				ofTranslate(space,0);
				ofTranslate(i*cellSize*displayCoeff+cameraWidth*displayCoeff+space, j*cellSize*displayCoeff+height);
					ofSetColor(br[(i*cameraHeight/cellSize)+j]);
					ofRect(0.0,0.0,cellSizeFl*displayCoeff, cellSizeFl*displayCoeff);
				ofPopMatrix();
			}
		}
	//ofPopMatrix();
	

	ofSetColor(255);
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 0), 5, ofGetWindowHeight()-5);
    
}

