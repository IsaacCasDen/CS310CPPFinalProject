#pragma once
#include "SpriteObject.h"
#include "ofPoint.h"
class EnemyShip : 
	public SpriteObject
{
public:

	EnemyShip(ofRectangle gameBounds, double x, double y);
	void update();
	void draw();
	~EnemyShip();
    void interpolate(float percent);
	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

protected:

	bool cycleSprite();
	
private:
	const double DEFAULT_HEIGHT = 48;
	const double DEFAULT_WIDTH = 48;
    int t=0;
    ofPoint posA;
    ofPoint posB;
    float pct;
    float xpos;
    float ypos;
    float curve;

};

