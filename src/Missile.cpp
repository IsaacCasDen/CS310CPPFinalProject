//
//  Missile.cpp
//  emptyExample
//
//  Created by Travis Olmstead on 11/28/18.
//

#include <stdio.h>
#include "ofApp.h"
#include "Missile.h"

Missile::Missile(){}//Default Constructor
void Missile::setup()
{
    xPos = ofGetWidth()/2;
    yPos = ofGetHeight()/2;
    radius = 10;
}//missile setup
void Missile::update()
{
    
}//missile update
void Missile::draw(char c)
{
    ofSetColor(255, 255, 255);
    ofDrawCircle(xPos, yPos, radius);
}//draw missile
