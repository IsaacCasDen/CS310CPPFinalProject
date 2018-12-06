//
//  Missile.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/28/18.
//

#ifndef Missile_h
#define Missile_h
#include "src/ofApp.h"
#include "ofMain.h"
#include "ofVec2f.h"
#include "GalagaShip.h"
#include <vector>

class Missile : public ofBaseApp
{
public:
    Missile();
    void setup();
    void update(char c);
    void draw(char c);
private:
    float xPos, yPos, radius;
    ofVec2f missilePosition;
    vector<GalagaShip*> galagaShip;
    float dx, dy;
    bool visible;
};

#endif /* Missile_h */
