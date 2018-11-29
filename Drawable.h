//#ifndef DRAWABLE_H
//#define DRAWABLE_H

#pragma once

#include "ofMain.h"

class Drawable
{
public:
	Drawable();
	~Drawable();

	virtual void update()=0;
	virtual void draw()=0;

	ofRectangle getBounds();
	void setPosition(ofVec2f position);

protected:
	
	void setSize(ofVec2f size);
	void setBounds(ofRectangle bounds);

private:
	ofRectangle bounds;
};

//#endif 
