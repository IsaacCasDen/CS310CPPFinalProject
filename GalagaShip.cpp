
//
//  GalagaShip.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/27/18.
//

#pragma once

#include "GalagaShip.h"
#include "ofMain.h"

GalagaShip::GalagaShip(ofSerial *serial, ofRectangle gameBounds, double x, double y) :SpriteObject(gameBounds)
{
	this->serial = serial;
	setPosition(ofVec2f(x, y));
	setSize(ofVec2f(DEFAULT_WIDTH, DEFAULT_HEIGHT));

	ofRectangle bounds = getBounds();
	double
		gb = gameBounds.getBottom(),
		sb = bounds.getBottom(),
		diff = sb - gb;

	if (diff > 0) {
		bounds.y -= diff;
		setBounds(bounds);
	}

	sprites.push_back(ofImage());
	sprites.push_back(ofImage());

	sprites[0].load("galaga_ship.png");
}

void GalagaShip::update()
{
	ticksSinceInput++;
	//setPosition(ofVec2f(getBounds().x + 5, getBounds().y));
	if (serial->available()) {
		char command = serial->readByte();
		readCommand(command);
		//std::cout << command << std::endl;
	}
	
	if (ticksSinceInput >= 8)
		currMoveDir = '\0';

	ofRectangle b = getBounds();

	switch (currMoveDir) {
	case 'L':
		b.x += -moveSpeed;
		break;
	case 'R':
		b.x += moveSpeed;
		break;
	}

	if (b.x < gameBounds.getLeft())
		b.x = gameBounds.getLeft();
	else if (b.x + b.getWidth() > gameBounds.getRight())
		b.x = gameBounds.getRight() - b.getWidth();

	setBounds(b);
}
void GalagaShip::readCommand(char command) {
	switch (command) {
	case 'B':
		fireMissile();
		break;
	case 'L':
		ticksSinceInput = 0;
		currMoveDir = 'L';
		break;
	case 'R':
		ticksSinceInput = 0;
		currMoveDir = 'R';
		break;
	}
}

void GalagaShip::fireMissile() {
	ofVec2f arg = ofVec2f(getBounds().getCenter().x, getBounds().getTop());
	ofNotifyEvent(firedShot, arg, this);
}

void GalagaShip::draw()
{
	getSprite().draw(getBounds());
}

GalagaShip::~GalagaShip()
{
}

void GalagaShip::keyPressed(int key)
{
}

void GalagaShip::keyReleased(int key)
{
}

void GalagaShip::mouseMoved(int x, int y)
{
}

void GalagaShip::mousePressed(int x, int y, int button)
{
}

void GalagaShip::mouseReleased(int x, int y, int button)
{
}

double GalagaShip::getMoveSpeed()
{
	return moveSpeed;
}

void GalagaShip::setMoveSpeed(double value)
{
	moveSpeed = value;
}
