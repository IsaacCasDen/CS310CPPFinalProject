#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
    
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i<galaga_ship.size(); i++) {
        char c;
        if(serial.available())
        {
            c = serial.readByte();
            galaga_ship[i]->update(c);
            cout << c << endl;
        }//if serial is available
    }//for loop cycling through galaga ship vector
    for(int i=0; i<missiles.size(); i++)
    {
        missiles[i]->update();
    }
}//update()

//--------------------------------------------------------------
void ofApp::draw(){
    char c;
    for (int i=0; i<galaga_ship.size(); i++) {
        galaga_ship[i]->draw();
    }
    for (int i=0; i<missiles.size(); i++) {
        missiles[i]->draw(c);
    }
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
