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
	
	videoGrabber.listDevices();
	videoGrabber.setDesiredFrameRate(60); 
	videoGrabber.initGrabber(cameraWidth, cameraHeight);

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
	ofBackground(10, 10, 10);
	
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
				br[(i*cameraHeight/cellSize)+j] = pix.getColor(x,y).getLightness();
			}
        }
    }

    /*
    for(int i = 0; i < 48; i++)
    {
    	printf("%d, ", br[i]);
    }
    printf("\n");
    */
    runLights(br); 
}

//--------------------------------------------------------------

void testApp::runLights(int br[])
{
	int lightBright[16*numBoards];
	for(int i = 0; i <16*numBoards; i++)
    {
    	lightBright[i] = ofMap(br[i], 0, 255, 0, 2000);
    	pca->setLED(i, lightBright[i]);

    	printf("channel: %d,  value: %d\n", i, lightBright[i]);
    }
}



//--------------------------------------------------------------
void testApp::draw(){
	
/*
	for(int i = 0; i<cameraWidth/cellSize; i++)
		{
			for(int j = 0; j < cameraHeight/cellSize; j++)
			{
				ofPushMatrix();
				ofTranslate(i*cellSize*3, j*cellSize*3);
					ofSetColor(br[(i*cameraHeight/cellSize)+j]);
					ofRect(0.0,0.0,cellSizeFl*3, cellSizeFl*3);
				ofPopMatrix();
			}
		}
*/
	ofSetColor(0,255,0);
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 0), 5, ofGetWindowHeight()-5);
    
}

