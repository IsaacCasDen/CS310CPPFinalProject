//#ifndef SCREENMENU_H
//#define SCREENMENU_H

#pragma once

#include "Button.h"
#include "Screen.h"
#include "Drawable.h"
#include <vector>

class Game;

class ScreenMenu :
	public Screen
{
public:
	ScreenMenu();
	ScreenMenu(Game *game, ofVec2f size);
	~ScreenMenu();

	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

	void update();
	void draw();

protected:
	void onButtonNewGameClicked();
	void onButtonQuitClicked();

private:
	Button buttonNewGame;
	Button buttonQuit;
	std::vector<Drawable *> buttons;
	int newScreenType = -1;
};

//#endif