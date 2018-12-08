#include "ScreenGalaga.h"



ScreenGalaga::ScreenGalaga()
{
}

ScreenGalaga::ScreenGalaga(Game * game, ofVec2f size) : ScreenGame(game, size)
{
}

ScreenGalaga::~ScreenGalaga()
{
}

void ScreenGalaga::update()
{
	ScreenGame::update();
	updatePlayers();
	updateItems();
	updatePlayerShots();
	updateEnemies();
	updateEnemyShots();
}

void ScreenGalaga::draw()
{
	ScreenGame::draw();
	drawPlayers();
	drawItems();
	drawPlayerShots();
	drawEnemies();
	drawEnemyShots();
}

void ScreenGalaga::updatePlayers()
{
	for (int i = 0; i < players.size(); i++) {
		players[i]->update();
	}
}

void ScreenGalaga::drawPlayers()
{
	for (int i = 0; i < players.size(); i++) {
		players[i]->draw();
	}
}

void ScreenGalaga::updatePlayerShots()
{
	for (int i = 0; i < playerShot.size(); i++) {
		playerShot[i]->update();
	}
}

void ScreenGalaga::drawPlayerShots()
{
	for (int i = 0; i < playerShot.size(); i++) {
		playerShot[i]->draw();
	}
}

void ScreenGalaga::updateItems()
{
	for (int i = 0; i < items.size(); i++) {
		items[i]->update();
	}
}

void ScreenGalaga::drawItems()
{
	for (int i = 0; i < items.size(); i++) {
		items[i]->draw();
	}
}

void ScreenGalaga::updateEnemies()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update();
	}
}

void ScreenGalaga::drawEnemies()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->draw();
	}
}

void ScreenGalaga::updateEnemyShots()
{
	for (int i = 0; i < enemyShot.size(); i++) {
		enemyShot[i]->update();
	}
}

void ScreenGalaga::drawEnemyShots()
{
	for (int i = 0; i < enemyShot.size(); i++) {
		enemyShot[i]->draw();
	}
}

void ScreenGalaga::keyPressed(int key)
{
}

void ScreenGalaga::keyReleased(int key)
{
}

void ScreenGalaga::mouseMoved(int x, int y)
{
}

void ScreenGalaga::mousePressed(int x, int y, int button)
{
}

void ScreenGalaga::mouseReleased(int x, int y, int button)
{
}
