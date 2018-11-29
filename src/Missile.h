//
//  Missile.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/28/18.
//

#ifndef Missile_h
#define Missile_h
#include "ofApp.h"
#include "ofMain.h"

class Missile : public ofBaseApp
{
public:
    Missile();
    void setup();
    void update();
    void draw(char c);
private:
    int xPos, yPos, radius;
};

#endif /* Missile_h */
