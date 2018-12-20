#pragma once
#include "SpriteObject.h"
#include "ofEvent.h"
class Ship : public SpriteObject
{
public:

	ofEvent<uint_fast64_t> destroyed;

	ofVec2f getBasePosition();

	void setBasePosition(ofVec2f value);

	Ship(ofRectangle gameBounds, ofVec2f position, ofVec2f targetPosition);
	~Ship();

	bool isDestroyed();
	bool isGone();
	void isGone(bool value);

	void addMaxDamage(int healthBonus);
	void addMaxSpeed(double speedBonus);

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

	double getSpeed();
	void setSpeed(double value);

	int getMaxDamage();
	void setMaxDamage(int value);

	int getCurrDamage();
	void setCurrDamage(int value);
	void addCurrDamage(int value);

	virtual void _destroyed() = 0;

private :

	ofVec2f basePosition = ofVec2f(0, 0);

	ofColor maxDamageOverlay = ofColor(128, 0, 0);

	int maxDamage = 1;
	int currDamage = 0;

	double speed = 3;

	bool _isGone = false;;

};
