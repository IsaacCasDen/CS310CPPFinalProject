#pragma once
#include "Screen.h"
#include "SpriteObject.h"
#include "ofTrueTypeFont.h"
#include "ofVec2f.h"
#include <vector>

class Game;

class ScreenGame :
	public Screen
{
public:

	/*void loadFontLarge();

	void loadFontMedium();

	void loadFontSmall();*/


	ScreenGame();
	ScreenGame(Game *game, ofVec2f size);
	~ScreenGame();

	void update();
	void draw();

	void drawHeader();

	void drawFooter();

	/*
	void addPlayer();
	void removePlayer();
	*/
	void updatePlayers();
	void drawPlayers();
	
	/*
	void addPlayerShot();
	void removePlayerShot();
	*/
	void updatePlayerShots();
	void drawPlayerShots();
	

	/*
	void addItem();
	void removeItem();
	*/
	void updateItems();
	void drawItems();

	/*
	void AddEnemy();
	void removeEnemy();
	*/
	void updateEnemies();
	void drawEnemies();

	/*
	void AddEnemyShot();
	void removeEnemyShot();
	*/
	void updateEnemyShots();
	void drawEnemyShots();

	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

	

private:
	std::vector<SpriteObject *> enemies;
	std::vector<SpriteObject *> enemyShot;

	std::vector<SpriteObject *> players;
	std::vector<SpriteObject *> playerShot;

	std::vector<SpriteObject *> items;

};

