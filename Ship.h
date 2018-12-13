#pragma once
#include "SpriteObject.h"
#include "ofEvent.h"
class Ship : public SpriteObject
{
public:

	ofEvent<uint_fast64_t> destroyed;

	Ship(ofRectangle gameBounds, double x, double y);
	~Ship();

	bool isDestroyed();

	void hit();
	void hit(int value);

	virtual void keyPressed(int key) = 0;
	virtual void keyReleased(int key) = 0;
	virtual void mouseMoved(int x, int y) = 0;
	virtual void mousePressed(int x, int y, int button) = 0;
	virtual void mouseReleased(int x, int y, int button) = 0;

	void onShipDestroyed();

protected:

	ofColor getCurrDamageOverlay();

	ofColor getMaxDamageOverlay();
	void setMaxDamageOverlay(ofColor value);

	int getMaxDamage();
	void setMaxDamage(int value);

	int getCurrDamage();
	void setCurrDamage(int value);
	void addCurrDamage(int value);

private :

	ofColor maxDamageOverlay = ofColor(128, 0, 0);

	int maxDamage = 1;
	int currDamage = 0;

};
