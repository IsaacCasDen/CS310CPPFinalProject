#pragma once
#include "Drawable.h"
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

