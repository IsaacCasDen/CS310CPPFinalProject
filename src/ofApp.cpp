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
	ofVec2f size;
	while ((size=ofGetWindowSize()).distance(ofVec2f(0,0))==0);
    game=Game(size);
    game.startGame();
	
}

//--------------------------------------------------------------
void ofApp::update(){
	game.update();
}//update()

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
	game.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	game.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	game.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	game.mouseReleased(x, y, button);
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
