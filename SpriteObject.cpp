#include "SpriteObject.h"

ofColor SpriteObject::getOverlayColor()
{
	return overlayColor;
}

void SpriteObject::setOverlayColor(ofColor color)
{
	overlayColor = color;
}

SpriteObject::SpriteObject(ofRectangle gameBounds)
{
	this->gameBounds = gameBounds;
}


uint_fast64_t SpriteObject::getObjectId()
{
	return objectId;
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

int SpriteObject::getSpriteSetStart()
{
	return spriteSetStart;
}

void SpriteObject::setSpriteSetStart(int value)
{
	if (value < sprites.size() && value >= 0)
		spriteSetStart = value;
}

int SpriteObject::getSpriteSetEnd()
{
	return spriteSetEnd;
}

void SpriteObject::setSpriteSetEnd(int value)
{
	if (value < sprites.size() && value >= 0)
		spriteSetEnd = value;
}

void SpriteObject::nextSprite()
{
	if (sprites.size() > 0 && (spriteSetEnd - spriteSetStart) > 1) {
		spriteIndex++;
		//spriteIndex = spriteIndex % (spriteSetEnd + 1 < sprites.size()) ? spriteSetEnd + 1 : sprites.size();
		if ((spriteSetEnd + 1 < sprites.size()))
			spriteIndex = spriteIndex %  spriteSetEnd + 1;
		else
			spriteIndex = spriteIndex % sprites.size();
		
		if (spriteIndex < spriteSetStart)
			spriteIndex = spriteSetStart + (abs(spriteSetStart - spriteIndex));
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
