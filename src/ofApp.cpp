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
	/*
    ofBackground(0, 0, 0);
    port = serial.setup("/dev/tty.usbmodem143101", 9600);
    if(port)
    {
        cout << "Port OK!" << endl;
    }
    else {
        cout << "Port NOT OK!" << endl;
    }
    for(int i=0; i<1; i++)
    {
        galaga_ship.push_back(new GalagaShip());
    }//create new ship and push it into the vector
    for (int i=0; i<1; i++) {
        missiles.push_back(new Missile());
    }//create new missiles and push them into the vector
    for(int j=0; j<galaga_ship.size(); j++)
    {
        galaga_ship[j]->setup();
    }//setup ship
    for (int i=0; i<missiles.size(); i++) {
        missiles[i]->setup();
    }//setup missiles
    

    game=Game(getWindowSize);
    game.startGame();
 
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i<galaga_ship.size(); i++)
    {
        char c;
        if(serial.available())
        {
            c = serial.readByte();
            galaga_ship[i]->update(c);
            
        }//if serial is available
    }//for loop cycling through galaga ship vector
    for(int i=0; i<missiles.size(); i++)
    {
        char c;
        if(serial.available())
        {
            c = serial.readByte();
            missiles[i]->update(c);
            cout << c << endl;
        }
    }
	*/
}//update()

//--------------------------------------------------------------
void ofApp::draw(){
    /*
    for (int i=0; i<galaga_ship.size(); i++) {
        char c;
        galaga_ship[i]->draw();
    }
    for (int i=0; i<missiles.size(); i++) {
        char c;
        missiles[i]->draw(c);
    }
    */
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
