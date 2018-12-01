#include "Game.h"

ofRectangle Game::getBounds() {
	return bounds;
}

Game::Game() {

}
Game::Game(ofVec2f size) {
    bounds = ofRectangle(0,0,size.x,size.y);

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
};

void Game::startGame() {};

void Game::update() {
	if (hasScreen()) {
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
	activeScreen = new ScreenMenu(this,ofVec2f(bounds.getWidth(),bounds.getHeight()));
	hasScreen(true);
}

void Game::loadScreenGame()
{
	//activeScreen = new loadScreenGame(this, ofVec2f(bounds.getWidth(), bounds.getHeight()));
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
	return _hasScreen;
}
void Game::hasScreen(bool value)
{
	_hasScreen = value;
}