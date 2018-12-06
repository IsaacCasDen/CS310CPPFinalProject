#include "ScreenMenu.h"
#include "Game.h"

ScreenMenu::ScreenMenu()
{
}

ScreenMenu::ScreenMenu(Game *game, ofVec2f size) : Screen(game,size)
{
	std::cout << this->getGame();
	ofVec3f area = game->getBounds().getCenter();
	buttonNewGame = Button("New Game", 20);
	buttonNewGame.setWidth(200);
	buttonNewGame.setHeight(50);
	buttonNewGame.setPosition(ofVec2f(area.x-buttonNewGame.getBounds().width/2, 100));
	ofAddListener(buttonNewGame.clicked, this, &ScreenMenu::onButtonNewGameClicked);
	buttons.push_back(&buttonNewGame);

	buttonQuit = Button("Quit", 20);
	buttonQuit.setWidth(200);
	buttonQuit.setHeight(50);
	buttonQuit.setPosition(ofVec2f(area.x - buttonQuit.getBounds().width / 2, buttonNewGame.getBounds().getBottom() + 10));
	ofAddListener(buttonQuit.clicked, this, &ScreenMenu::onButtonQuitClicked);
	buttons.push_back(&buttonQuit);
	
}

ScreenMenu::~ScreenMenu()
{
	ofRemoveListener(buttonNewGame.clicked, this, &ScreenMenu::onButtonNewGameClicked);
	ofRemoveListener(buttonQuit.clicked, this, &ScreenMenu::onButtonQuitClicked);
}

void ScreenMenu::mouseMoved(int x, int y)
{
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->mouseMoved(x, y);
	}
}

void ScreenMenu::mousePressed(int x, int y, int button)
{
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->mousePressed(x, y, button);
	}
}

void ScreenMenu::mouseReleased(int x, int y, int button)
{
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->mouseReleased(x, y, button);
	}
}

void ScreenMenu::update()
{
	switch (newScreenType) {
	case 1:
		Screen * screen = new ScreenGame(getGame(), ofVec2f(getBounds().getWidth(), getBounds().getHeight()));
		screen->setGameRunning(true);
		setPreLoadedScreen(screen);
		newScreenType = -1;
	}
	
}

void ScreenMenu::draw()
{
	buttonNewGame.draw();
	buttonQuit.draw();
}

void ScreenMenu::onButtonNewGameClicked()
{
	
	newScreenType = 1;
}

void ScreenMenu::onButtonQuitClicked()
{
	this->onClosed();
}
