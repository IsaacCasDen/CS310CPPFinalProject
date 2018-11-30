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
    visible = false;
    dx = 0;
    dy = 0;
    xPos = ofGetWidth()/(1.425);
    yPos = ofGetHeight()-50;
    radius = 10;
}//missile setup
void Missile::update(char c)
{
    xPos += dx;
    yPos += dy;
    if(c == 'C')
    {
        dx = 1.35;
        dy = 0;
    }
    if(c == 'D')
    {
        dx = -1.35;
        dy = 0;
    }
    
    
}//missile update
void Missile::draw(char c)
{
    //ofSetColor(0, 0, 0);
    ofDrawCircle(xPos, yPos, radius);

}//draw missile
