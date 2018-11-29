#include "Drawable.h"

Drawable::Drawable()
{
}


Drawable::~Drawable()
{
}

bool Drawable::isIntersecting(int x, int y)
{
	return isIntersecting(ofVec2f(x,y));
}

bool Drawable::isIntersecting(ofVec2f point)
{
	return getBounds().inside(point);
}

ofRectangle Drawable::getBounds()
{
	return this->bounds;
}

void Drawable::setPosition(ofVec2f position)
{
	bounds.x = position.x;
	bounds.y = position.y;
}

void Drawable::setSize(ofVec2f size)
{
	this->bounds = ofRectangle(bounds.x, bounds.y, size.x, size.y);
}

void Drawable::setBounds(ofRectangle bounds)
{
	this->bounds = bounds;
}
