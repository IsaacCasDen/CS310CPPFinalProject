#include "Game.h"

bool Game::hasFontLarge = false;
bool Game::hasFontMedium = false;
bool Game::hasFontSmall = false;

ofTrueTypeFont Game::fontLarge;
ofTrueTypeFont Game::fontMedium;
ofTrueTypeFont Game::fontSmall;

ofColor Game::currentColor;

//
//void Game::loadFontLarge() {
//	fontLarge.load("arial.ttf", 60, true, true);
//	fontLarge.setLineHeight(34.0);
//	fontLarge.setLetterSpacing(1.037);
//}
//void Game::loadFontMedium() {
//	fontMedium.load("arial.ttf", 30, true, true);
//	fontMedium.setLineHeight(18.0f);
//	fontMedium.setLetterSpacing(1.037);
//}
//void Game::loadFontSmall() {
//	fontSmall.load("arial.ttf", 20, true, true);
//	fontSmall.setLineHeight(12.0f);
//	fontSmall.setLetterSpacing(1.037);
//}
//
//ofTrueTypeFont Game::getFontLarge() {
//	return fontLarge;
//}
//
//ofTrueTypeFont Game::getFontMedium() {
//	return fontMedium;
//}
//
//ofTrueTypeFont Game::getFontSmall() {
//	return fontSmall;
//}

ofRectangle Game::getBounds() {
	return bounds;
}

Game::Game() {

}
Game::Game(ofVec2f size) {
    bounds = ofRectangle(0,0,size.x,size.y);
	setActiveScreen(new ScreenMenu(this, ofVec2f(bounds.getWidth(), bounds.getHeight())));
};

void Game::startGame() {};
void Game::exitGame() {
	dispose();
}

void Game::update() {
	if (this->activeScreen!=nullptr) {
		if (this->activeScreen->isClosed()) {
			onGameClosed();
		}
		else {
			if (this->activeScreen->hasPreLoadedScreen()) {
				setActiveScreen(this->activeScreen->takePreLoadedScreen());
			}
			this->activeScreen->update();
		}
	}
};
void Game::draw() {
	if (this->activeScreen!=nullptr) {
		this->activeScreen->draw();
	}
}

void Game::mouseMoved(int x, int y)
{
	if (activeScreen != nullptr) {
		activeScreen->mouseMoved(x, y);
	}
}

void Game::mousePressed(int x, int y, int button)
{
	if (activeScreen != nullptr) {
		activeScreen->mousePressed(x, y, button);
	}
}

void Game::mouseReleased(int x, int y, int button)
{
	if (activeScreen != nullptr) {
		activeScreen->mouseReleased(x, y, button);
	}
}

void Game::dispose() {}
bool Game::isGameRunning()
{
	if (this->activeScreen != nullptr)
		return this->activeScreen->isGameRunning();

	return false;
}
void Game::setGameRunning(bool isRunning)
{
	if (isRunning) {
		ofSetFrameRate(144);
	}
	else {
		ofSetFrameRate(30);
	}
}
void Game::setActiveScreen(Screen * screen)
{
	if (activeScreen != nullptr) {
		ofRemoveListener(activeScreen->closed, this, &Game::onGameClosed);
		delete activeScreen;
	}
	ofAddListener(screen->closed, this, &Game::onGameClosed);
	activeScreen = screen;
}

bool Game::hasScreen()
{
	return activeScreen != nullptr;
}

void Game::onGameClosed()
{
	ofNotifyEvent(closed);
}
