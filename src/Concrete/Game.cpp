#include "Game.h"
#include "ofVec2f.h"

ofRectangle Game::getBounds() {
	return bounds;
}

Game::Game(ofVec2f size) {
    bounds = ofRectangle(0,0,size.x,size.y);
};

void Game::startGame() {};

void Game::updateGame() {};
void Game::drawGame() {};

void Game::exitGame() {
    dispose();
};
void Game::dispose() {};