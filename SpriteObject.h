#pragma once

#include "Drawable.h"
#include "ofImage.h"
#include <vector>

class SpriteObject :
	public Drawable
{
public:
	SpriteObject(ofRectangle gameBounds);
	~SpriteObject();

	ofImage getSprite();

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);

protected:

	void nextSprite();
	int getTicksperSprite();
	void setTicksPerSprite(int value);

	ofRectangle gameBounds;

	std::vector<ofImage> sprites;
	int spriteIndex = 0;
	int tick=0;

private:

	int ticksPerSprite;
	int lastChangeTick;
	
};

