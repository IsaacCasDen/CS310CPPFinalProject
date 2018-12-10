#include "ScreenMenu.h"
#include "Game.h"

ScreenMenu::ScreenMenu()
{
}

ScreenMenu::ScreenMenu(Game *game, ofVec2f size) : Screen(game,size)
{
	ofVec3f area = game->getBounds().getCenter();
	buttonPlayGalaga = Button("Play Galaga", 20);
	buttonPlayGalaga.setWidth(200);
	buttonPlayGalaga.setHeight(50);
	buttonPlayGalaga.setPosition(ofVec2f(area.x-buttonPlayGalaga.getBounds().width/2, 100));
	ofAddListener(buttonPlayGalaga.clicked, this, &ScreenMenu::onButtonPlayGalagaClicked);
	buttons.push_back(&buttonPlayGalaga);

	buttonPlaySnake = Button("Play Snake", 20);
	buttonPlaySnake.setWidth(200);
	buttonPlaySnake.setHeight(50);
	buttonPlaySnake.setPosition(ofVec2f(area.x - buttonPlaySnake.getBounds().width / 2, buttonPlayGalaga.getBounds().getBottom() + 10));
	ofAddListener(buttonPlaySnake.clicked, this, &ScreenMenu::onButtonPlaySnakeClicked);
	buttons.push_back(&buttonPlaySnake);

	buttonQuit = Button("Quit", 20);
	buttonQuit.setWidth(200);
	buttonQuit.setHeight(50);
	buttonQuit.setPosition(ofVec2f(area.x - buttonQuit.getBounds().width / 2, buttonPlaySnake.getBounds().getBottom() + 10));
	ofAddListener(buttonQuit.clicked, this, &ScreenMenu::onButtonQuitClicked);
	buttons.push_back(&buttonQuit);
	
}

ScreenMenu::~ScreenMenu()
{
	ofRemoveListener(buttonPlayGalaga.clicked, this, &ScreenMenu::onButtonPlayGalagaClicked);
	ofRemoveListener(buttonQuit.clicked, this, &ScreenMenu::onButtonQuitClicked);
}

void ScreenMenu::keyPressed(int key)
{
}

void ScreenMenu::keyReleased(int key)
{
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
	Screen * screen;
	switch (newScreenType) {
	case 1:
		screen = new ScreenGalaga(getGame(), ofVec2f(getBounds().getWidth(), getBounds().getHeight()));
		screen->setGameRunning(true);
		setPreLoadedScreen(screen);
		newScreenType = -1;
		break;
	case 2:
		screen = new ScreenSnake(getGame(), ofVec2f(getBounds().getWidth(), getBounds().getHeight()));
		screen->setGameRunning(true);
		setPreLoadedScreen(screen);
		newScreenType = -1;
		break;
    default:
        break;
	}
	
}

void ScreenMenu::draw()
{
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->draw();
	}
}

void ScreenMenu::onButtonPlayGalagaClicked()
{
	newScreenType = 1;
}

void ScreenMenu::onButtonPlaySnakeClicked()
{
	newScreenType = 2;
}

void ScreenMenu::onButtonQuitClicked()
{
	this->onClosed();
}
