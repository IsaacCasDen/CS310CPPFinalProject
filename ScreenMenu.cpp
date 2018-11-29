#include "ScreenMenu.h"
#include "Game.h"

ScreenMenu::ScreenMenu()
{
}

ScreenMenu::ScreenMenu(Game *game, ofVec2f size) : Screen(game,size)
{
	buttonNewGame = Button("New Game", 20);
	buttonNewGame.setPosition(ofVec2f(100, 100));
	buttonNewGame.setWidth(200);
	buttonNewGame.setHeight(50);

	buttonQuit = Button("Quit", 20);
	buttonQuit.setPosition(ofVec2f(buttonNewGame.getBounds().getLeft(), buttonNewGame.getBounds().getBottom() + 10));
	buttonQuit.setWidth(200);
	buttonQuit.setHeight(50);
	
}

ScreenMenu::~ScreenMenu()
{
}

void ScreenMenu::update()
{
}

void ScreenMenu::draw()
{
	buttonNewGame.draw();
	buttonQuit.draw();
}
