//
//  Missile.cpp
//  emptyExample
//
//  Created by Travis Olmstead on 11/28/18.
//

#include <stdio.h>
#include "ofApp.h"
#include "Missile.h"

Missile::Missile(){
    
}//Default Constructor
void Missile::setup()
{
    
    visible = false;
    dx = 0;
    dy = 0;
    xPos = ofGetWidth()/(1.425);
    yPos = ofGetHeight()-50;
    missilePosition = ofVec2f(xPos, yPos);
    radius = 10;
}//missile setup
void Missile::update(char c)
{
    
}//missile update
void Missile::draw(char c)
{
    //ofSetColor(0, 0, 0);
    ofDrawCircle(xPos, yPos, radius);

}//draw missile
