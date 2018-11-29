//#ifndef SCREENMENU_H
//#define SCREENMENU_H

#pragma once

#include "Screen.h"

class Game;

class ScreenMenu :
	public Screen
{
public:
	ScreenMenu();
	ScreenMenu(Game *game, ofVec2f size);
	~ScreenMenu();

	void update();
	void draw();

private:
	Button buttonNewGame;
	Button buttonQuit;
};

//#endif