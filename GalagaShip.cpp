//
//  GalagaShip.cpp
//  emptyExample
//
//  Created by Travis Olmstead on 11/27/18.
//

#include <stdio.h>
#include "src/ofApp.h"
#include "GalagaShip.h"
GalagaShip::GalagaShip(){}
void GalagaShip::setup()
{
    int xPos = ofGetWidth()/(1.85);
    int yPos = ofGetHeight()-150;
    pos = ofVec2f(xPos, yPos);
    dx = 0;
    dy = 0;
    ship.load("galaga_ship.png");
}
void GalagaShip::update(char c)
{
    pos.x += dx;
    pos.y += dy;
    if (c == 'L') {
        dx = -1;
        dy = 0;
    }
    if (c == 'R') {
        dx = 1;
        dy = 0;
    }
}
void GalagaShip::draw()
{
    ship.draw(pos.x, pos.y);
    
}
ofVec2f GalagaShip::getPosition(){
    return pos;
}

