#include "Ship.h"
#include "ofMain.h"
#include "ofEvent.h"


ofVec2f Ship::getBasePosition()
{
	return basePosition;
}
void Ship::setBasePosition(ofVec2f value) {
	basePosition = value;
}

Ship::Ship(ofRectangle gameBounds, ofVec2f position, ofVec2f targetPosition) :SpriteObject(gameBounds)
{
	setPosition(position);
	setBasePosition(targetPosition);
}


Ship::~Ship()
{
}

//void Ship::update()
//{
//}
//
//void Ship::draw()
//{
//}

bool Ship::isDestroyed()
{
	return currDamage >= maxDamage;
}

bool Ship::isGone()
{
	return _isGone;
}

void Ship::isGone(bool value)
{
	_isGone = value;
}

void Ship::addMaxDamage(int healthBonus)
{
	maxDamage += healthBonus;
}

void Ship::addMaxSpeed(double speedBonus)
{
	speed += speedBonus;
}

void Ship::hit()
{
	hit(1);
}

void Ship::hit(int value)
{
	addCurrDamage(value);
}

void Ship::onShipDestroyed()
{
	_destroyed();
	//isDisposed(true);
	//uint_fast64_t arg = getObjectId();
	//ofNotifyEvent(destroyed, arg, this);
}

ofColor Ship::getCurrDamageOverlay()
{
	return ofColor(255,255,255).lerp(maxDamageOverlay,(float)currDamage/maxDamage);
}

ofColor Ship::getMaxDamageOverlay()
{
	return maxDamageOverlay;
}

void Ship::setMaxDamageOverlay(ofColor value)
{
	maxDamageOverlay = value;
}

double Ship::getSpeed()
{
	return speed;
}

void Ship::setSpeed(double value)
{
	speed = value;
}

int Ship::getMaxDamage()
{
	return maxDamage;
}

void Ship::setMaxDamage(int value)
{
	maxDamage = value;
	if (isDestroyed())
		onShipDestroyed();
}

int Ship::getCurrDamage()
{
	return currDamage;
}

void Ship::setCurrDamage(int value)
{
	currDamage = value;
	if (isDestroyed())
		onShipDestroyed();
}

void Ship::addCurrDamage(int value)
{
	currDamage += value;
	if (isDestroyed())
		onShipDestroyed();
}
