#pragma once
#include "ScreenGame.h"
#include "ofTrueTypeFont.h"
#include "ofVec2f.h"
#include <vector>
class ScreenGalaga :
	public ScreenGame
{
public:
	ScreenGalaga();
	ScreenGalaga(Game *game, ofVec2f size);
	~ScreenGalaga();

	virtual void update();
	void draw();

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

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
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

