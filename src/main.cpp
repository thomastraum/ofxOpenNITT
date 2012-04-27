
#include "testApp.h"
#include "ofMain.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
//	ofSetupOpenGL(&window, 640*2,500*2, OF_WINDOW);			// <-------- setup the GL context
	ofSetupOpenGL(&window, 1280,960, OF_WINDOW);			// <-------- setup the GL 
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
