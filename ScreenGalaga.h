#pragma once
#include "ScreenGame.h"
#include "ofTrueTypeFont.h"
#include "ofVec2f.h"
#include "ofSerial.h"
#include "SpriteObject.h"
#include "GalagaShip.h"
#include "EnemyShip.h"
#include "Missile.h"
#include <vector>
class ScreenGalaga :
	public ScreenGame
{
public:
	ScreenGalaga();
	ScreenGalaga(Game *game, ofVec2f size);
	void createEnemyShips(int count);
	~ScreenGalaga();

	virtual void update();
	void draw();

	
	void updatePlayers();
	void drawPlayers();

	
	void addPlayerShot(ofVec2f &value);
	void removePlayerShot(Missile &value);
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
	*/
	void removeEnemy(EnemyShip &value);
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

protected:

	void createEnemyShip(double x, double y);
	bool createPlayerShip(std::string devicePath, double x, double y);
	void createMissile(double x, double y);

private:
	std::vector<SpriteObject *> enemies;
	std::vector<SpriteObject *> enemyShot;

	std::vector<SpriteObject *> players;
	std::vector<SpriteObject *> playerShot;

	std::vector<SpriteObject *> items;

	std::vector<ofSerialDeviceInfo> devices;
};

