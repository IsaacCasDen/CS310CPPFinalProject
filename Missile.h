#pragma once

//
//  Missile.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/28/18.
//

#include "SpriteObject.h"
#include "ofMain.h"

class Missile : public SpriteObject
{
public:

	ofEvent<uint_fast64_t> isOffScreen;

	bool isPlayer();
	int getPlayerId();

	Missile(ofRectangle gameBounds, int playerId, int directionY, double x, double y);
    Missile(ofRectangle gameBounds, int directionY, double x, double y);
    void update();
    void draw();

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

protected:
	const double DEFAULT_RADIUS = 4;
	const double DEFAULT_VELX = 0;
	const double DEFAULT_VELY = 10;

private:
	double radius = DEFAULT_RADIUS;
	ofVec2f vel = ofVec2f(DEFAULT_VELX, DEFAULT_VELY);
	int directionY=1;
	bool _isPlayer = false;
	int playerId = -1;
    
};

