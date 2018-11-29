//
//  GalagaShip.cpp
//  emptyExample
//
//  Created by Travis Olmstead on 11/27/18.
//

#include <stdio.h>
#include "ofApp.h"
#include "GalagaShip.h"
GalagaShip::GalagaShip(){}
void GalagaShip::setup()
{
    xPos = ofGetWidth()/(1.85);
    yPos = ofGetHeight()-150;
    dx = 0;
    dy = 0;
    ship.load("galaga_ship.png");
}
void GalagaShip::update(char c)
{
    xPos += dx;
    yPos += dy;
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
    ship.draw(xPos, yPos);
}

