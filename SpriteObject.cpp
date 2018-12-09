#include "SpriteObject.h"



SpriteObject::SpriteObject(ofRectangle gameBounds)
{
	this->gameBounds = gameBounds;
}

SpriteObject::~SpriteObject()
{
}

ofImage SpriteObject::getSprite()
{
	ofImage value;

	if (sprites.size() > spriteIndex) {
		value = sprites[spriteIndex];
	}

	return value;
}

void SpriteObject::keyPressed(int key)
{
}

void SpriteObject::keyReleased(int key)
{
}

void SpriteObject::nextSprite()
{
	if (sprites.size() > 0) {
		spriteIndex = (spriteIndex + 1) % sprites.size();
	}
}

int SpriteObject::getTicksperSprite()
{
	return ticksPerSprite;
}

void SpriteObject::setTicksPerSprite(int value)
{
	ticksPerSprite = value;
}
