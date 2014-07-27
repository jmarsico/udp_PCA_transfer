#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetLogLevel(OF_LOG_VERBOSE);

	//construct new PCA9685 object with the number of boards you're using
	numBoards = 11;
	pca = new PCA9685(numBoards);
    ofSetVerticalSync(false);

    //test the lights before turning on UDP
    //testLights();

	udpConnection.Create();
	udpConnection.Bind(11999);
	udpConnection.SetNonBlocking(true);
	

	//on start-up, run through light test
	//val = 0;
	blankCounter = 0;

}


//--------------------------------------------------------------
void testApp::update()
{
	
	char udpMessage[200000];
	int result = udpConnection.Receive(udpMessage,200000);
	if(result > 0)
	{
		string message=udpMessage;
		blankCounter = 0;
		if(message!="")
		{
			int chan, val;
			vector<string> strVals = ofSplitString(message,"[/p]");
			for(unsigned int i=0;i<strVals.size();i++)
			{
				vector<string> point = ofSplitString(strVals[i],"|");
				if( point.size() == 2 )
				{
					chan=atoi(point[0].c_str());
					val=atoi(point[1].c_str());
					val = curvedMap(val);
					pca->setLED(chan, val);
				}
			}
 			ofLogVerbose() << "FrameRate: " << ofGetFrameRate();
		}
	}
	else if (result < 0)
	{
		//ofLog() << "nothing there";
		blankCounter ++;
	}

	if (blankCounter == 1000)
	{
		killallLights();

	}


}


//--------------------------------------------------------------
int testApp::curvedMap(int inVal){
	float shaper = 1.2;
	float in = (float)inVal;
	float pct = ofMap(in, 0, 255, 0, 1, true);
	pct = powf(pct, shaper);
	int outVal = (int)ofMap(pct, 0, 1, 0, 4095, true);

	return outVal;
}


//--------------------------------------------------------------
void testApp::testLights(void)
{
    for(int i = 0; i < 16*numBoards; i++)
    {
	  pca->setLED(i, 4095);
	  ofSleepMillis(100); 
	  ofLog() << "light: " << i;
	  pca->setLED(i,0);

    }
}


//--------------------------------------------------------------
void testApp::killallLights(){
	for(int i = 0; i < 16 * numBoards; i++)
	{
		pca->setLED(i, 0);
	}
}


