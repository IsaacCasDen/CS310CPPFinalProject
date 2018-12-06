#include "Game.h"

bool Game::hasFontLarge = false;
bool Game::hasFontMedium = false;
bool Game::hasFontSmall = false;

ofTrueTypeFont Game::fontLarge;
ofTrueTypeFont Game::fontMedium;
ofTrueTypeFont Game::fontSmall;

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
	/*loadFontLarge();
	loadFontMedium();
	loadFontSmall();*/

	/*
	ofBackground(0, 0, 0);
	port = serial.setup("/dev/tty.usbmodem143101", 9600);
	if(port)
	{
		cout << "Port OK!" << endl;
	}
	else {
		cout << "Port NOT OK!" << endl;
	}
	
	*/

	loadScreenMenu();
	//loadScreenGame();
};

void Game::startGame() {};

void Game::update() {
	if (newScreen != nullptr || hasScreen()) {
		activeScreen = newScreen;
		newScreen = nullptr;
		hasScreen(false);
	}
	if (activeScreen!=nullptr) {
		activeScreen->update();
	}
};
void Game::draw() {
	if (hasScreen()) {
		activeScreen->draw();
	}
}
void Game::loadScreenMenu()
{
	newScreen = new ScreenMenu(this,ofVec2f(bounds.getWidth(),bounds.getHeight()));
	hasScreen(true);
}

void Game::loadScreenGame()
{
	newScreen = new ScreenGame(this, ofVec2f(bounds.getWidth(), bounds.getHeight()));
	hasScreen(true);
}

void Game::mouseMoved(int x, int y)
{
	if (hasScreen()) {
		activeScreen->mouseMoved(x, y);
	}
}

void Game::mousePressed(int x, int y, int button)
{
	if (hasScreen()) {
		activeScreen->mousePressed(x, y, button);
	}
}

void Game::mouseReleased(int x, int y, int button)
{
	if (hasScreen()) {
		activeScreen->mouseReleased(x, y, button);
	}
}

void Game::exitGame() {
    dispose();
}
void Game::dispose() {}
bool Game::isGameRunning()
{
	return _isGameRunning;
}
void Game::setGameRunning(bool isRunning)
{
	_isGameRunning = isRunning;
}
bool Game::hasScreen()
{
	return currentScreenIndex > lastScreenIndex;
}
void Game::hasScreen(bool value)
{
	if (value) {
		currentScreenIndex++;
	}
	else {
		lastScreenIndex = currentScreenIndex;
	}
}