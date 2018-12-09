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


Screen * Screen::takePreLoadedScreen()
{
	Screen * value = preLoadedScreen;
	preLoadedScreen=nullptr;
	return value;
}

bool Screen::hasPreLoadedScreen()
{
	return preLoadedScreen!=nullptr;
}

bool Screen::isGameRunning()
{
	return _isGameRunning;
}

void Screen::setGameRunning(bool value)
{
	_isGameRunning = value;
}

bool Screen::isClosed()
{
	return _isClosed;
}

Game * Screen::getGame()
{
	return game;
}

void Screen::setPreLoadedScreen(Screen * screen)
{
	preLoadedScreen = screen;
}

void Screen::onClosed()
{
	_isClosed = true;
}


void Screen::setGame(Game *game)
{
	this->game = game;
}


