//
//  Missile.cpp
//  emptyExample
//
//  Created by Travis Olmstead on 11/28/18.
//

#include <stdio.h>
#include "src/ofApp.h"
#include "Missile.h"

Missile::Missile(ofRectangle gameBounds, int directionY, double x, double y):SpriteObject(gameBounds)
{
	this->directionY *= directionY;
	setBounds(ofRectangle(x, y, radius, radius));
}
void Missile::update()
{
	ofRectangle bounds = getBounds();
	bounds.x += vel.x;
	bounds.y += vel.y*directionY;

	if (!gameBounds.intersects(bounds)) {
		Missile m = *this;
		ofNotifyEvent(isOffScreen, m);
	}

	setBounds(bounds);
}
void Missile::draw()
{
	ofSetColor(255,255,255);
	ofFill();
	ofDrawCircle(getBounds().getCenter(),radius);
}

void Missile::keyPressed(int key)
{
}

void Missile::keyReleased(int key)
{
}

void Missile::mouseMoved(int x, int y)
{
}

void Missile::mousePressed(int x, int y, int button)
{
}

void Missile::mouseReleased(int x, int y, int button)
{
}
