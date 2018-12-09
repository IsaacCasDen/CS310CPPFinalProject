
//
//  GalagaShip.h
//  emptyExample
//
//  Created by Travis Olmstead on 11/27/18.
//

#pragma once

#include "ofMain.h"
#include "SpriteObject.h"

class GalagaShip : 
	public SpriteObject {
public:

	ofEvent<ofVec2f> firedShot;

    GalagaShip(ofSerial *serial, ofRectangle gameBounds, double x, double y);
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
	ofSerial *serial;
	char currMoveDir = '\0';
	double moveSpeed = 5;
    
	int ticksSinceInput;
};
