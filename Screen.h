#pragma once
//#ifndef SCREEN_H
//#define SCREEN_H

#include "Screen.h"
#include "Drawable.h"
#include "Button.h"
#include "ofTrueTypeFont.h"
#include <string>

class Screen :
	public Drawable
{
public:
	Screen();
	//Screen(Game game, ofVec2f size);
	~Screen();

	//virtual void update() = 0;
	//virtual void draw() = 0;

protected:
	//Game getGame();
	
private:
	//Game game;
	//void setGame(Game game);

};

//#endif