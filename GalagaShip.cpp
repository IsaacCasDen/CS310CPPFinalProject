
//
//  GalagaShip.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/27/18.
//

#pragma once

#include "GalagaShip.h"
#include "ofMain.h"

int GalagaShip::getPlayerId()
{
	return playerId;
}

GalagaShip::GalagaShip(ofSerial *serial, int playerId, ofRectangle gameBounds, double x, double y) :Ship(gameBounds, x, y)
{
	this->serial = serial;
	this->playerId = playerId;
	setSize(ofVec2f(DEFAULT_WIDTH, DEFAULT_HEIGHT));
	setMaxDamage(10);

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

	sprites[0].load("galaga_ship.png");
    soundShot.load("ship_shot.mp3");
	soundShot.setMultiPlay(true);
}
GalagaShip::~GalagaShip()
{
	serial->close();
}

void GalagaShip::update()
{
	ticksSinceInput++;
	//setPosition(ofVec2f(getBounds().x + 5, getBounds().y));
	try {
		if (serial->available()) {
			char command = serial->readByte();
			readCommand(command);
			//std::cout << command << std::endl;
		}
	}
	catch (...) {

	}
	
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
        soundShot.play();
		break;
	case 'L':
		ticksSinceInput = 0;
		currMoveDir = 'L';
		break;
	case 'R':
		ticksSinceInput = 0;
		currMoveDir = 'R';
		break;
	case 'N':
		ticksSinceInput = 0;
		currMoveDir = '\0';
		break;
	}
}

void GalagaShip::fireMissile() {
	ofVec3f arg = ofVec3f(getBounds().getCenter().x, getBounds().getTop(), getPlayerId());
	ofNotifyEvent(firedShot, arg, this);
}

void GalagaShip::draw()
{
	ofSetColor(getOverlayColor().lerp(getCurrDamageOverlay(),0.5f));
	getSprite().draw(getBounds());
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

void GalagaShip::_destroyed()
{
}
