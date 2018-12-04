//
//  GalagaShip.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/27/18.
//

#ifndef GalagaShip_h
#define GalagaShip_h
#include "src/ofApp.h"
#include "ofMain.h"
#include "ofVec2f.h"

class GalagaShip : public ofBaseApp {
public:
    GalagaShip();
    void setup();
    void update(char c);
    void draw();
    ofImage ship;
    ofVec2f getPosition();
private:
    ofVec2f pos;
    
    float dx, dy;
    
};

#endif /* GalagaShip_h */
