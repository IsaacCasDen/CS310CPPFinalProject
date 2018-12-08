#pragma once

#include "ofRectangle.h"
#include "ofVec2f.h"

class Drawable
{
public:
	Drawable();
	~Drawable();

	virtual void update()=0;
	virtual void draw()=0;

	virtual void keyPressed(int key)=0;
	virtual void keyReleased(int key)=0;
	virtual void mouseMoved(int x, int y)=0;
	virtual void mousePressed(int x, int y, int button)=0;
	virtual void mouseReleased(int x, int y, int button)=0;

	bool isIntersecting(int x, int y);
	bool isIntersecting(ofVec2f point);

	virtual ofRectangle getBounds();
	virtual void setPosition(ofVec2f position);

protected:
	
	void setSize(ofVec2f size);
	virtual void setBounds(ofRectangle bounds);

private:
	ofRectangle bounds;
};

