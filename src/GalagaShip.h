//
//  GalagaShip.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/27/18.
//

#ifndef GalagaShip_h
#define GalagaShip_h
#include "ofApp.h"
#include "ofMain.h"
class GalagaShip : public ofBaseApp {
public:
    GalagaShip();
    void setup();
    void update(char c);
    void draw();
    ofImage ship;
private:
    int xPos, yPos;
    float dx, dy;
    
};

#endif /* GalagaShip_h */
