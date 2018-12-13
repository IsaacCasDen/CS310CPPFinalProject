
//
//  GalagaShip.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/27/18.
//

#pragma once

#include "ofMain.h"
#include "Ship.h"

class GalagaShip : 
	public Ship {
public:

	ofEvent<ofVec3f> firedShot;

	int getPlayerId();

    GalagaShip(ofSerial *serial, int playerId, ofRectangle gameBounds, double x, double y);
	~GalagaShip();
    void update();
	void readCommand(char command);
	void fireMissile();
    void draw();

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

protected:

	double getMoveSpeed();
	void setMoveSpeed(double value);
        
private:

	const double DEFAULT_HEIGHT = 48;
	const double DEFAULT_WIDTH = 48;

	int playerId;
	ofSerial *serial;
    ofSoundPlayer soundShot;
	char currMoveDir = '\0';
	double moveSpeed = 5;
    
	int ticksSinceInput;
};
