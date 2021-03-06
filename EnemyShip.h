#pragma once
#include "Ship.h"
class EnemyShip :
public Ship
{
public:

	int getPointValue();

	bool isActive = false;

	ofEvent<ofVec2f> firedShot;

	EnemyShip(ofRectangle gameBounds, ofVec2f position, ofVec2f targetPosition);
	void update();
	void draw();
	~EnemyShip();

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

protected:

	bool cycleSprite();
	int getTicksToFire();
	void setTicksToFire(int value);
	bool shouldFire();
	void fire();
	void _destroyed();

	ofVec2f getMovePattern1_NextPos(bool isReflected, ofVec2f currentPos);
	ofVec2f getMovePattern2_NextPos(bool isReflected, ofVec2f currentPos);
	ofVec2f getMovePattern3_NextPos(bool isReflected, ofVec2f currentPos);
	
private:
	const double DEFAULT_HEIGHT = 48;
	const double DEFAULT_WIDTH = 48;

	
	int ticksToFire = 0;
	int tick = 0;
	int movePattern = 0;
	int moveTick = 0;

};
