#pragma once
//#ifndef SCREEN_H
//#define SCREEN_H

#include "Drawable.h"
#include "ofColor.h"
//#include "Button.h"
#include "ofTrueTypeFont.h"
#include <string>
#include "ofVec2f.h"
#include "ofVec3f.h"

class Game;

class Screen :
	public Drawable
{
public:
	Screen();
	Screen(Game *game, ofVec2f size);
	~Screen();

	virtual void mouseMoved(int x, int y) = 0;
	virtual void mousePressed(int x, int y, int button) = 0;
	virtual void mouseReleased(int x, int y, int button) = 0;

protected:
	Game * getGame();
	
private:
	Game * game;
	void setGame(Game *game);

};

//#endif