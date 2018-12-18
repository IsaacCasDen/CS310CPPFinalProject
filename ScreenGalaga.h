#pragma once
#include "ScreenGame.h"
#include "ofTrueTypeFont.h"
#include "ofVec2f.h"
#include "ofSerial.h"
#include "SpriteObject.h"
#include "Ship.h"
#include "GalagaShip.h"
#include "EnemyShip.h"
#include "Missile.h"
#include "ofMain.h"
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

	std::vector<SpriteObject *> cleanVectorItems(std::vector<SpriteObject*>& vec);
	std::vector<Ship *> cleanVectorItems(std::vector<Ship*>& vec);

	SpriteObject * removeVectorItem(std::vector<SpriteObject *> &vec, int index);
	Ship * removeVectorItem(std::vector<Ship *> &vec, int index);
	
	void updatePlayers();
	void drawPlayers();

	
	void addPlayerShot(ofVec3f & value);
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
	void removeEnemy(uint_fast64_t & objectId);
	void updateEnemies();
	void drawEnemies();
    int randomEnemy();
	void addEnemyShot(ofVec2f & value);
	void updateEnemyShots();
	void drawEnemyShots();

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

protected:

	void createEnemyShip(double x, double y);
	bool createPlayerShip(std::string devicePath, int playerId, double x, double y);
	void createMissile(double x, double y);

private:
	//std::recursive_mutex lock;

	std::vector<Ship *> enemies;
	std::vector<SpriteObject *> enemyShot;

	std::vector<Ship *> players;
	std::vector<SpriteObject *> playerShot;

	std::vector<SpriteObject *> items;

	std::vector<ofSerialDeviceInfo> devices;

    int hits;
    int misses;
    int score;
    int lives;
    //Missile miss;
    ofVec2f pos;
    ofSoundPlayer sound_hit;
    int shots;
    string level;
    bool isMoving;
    int index;
    //GalagaShip *galaga_miss;
};
