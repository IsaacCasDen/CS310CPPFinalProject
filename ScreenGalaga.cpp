
#include "ScreenGalaga.h"

ScreenGalaga::ScreenGalaga()
{
    
}

ScreenGalaga::ScreenGalaga(Game * game, ofVec2f size) : ScreenGame(game, size)
{
    std::vector<string> devNames;
    devNames.push_back("USB Serial Device");
    devNames.push_back("tty.usbmodem");
    
    ofSerial serial;
    devices = serial.getDeviceList();
    if (devices.size() > 0) {
        for (size_t i = 0; i < devices.size(); i++) {
            //
            // 143101
            for (size_t j = 0; j < devNames.size(); j++) {
                if (devices[i].getDeviceName().find(devNames[j]) != std::string::npos) {
                    if (createPlayerShip(devices[i].getDevicePath(), devices[i].getDeviceID(), i * 50 + 20, getGameBounds().getBottom())) {
                        
                    }
                    break;
                };
            }
        }
    }
    
    createEnemyShips(10);
    hits = *getScores();
    shots = 0;
    misses = 0;
    score = *getScores();
    //lives = *getLives();
    level = getGameLevel();
    sound_hit.load("ship_explosion.mp3");
	sound_hit.setMultiPlay(true);

	createStarField();
}

void ScreenGalaga::createStarField() {
	createStarField(100);
}
void ScreenGalaga::createStarField(int starCount) {
	createStarField(starCount, 3, 6);
}
void ScreenGalaga::createStarField(int starCount, int smallBodySize, int largeBodySize) {
	int largeBodyInterval = starCount / 5;
	if (largeBodyInterval < 5) largeBodyInterval = 5;
	ofRectangle b = getGameBounds();
	for (int i = 0; i < starCount; i++) {
		ofVec3f pos = ofVec3f(ofRandom(b.getLeft(), b.getRight()), ofRandom(b.getTop(), b.getBottom()), 0);
		if (i%largeBodyInterval == 0) {
			pos.z = largeBodySize;
		}
		else {
			pos.z = smallBodySize;
		}
		starField.push_back(pos);
	}
}

bool ScreenGalaga::createPlayerShip(std::string devicePath, int playerId, double x, double y)
{
	ofSerial *serial = new ofSerial();
	if (serial->setup(devicePath, 9600)) {
		GalagaShip *player = new GalagaShip(serial, playerId, getGameBounds(), x, y);
		player->setOverlayColor(
			ofColor(
				ofRandom(128,255),
				ofRandom(128,255),
				ofRandom(128,255)
			)
		);
		ofAddListener(player->firedShot, this, &ScreenGalaga::addPlayerShot);
		//ofAddListener(player->destroyed, this, &ScreenGalaga::removePlayer);
		players.push_back(player);
		return true;
	}
	return false;
}

void ScreenGalaga::createEnemyShips(int count) {

	int row = 0, col = 0;

	while (count > 0) {
		createEnemyShip(col * 52 + 100, row * 50 + 100);
		count--;
		col++;
		if (col > 10) {
			row++;
			col = 0;
		}
	}

}

ScreenGalaga::~ScreenGalaga()
{
	for (int i = 0; i < players.size(); i++)
		delete players[i];

	for (int i = 0; i < playerShot.size(); i++)
		delete playerShot[i];

	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];

	for (int i = 0; i < enemyShot.size(); i++)
		delete enemyShot[i];

	for (int i = 0; i < items.size(); i++)
		delete items[i];
}

void ScreenGalaga::update()
{
	try {
		ScreenGame::update();
		updateBackground();
		updatePlayers();
		updateItems();
		updatePlayerShots();
		updateEnemies();
		updateEnemyShots();
	}
	catch (std::exception& e) {
		std::cout << e.what() << endl;
	}
}

void ScreenGalaga::draw()
{
	drawBackground();
	drawPlayers();
	drawItems();
	drawPlayerShots();
	drawEnemies();
	drawEnemyShots();

	ScreenGame::draw();

    ofSetColor(0,0,0);
    ofDrawBitmapString("Hits: " + std::to_string(hits), 220, 20);
    ofDrawBitmapString("Misses: " + std::to_string(misses), 370, 20);
    ofDrawBitmapString("Shots: " + std::to_string(shots), 520, 20);
    ofDrawBitmapString("Lives: " + std::to_string(lives), 670, 20);
    ofDrawBitmapString("Score: " + std::to_string(score), 820, 20);
    ofDrawBitmapString("Level: " + level, 970, 20);
}

void ScreenGalaga::updateBackground() {
	ofRectangle b = getGameBounds();
	for (int i = 0; i < starField.size(); i++) {
		starField[i].y += 3;
		if (starField[i].y > b.getBottom()) {
			starField[i].y = 0;
			starField[i].x = b.getRight() - starField[i].x;
		}
	}
}

void ScreenGalaga::drawBackground() {
	ofSetColor(ofColor(0, 0, 0));
	ofFill();
	ofDrawRectangle(getGameBounds());

	ofSetColor(ofColor(255, 255, 255));

	for (int i = 0; i < starField.size(); i++) {
		ofDrawLine(starField[i].x, starField[i].y, starField[i].x, starField[i].y + starField[i].z);
	}
}

std::vector<SpriteObject *> ScreenGalaga::cleanVectorItems(std::vector<SpriteObject *> &vec)
{
	std::vector<SpriteObject *> value;
	bool runCleanup;
	do {
		runCleanup = false;
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i]->isDisposed()) {
				SpriteObject * v = removeVectorItem(vec, i);
				if (v != nullptr)
					value.push_back(v);
				runCleanup = true;
				break;
			}
		}
	} while (runCleanup);

	return value;
}

std::vector<Ship *> ScreenGalaga::cleanVectorItems(std::vector<Ship *> &vec)
{
	std::vector<Ship *> value;
	bool runCleanup;
	do {
		runCleanup = false;
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i]->isDisposed()) {
				Ship * v = removeVectorItem(vec, i);
				if (v != nullptr)
					value.push_back(v);
				runCleanup = true;
				break;
			}
		}
	} while (runCleanup);

	return value;
}

Ship * ScreenGalaga::removeVectorItem(std::vector<Ship *> &vec, int index)
{
	Ship * value = nullptr;
	if (index >= 0 && index < vec.size()) {
		value = vec[index];
		if (vec.size() == 1)
			vec.clear();
		else
			vec.erase(vec.begin() + index);
	}
	return value;
}
SpriteObject * ScreenGalaga::removeVectorItem(std::vector<SpriteObject *> &vec, int index)
{
	SpriteObject * value = nullptr;
	if (index >= 0 && index < vec.size()) {
		value = vec[index];
		if (vec.size() == 1)
			vec.clear();
		else
			vec.erase(vec.begin() + index);
	}
	return value;
}

void ScreenGalaga::updatePlayers()
{
	std::vector<Ship * > items = cleanVectorItems(players);
	for (size_t i = 0; i < items.size(); i++) {
		//ofRemoveListener(items[i]->destroyed, this, &ScreenGalaga::removePlayer);
		ofRemoveListener(((GalagaShip*)items[i])->firedShot, this, &ScreenGalaga::addPlayerShot);
	}

	for (size_t i = 0; i < players.size(); i++) {
		players[i]->update();
	}
}

void ScreenGalaga::drawPlayers()
{
	ofSetColor(255);
	for (size_t i = 0; i < players.size(); i++) {
		players[i]->draw();
	}
}

void ScreenGalaga::addPlayerShot(ofVec3f &value) {
	Missile *m = new Missile(getGameBounds(), value.z, -1, value.x, value.y);
	//ofAddListener(m->isOffScreen, this, &ScreenGalaga::removePlayerShot);
	playerShot.push_back(m);
    shots++;
    //misses = shots - hits;    
}

void ScreenGalaga::updatePlayerShots()
{

	cleanVectorItems(playerShot);

    misses = shots - hits;
	bool repeatShot;
	size_t i = 0;
	do {
		repeatShot = false;
		for (i; i < playerShot.size(); i++) {
			playerShot[i]->update();
            
            
			bool repeatEnemy;
			size_t j = 0;
			do {
				repeatEnemy = false;
				for (j; j < enemies.size(); j++) {
					if (enemies[j]->getBounds().intersects(playerShot[i]->getBounds())) {
						enemies[j]->hit();
						repeatEnemy = true;
						repeatShot = true;
                        hits++;
                        sound_hit.play();
                        //*getScores() = *getScores() + 1;
                        score = score + 10;
						break;
					}
				}
			} while (repeatEnemy);
			if (repeatShot) {
				playerShot.erase(playerShot.begin() + i);
				break;
			}
		}
        
	} while (repeatShot);
}

void ScreenGalaga::drawPlayerShots()
{
	ofSetColor(255);
	for (size_t i = 0; i < playerShot.size(); i++) {
		playerShot[i]->draw();
	}
}

void ScreenGalaga::updateItems()
{
	cleanVectorItems(items);

	for (size_t i = 0; i < items.size(); i++) {
		items[i]->update();
	}
}

void ScreenGalaga::drawItems()
{
	ofSetColor(255);
	for (size_t i = 0; i < items.size(); i++) {
		items[i]->draw();
	}
}

void ScreenGalaga::removeEnemy(uint_fast64_t &objectId)
{
	for (size_t i = 0; i < enemies.size(); i++) {
		if (enemies[i]->getObjectId() == objectId) {
			EnemyShip * ship = (EnemyShip *)enemies[i];
			ofRemoveListener(ship->destroyed, this, &ScreenGalaga::removeEnemy);
			ofRemoveListener(ship->firedShot, this, &ScreenGalaga::addEnemyShot);
			enemies.erase(enemies.begin() + i);
		}
	}
}

void ScreenGalaga::updateEnemies()
{
	std::vector<Ship * > items = cleanVectorItems(enemies);
	for (size_t i = 0; i < items.size(); i++) {
		if (((EnemyShip *)items[i])->isActive) {
			active--;
		}
		//ofRemoveListener(items[i]->destroyed, this, &ScreenGalaga::addEnemyShot);
		ofRemoveListener(((EnemyShip*)items[i])->firedShot, this, &ScreenGalaga::addEnemyShot);
	}

	int count = 0;
	while (count<enemies.size() && active < 2 && active < enemies.size() && enemies.size()>0) {
		count++;
		int i = ofRandom(0, enemies.size() - 1);
		if (!((EnemyShip *)enemies[i])->isActive) {
			((EnemyShip *)enemies[i])->isActive = true;
			active++;
		}
	}

	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->update();
		for (size_t j = 0; j < players.size(); j++) {
			if (!enemies[i]->isDestroyed()&&enemies[i]->getBounds().intersects(players[j]->getBounds())) {
				enemies[i]->hit();
				players[j]->hit();
			}
		}
	}
}

void ScreenGalaga::drawEnemies()
{
	ofSetColor(255);
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->draw();
	}
}

void ScreenGalaga::addEnemyShot(ofVec2f &value) {
	Missile *m = new Missile(getGameBounds(), -1, value.x, value.y);
	enemyShot.push_back(m);
	shots++;
	//misses = shots - hits;
	cout << value.y << endl;//value is 622

}

void ScreenGalaga::updateEnemyShots()
{
	cleanVectorItems(enemyShot);

	for (size_t i = 0; i < enemyShot.size(); i++) {
		enemyShot[i]->update();
	}
}

void ScreenGalaga::drawEnemyShots()
{
	ofSetColor(255);
	for (size_t i = 0; i < enemyShot.size(); i++) {
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

void ScreenGalaga::createEnemyShip(double x, double y)
{
	ofRectangle b = getGameBounds();
	EnemyShip *ship = new EnemyShip(getGameBounds(), b.getLeft() + x, b.getTop() - 50);
	enemies.push_back(ship);
	ofAddListener(ship->destroyed, this, &ScreenGalaga::removeEnemy);
	ofAddListener(ship->firedShot, this, &ScreenGalaga::addEnemyShot);
}

void ScreenGalaga::createMissile(double x, double y)
{
}
