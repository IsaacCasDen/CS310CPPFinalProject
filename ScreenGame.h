#pragma once
#include "Screen.h"
#include <vector>
#include "SpriteObject.h"
#include "ofVec2f.h"

class Game;

class ScreenGame :
	public Screen
{
public:
	ScreenGame();
	//ScreenMenu(Game *game, ofVec2f size);
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


private:
	std::vector<SpriteObject *> enemies;
	std::vector<SpriteObject *> enemyShot;

	std::vector<SpriteObject *> players;
	std::vector<SpriteObject *> playerShot;

	std::vector<SpriteObject *> items;

};

