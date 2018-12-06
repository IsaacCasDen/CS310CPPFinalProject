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

private:
	ofImage sprite;
};

