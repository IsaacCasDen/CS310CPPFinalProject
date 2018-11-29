#include "ofApp.h"

ofApp::ofApp()
{
	game = Game(ofVec2f(ofGetWindowWidth(), ofGetWindowHeight()));
}

ofApp::~ofApp()
{
}

//--------------------------------------------------------------
void ofApp::setup(){
    game=Game(ofGetWindowSize());
    game.startGame();
}

//--------------------------------------------------------------
void ofApp::update(){
    game.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    game.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
    game.exitGame();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
