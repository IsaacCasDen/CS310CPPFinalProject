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
    void update(char c);
    void draw(char c);
private:
    float xPos, yPos, radius;
    float dx, dy;
    bool visible;
};

#endif /* Missile_h */
