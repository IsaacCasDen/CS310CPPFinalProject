
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

bool GalagaShip::isController(Controller * controller)
{
	return controller == this->controller;
}

GalagaShip::GalagaShip(Controller * controller, int playerId, ofRectangle gameBounds, ofVec2f position, ofVec2f targetPosition) :Ship(gameBounds, position, targetPosition)
{
	this->controller = controller;
	this->playerId = playerId;
	setSize(ofVec2f(DEFAULT_WIDTH, DEFAULT_HEIGHT));
	setCurrDamage(0);
	setMaxDamage(3);
	_lives = 2;

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
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());

	sprites[0].load("sprites/galaga_ship.png");
	sprites[1].load("sprites/explode_1.gif");
	sprites[2].load("sprites/explode_2.gif");
	sprites[3].load("sprites/explode_3.gif");
	sprites[4].load("sprites/explode_4.gif");
	sprites[5].load("sprites/explode_5.gif");
	sprites[6].load("sprites/explode_6.gif");
	sprites[7].load("sprites/explode_7.gif");
	sprites[8].load("sprites/explode_8.gif");
}
GalagaShip::~GalagaShip()
{
	controller->getSerial()->close();
}

bool GalagaShip::cycleSprite()
{
	return getTicksperSprite() < tick;
}

void GalagaShip::update()
{
	if (isGone()) {
		if (getLifeCount() >= 0) {
			if (_respawnTick < _respawnTicks)
				_respawnTick++;
			else {
				setCurrDamage(0);
				spriteIndex = 0;
				setSpriteSetStart(0);
				setSpriteSetEnd(0);
				//setPosition(getBasePosition());
				isGone(false);
				update();
			}
		}
	}
	else {
		if (cycleSprite()) {
			tick = 0;
			nextSprite();
		}
		else
			tick++;

		ticksSinceInput++;
		//setPosition(ofVec2f(getBounds().x + 5, getBounds().y));
		try {
			if (controller->getSerial()->available()) {
				char command = controller->getSerial()->readByte();
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
	if (isGone()) return;
	ofSetColor(getOverlayColor().lerp(getCurrDamageOverlay(),0.5f));
	getSprite().draw(getBounds());
	if (spriteIndex == 8)
	{
		_respawnTick = 0;
		isGone(true);
	}
}

void GalagaShip::reset()
{
	_lives = 2;
	_score = 0;
	setCurrDamage(0);
	setSpriteSetStart(0);
	setSpriteSetEnd(0);
	spriteIndex = 0;
}

int GalagaShip::getLifeCount()
{
	return _lives;
}

void GalagaShip::addLife()
{
	addLife(1);
}

void GalagaShip::addLife(int count)
{
	_lives += count;
}

void GalagaShip::removeLife()
{
	_lives -= 1;
}

int GalagaShip::getScore()
{
	return _score;
}

void GalagaShip::setScore(int value)
{
	_score = value;
}

void GalagaShip::addScore(int value)
{
	_score += value;
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
	setTicksPerSprite(ofGetFrameRate() / 6);
	setSpriteSetStart(1);
	setSpriteSetEnd(8);
	removeLife();
}
