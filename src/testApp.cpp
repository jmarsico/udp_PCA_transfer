#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
	

	//construct new PCA9685 object with the number of boards you're using
	numBoards = 2;
	pca = new PCA9685(numBoards);

	
    ofSetVerticalSync(false);
	cameraWidth		= 320;
	cameraHeight	= 240;
	cellSize = 48;
	cellSizeFl  = (float)cellSize;
	numPixels = (cameraWidth/cellSize) * (cameraHeight/cellSize);
    ofLog() << "numPixels: " << numPixels;

	displayCoeff = 1;
	
	videoGrabber.listDevices();
	videoGrabber.setDesiredFrameRate(60); 
	videoGrabber.initGrabber(cameraWidth, cameraHeight);
	pixels = new unsigned char[numPixels];

    noiseSpeedX = 0.01;
    noiseSpeedY = 0.01;
    noiseAmp = 2000;
    
    time = 0;
    timeInc = 0.1;


}


//--------------------------------------------------------------
void testApp::update()
{
	
//////////////////Prod Section //////////////////
	videoGrabber.update();

	
	if(videoGrabber.isFrameNew())                            //if a new frame is available do this:
    {
        ofPixels pix = videoGrabber.getPixelsRef(); 
        pix.mirror(false, true); 

        for(int j = 0; j < cameraHeight/cellSize; j++)
        {
        	for (int i = 0; i < cameraWidth/cellSize; i++)
			{
				int x = i*cellSize;
				int y = j*cellSize;
				br[(j*(cameraWidth/cellSize))+i] = (float)pix.getColor(x,y).getLightness();
				br[(j*(cameraWidth/cellSize))+i] = ofMap(br[(j*(cameraWidth/cellSize))+i], 0, 255, 0, 2000);
			}
        }
    }

    makeNoise();
    runLights(br);
    ofLog() << ofGetFrameRate() ;
    
}


///////////////////////// NOISE ///////////////////////////////////
void testApp::makeNoise(void)
{
    for(int i = 0; i < 30; i++)
    {
        noiseVal[i] = abs(noiseAmp * ofNoise(time * noiseSpeedX*(i+10), time*noiseSpeedY*(10-i)));
       // ofLog() << "index: " << i << " || value: " << noiseVal[i];
    }
    time += timeInc;
}


/////////////////// STEVEN'S LAW /////////////////////////////////
float testApp::stevensLaw(float val)
{
    float newVal;
    if(val <= 255)
    {
       newVal = pow(255.0 * ((float)val/(float)255), 1.0/0.5) + 0.5;
    }
    
    return newVal;
}

////////////////////// RUN LIGHTS //////////////////////////////////
void testApp::runLights(float br[])
{
	int lightBright[16*numBoards];
	for(int i = 0; i <30; i++)
    {
    	lightBright[i] = br[i] + noiseVal[i];
    	
    	//pca->setLED(i, br[i]);
    	//pca->setLED(i, noiseVal[i]);
    	pca->setLED(i, lightBright[i]);
    	

    	//ofLog() << "channel: " << i << " value: " << noiseVal[i];
    }
}





//--------------------------------------------------------------
void testApp::draw(){
	
	/*
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

	for(int j = 0; j < (cameraHeight/cellSize); j++)
		{
			for(int i = 0; i < (cameraWidth/cellSize); i++)
			{
				ofPushMatrix();
				ofTranslate(space,0);
				ofTranslate(i*cellSize*displayCoeff+cameraWidth*displayCoeff+space, j*cellSize*displayCoeff+height);
				//ofSetColor(stevensLaw(br[j*(cameraWidth/cellSize)+i]));
                //ofSetColor((noiseVal[j*(cameraWidth/cellSize)+i]) + ofMap(br[j*(cameraWidth/cellSize)+i], 0, 255, 0, 125));
					ofRect(0.0,0.0,cellSizeFl*displayCoeff, cellSizeFl*displayCoeff);
                    ofSetColor(255,0,0);
                    ofDrawBitmapString(ofToString(j*(cameraWidth/cellSize)+i), 0,10);
				ofPopMatrix();
			}
		}
	//ofPopMatrix();
	

	ofSetColor(255);
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 0), 5, ofGetWindowHeight()-5);
    */
}


void testApp::testLights(void)
{
    
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
}


