#include "Game.h"

ofRectangle Game::getBounds() {
	return bounds;
}

Game::Game() {

}
Game::Game(ofVec2f size) {
    bounds = ofRectangle(0,0,size.x,size.y);
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
	//activeScreen = new ScreenMenu(*this,ofVec2f(bounds.getWidth(),bounds.getHeight()));
	hasScreen(true);
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