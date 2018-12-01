#include "ScreenGame.h"
//#include "Game.h"


ScreenGame::ScreenGame()
{
	
}
/*
ScreenMenu::ScreenMenu(Game *game, ofVec2f size) : Screen(game, size)
{
	/*
	for(int i=0; i<1; i++)
	{
		galaga_ship.push_back(new GalagaShip());
	}//create new ship and push it into the vector
	for (int i=0; i<1; i++) {
		missiles.push_back(new Missile());
	}//create new missiles and push them into the vector
	for(int j=0; j<galaga_ship.size(); j++)
	{
		galaga_ship[j]->setup();
	}//setup ship
	for (int i=0; i<missiles.size(); i++) {
		missiles[i]->setup();
	}//setup missiles
	
}
*/


ScreenGame::~ScreenGame()
{
}

void ScreenGame::update()
{
	
	

	updatePlayers();
	updateItems();
	updatePlayerShots();
	drawEnemies();
	drawEnemyShots();
}

void ScreenGame::draw()
{
	drawPlayers();
	drawItems();
	drawPlayerShots();
	drawEnemies();
	drawEnemyShots();
}

void ScreenGame::drawHeader() {
	ofRectangle bounds = getBounds();
	ofVec3f v = bounds.getCenter();
	//getGame()->getFontSmall().drawString("Level 1", bounds.getCenter().x - getGame()->getFontSmall().stringWidth("Level 1") / 2, getGame()->getFontSmall().stringHeight("Level 1") + 3);
}

void ScreenGame::drawFooter() {

}

void ScreenGame::updatePlayers()
{
	/*
	for (int i=0; i<galaga_ship.size(); i++)
	{
		char c;
		if(serial.available())
		{
			c = serial.readByte();
			galaga_ship[i]->update(c);

		}//if serial is available
	}//for loop cycling through galaga ship vector
	*/

	for (int i = 0; i < players.size(); i++) {
		players[i]->update();
	}
}

void ScreenGame::drawPlayers()
{
	/*
	for (int i=0; i<galaga_ship.size(); i++) {
		char c;
		galaga_ship[i]->draw();
	}
	*/
	for (int i = 0; i < players.size(); i++) {
		players[i]->draw();
	}
}

void ScreenGame::updatePlayerShots()
{
	/*
	for(int i=0; i<missiles.size(); i++)
	{
		char c;
		if(serial.available())
		{
			c = serial.readByte();
			missiles[i]->update(c);
			cout << c << endl;
		}
	}
	*/

	for (int i = 0; i < playerShot.size(); i++) {
		playerShot[i]->update();
	}
}

void ScreenGame::drawPlayerShots()
{
	/*
	for (int i=0; i<missiles.size(); i++) {
		char c;
		missiles[i]->draw(c);
	}
	*/
	for (int i = 0; i < playerShot.size(); i++) {
		playerShot[i]->draw();
	}
}

void ScreenGame::updateItems()
{
	for (int i = 0; i < items.size(); i++) {
		items[i]->update();
	}
}

void ScreenGame::drawItems()
{
	for (int i = 0; i < items.size(); i++) {
		items[i]->draw();
	}
}

void ScreenGame::updateEnemies()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update();
	}
}

void ScreenGame::drawEnemies()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->draw();
	}
}

void ScreenGame::updateEnemyShots()
{
	for (int i = 0; i < enemyShot.size(); i++) {
		enemyShot[i]->update();
	}
}

void ScreenGame::drawEnemyShots()
{
	for (int i = 0; i < enemyShot.size(); i++) {
		enemyShot[i]->draw();
	}
}
