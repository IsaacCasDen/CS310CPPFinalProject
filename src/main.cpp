#include "ofMain.h"
#include "ofApp.h"
#include "ofVec2f.h"

//========================================================================
int main( ){
	ofVec2f size = ofVec2f(1920,1080);
	ofSetupOpenGL(size.x,size.y,OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	ofRunApp(new ofApp());

}
