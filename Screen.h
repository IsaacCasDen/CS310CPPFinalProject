#pragma once
//#ifndef SCREEN_H
//#define SCREEN_H

#include "Drawable.h"
#include "ofColor.h"
#include "ofTrueTypeFont.h"
#include <string>
#include "ofVec2f.h"
#include "ofVec3f.h"
#include "ofEvent.h"

class Game;

class Screen :
	public Drawable
{
public:

	ofEvent<void> closed;

	Screen();
	Screen(Game *game, ofVec2f size);
    
	virtual void keyPressed(int key) = 0;
	virtual void keyReleased(int key) = 0;
	virtual void mouseMoved(int x, int y) = 0;
	virtual void mousePressed(int x, int y, int button) = 0;
	virtual void mouseReleased(int x, int y, int button) = 0;
	Screen * takePreLoadedScreen();
	bool hasPreLoadedScreen();
	bool isGameRunning();
	void setGameRunning(bool value);
	bool isClosed();

protected:

	static const int KEY_LEFT = 57356;
	static const int KEY_UP = 57357;
	static const int KEY_RIGHT = 57358;
	static const int KEY_DOWN = 57359;

	const int KEY_SPACE = 32;
	

	Game * getGame();
	void setPreLoadedScreen(Screen * screen);
	void onClosed();
	
private:
	Game * game = nullptr;
	void setGame(Game *game);
	Screen * preLoadedScreen = nullptr;
	bool _isGameRunning = false;
	bool _isClosed = false;

};

//#endif
