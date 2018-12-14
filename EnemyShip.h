#pragma once
#include "Ship.h"
class EnemyShip : 
	public Ship
{
public:

	ofEvent<ofVec2f> firedShot;

	EnemyShip(ofRectangle gameBounds, double x, double y);
    EnemyShip();
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
	
private:
	const double DEFAULT_HEIGHT = 48;
	const double DEFAULT_WIDTH = 48;

	int ticksToFire = 0;
	int tick = 0;
};

