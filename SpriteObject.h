#pragma once

#include "Drawable.h"
#include "ofImage.h"
#include <vector>
#include "ofMath.h"
#include <functional>
#include <iostream>

class SpriteObject :
	public Drawable
{
public:
	SpriteObject(ofRectangle gameBounds);
	~SpriteObject();

	uint_fast64_t getObjectId();

	ofColor getOverlayColor();
	void setOverlayColor(ofColor color);

	ofImage getSprite();

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);

protected:

	int getSpriteSetStart();
	void setSpriteSetStart(int value);

	int getSpriteSetEnd();
	void setSpriteSetEnd(int value);

	void nextSprite();
	int getTicksperSprite();
	void setTicksPerSprite(int value);

	ofRectangle gameBounds;

	std::vector<ofImage> sprites;
	int spriteIndex = 0;
	int tick=0;

private:

	ofColor overlayColor = ofColor(255, 255, 255);

	int spriteSetStart = 0;
	int spriteSetEnd = 0;

	int ticksPerSprite;
	int lastChangeTick;
	
	uint_fast64_t objectId = reinterpret_cast<uint_fast64_t>(this);
};

