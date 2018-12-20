#include "ofApp.h"

ofApp::ofApp()
{
}

ofApp::~ofApp()
{
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofVec2f size;
	if (true) {
		while ((size = ofGetWindowSize()).distance(ofVec2f(0, 0)) == 0);
	}
	else {
		while ((size = ofVec2f(ofGetScreenWidth(), ofGetScreenHeight())).distance(ofVec2f(0, 0)) == 0);
	}
	
    game=Game(size);
	ofAddListener(game.closed, this, &ofApp::onGameExit);

    game.startGame();
    output.open(ofToDataPath("../output.txt").c_str());
    if(!output.is_open())
    {
        cout << "ERROR! Cannot open file!" << endl;
    }
    
    output << "You created this game on: " << ofGetMonth() << "-" << ofGetDay() << "-" <<
    ofGetYear() << " at " << ofGetHours() << ":" << ofGetMinutes() << "." << ofGetSeconds() ;
    output.close();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (!this->isClosing) {
		game.update();
	}
	else {
		try {
			ofExit();
		}
		catch (const std::exception& e) {
			cerr << "Error Exiting Application:" << endl << e.what() << endl;
		}
	}
}//update()

//--------------------------------------------------------------
void ofApp::draw(){
	if (!this->isClosing) {
		game.draw();
	}
}

void ofApp::onGameExit()
{
	this->isClosing = true;
	game.exitGame();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (!this->isClosing) {
		game.keyPressed(key);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (!this->isClosing) {
		game.keyReleased(key);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (!this->isClosing) {
		game.mouseMoved(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (!this->isClosing) {
		game.mouseMoved(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (!this->isClosing) {
		game.mousePressed(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (!this->isClosing) {
		game.mouseReleased(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
