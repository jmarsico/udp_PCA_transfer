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

	ofSetVerticalSync(false);
	cameraWidth		= 320;
	cameraHeight	= 240;
	cellSize = 40;
	cellSizeFl  = (float)cellSize;
	
	videoGrabber.listDevices();
	videoGrabber.setDesiredFrameRate(60); 
	videoGrabber.initGrabber(cameraWidth, cameraHeight);

}


//--------------------------------------------------------------
void testApp::update(){


	/////////////TEST BLINK FIRST LED/////////////////
	/*
	pwm->setPWM(0,0,1);
	sleep(1);
	pwm->setPWM(0,0,4095);
	sleep(1);
	*/

	///////////// RAMP TEST ////////////////////
    /*
	for(int val = 1; val < 4096; val+=10)
	{
		for(int i = 0; i < 16; i++)
		{
			pwm->setPWM(i,0,val);
		}
	}
	*/

	ofBackground(10, 10, 10);
	
	videoGrabber.update();

	
	if(videoGrabber.isFrameNew())                            //if a new frame is available do this:
    {
        ofPixels pix = videoGrabber.getPixelsRef(); 
        pix.mirror(false, true); 
       // invertedTexture.loadData(pix);

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
	int lightBright[16];
	for(int i = 0; i <16; i++)
    {
    	lightBright[i] = ofMap(br[i], 0, 255, 0, 2000);
    	pwm->setPWM(i, 0, lightBright[i]);

    	//printf("%d, ", lightBright[i]);
    }
   // printf("\n");
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

