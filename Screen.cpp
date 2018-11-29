#include "Screen.h"
#include "Game.h"

Screen::Screen()
{
}

Screen::Screen(Game *game, ofVec2f size)
{
	setSize(size);
	setGame(game);
}

Screen::~Screen()
{
}

Game * Screen::getGame()
{
	return game;
}

void Screen::setGame(Game *game)
{
	this->game = game;
}
