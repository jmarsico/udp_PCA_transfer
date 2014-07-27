#include "ofMain.h"
#include "testApp.h"
#ifdef TARGET_OPENGLES
#include "ofGLProgrammableRenderer.h"
#include "ofAppNoWindow.h"
#endif
//========================================================================
int main( ){

	
	#ifdef TARGET_OPENGLES
	ofSetCurrentRenderer(ofPtr<ofBaseRenderer>(new ofGLProgrammableRenderer()));
	ofAppNoWindow window;
	#endif
	ofSetupOpenGL(&window,1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
