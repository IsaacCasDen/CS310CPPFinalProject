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
    }
    for(int j=0; j<galaga_ship.size(); j++)
    {
        galaga_ship[j]->setup();
    }
    
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
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i=0; i<galaga_ship.size(); i++) {
        galaga_ship[i]->draw();
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
