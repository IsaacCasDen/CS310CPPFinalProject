#pragma once
//#ifndef SCREEN_H
//#define SCREEN_H

#include "Screen.h"
#include "Drawable.h"
#include "Button.h"
#include "ofTrueTypeFont.h"
#include <string>

class Game;

class Screen :
	public Drawable
{
public:
	Screen();
	Screen(Game *game, ofVec2f size);
	~Screen();

protected:
	Game * getGame();
	
private:
	Game * game;
	void setGame(Game *game);

};

//#endif