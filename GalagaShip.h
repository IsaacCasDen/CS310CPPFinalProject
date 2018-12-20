
//
//  GalagaShip.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/27/18.
//

#pragma once

#include "ofMain.h"
#include "Ship.h"
#include "Controller.h"

class GalagaShip : 
	public Ship {
public:

	ofEvent<ofVec3f> firedShot;

	int getPlayerId();
	bool isController(Controller * controller);

    GalagaShip(Controller * controller, int playerId, ofRectangle gameBounds, ofVec2f position, ofVec2f targetPosition);
	~GalagaShip();
	bool cycleSprite();
    void update();
	void readCommand(char command);
	void fireMissile();
    void draw();

	void reset();

	int getLifeCount();
	void addLife();
	void addLife(int count);
	void removeLife();

	int getScore();
	void setScore(int value);
	void addScore(int value);

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

protected:

	double getMoveSpeed();
	void setMoveSpeed(double value);

	void _destroyed();
        
private:

	const double DEFAULT_HEIGHT = 48;
	const double DEFAULT_WIDTH = 48;

	int playerId;
	Controller * controller;
	char currMoveDir = '\0';
	double moveSpeed = 5;
    
	int ticksSinceInput;

	int _score = 0;
	int _lives = 2;
	int _respawnTicks = 120;
	int _respawnTick = 0;
};
