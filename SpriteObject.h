#pragma once

#include "Drawable.h"
#include "ofImage.h"

class SpriteObject :
	public Drawable
{
public:
	SpriteObject();
	~SpriteObject();

	ofImage getSprite();

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);

private:
	ofImage sprite;
};

