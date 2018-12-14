#include "Ship.h"
#include "ofMain.h"
#include "ofEvent.h"


Ship::Ship(ofRectangle gameBounds, double x, double y) :SpriteObject(gameBounds)
{
	setPosition(ofVec2f(x, y));
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
	isDisposed(true);
	uint_fast64_t arg = getObjectId();
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
