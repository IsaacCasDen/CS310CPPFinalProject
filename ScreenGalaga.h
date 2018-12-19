#pragma once
#include "ScreenGame.h"
#include "Drawable.h"
#include "Button.h"
#include "Controller.h"
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
	void updateControllers();
	~ScreenGalaga();

	virtual void update();
	
	void draw();

	

	void updateBackground();

	void drawBackground();

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
	bool createPlayerShip(Controller * controller, int playerId, ofColor playerColor, double x, double y);

private:
	void loadSounds();
	void loadMenu();
	void startGame();
	void loadGame();
	void createStarField();
	void createStarField(int starCount);
	void createStarField(int starCount, int smallBodySize, int largeBodySize);
	void createEnemyShips(int count);

	void updateMenu();
	void updateGame();

	void drawMenu();
	void drawGame();

	std::vector<Ship *> enemies;
	std::vector<SpriteObject *> enemyShot;

	std::vector<Ship *> players;
	std::vector<SpriteObject *> playerShot;

	std::vector<SpriteObject *> items;

	int active = 0;

    int hits;
    int misses;
    int score;
    int lives;
    //Missile miss;
    ofVec2f pos;

	ofSoundPlayer soundShoot;
    ofSoundPlayer soundExplosion;

    int shots;
    string level;
    
	std::vector<ofVec3f> starField;

	bool gameRunning = false;
	double menuTick = 0;

	Button buttonStartGame;
	ofImage logo;
	ofRectangle logoBounds;
	std::vector<Controller *> controllers;
	std::vector<bool> activePlayers;
	std::vector<ofColor> playerColor;

	ofTrueTypeFont font;
};

