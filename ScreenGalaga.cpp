
#include "ScreenGalaga.h"

ScreenGalaga::ScreenGalaga()
{
    
}

ScreenGalaga::ScreenGalaga(Game * game, ofVec2f size) : ScreenGame(game, size)
{
	font.load("fonts/emulogic.ttf", 24, true, true);
    createEnemyShips(20);
    hits = *getScores();
    shots = 0;
    misses = 0;
    score = *getScores();
    //lives = *getLives();
    level = getGameLevel();

	createStarField();

	loadSounds();
	loadMenu();

}
void ScreenGalaga::updateControllers() {
	/*
	if (createPlayerShip(devices[i].getDevicePath(), devices[i].getDeviceID(), i * 50 + 20, getGameBounds().getBottom())) {
	}
	*/
	ofSerial serial;
	std::vector<string> devNames;
	
	devNames.push_back("USB Serial Device");
	devNames.push_back("tty.usbmodem");

	std::vector<ofSerialDeviceInfo> devices = serial.getDeviceList();
	if (devices.size() > 0) {
		for (size_t i = 0; i < devices.size(); i++) {
			//
			// 143101
			for (size_t j = 0; j < devNames.size(); j++) {
				if (devices[i].getDeviceName().find(devNames[j]) != std::string::npos) {
					bool hasDevice = false;
					for (size_t k = 0; k < controllers.size(); k++) {
						if (controllers[k]->getDeviceId() == devices[i].getDeviceID()) {
							hasDevice = true;
							/*
								Controller * controller = new Controller(devices[i], 9600);
								if (controller->isSetup())
									controllers[k] = controller;
							*/
							break;
						}
					}
					if (!hasDevice) {
						Controller * controller = new Controller(devices[i], 9600);
						if (controller->isSetup()) {
							controllers.push_back(controller);
							activePlayers.push_back(false);
							playerColor.push_back(
								ofColor(
									ofRandom(128, 255),
									ofRandom(128, 255),
									ofRandom(128, 255)
								)
							);
						}
					}
					break;
				};
			}
		}
	}
}
void ScreenGalaga::loadSounds() {
	soundShoot.load("sounds/shipshoot.mp3");
	soundShoot.setMultiPlay(true);

	soundExplosion.load("sounds/shipexplode.mp3");
	soundExplosion.setMultiPlay(true);
}
void ScreenGalaga::loadMenu() {

	double logoWidth = 2000;
	double logoHeight = 1121;
	double logoSizeX = getGameBounds().getWidth()*0.75;
	double logoSizeY = getGameBounds().getHeight()*0.75;
	double logoSize = min(logoSizeX, logoSizeY);

	logoBounds.x = getGameBounds().getCenter().x;
	logoBounds.width = logoSize;
	logoBounds.height = logoHeight * logoSize / logoWidth;
	logoBounds.x -= logoBounds.getWidth() / 2;
	logoBounds.y = getGameBounds().getTop();

	logo.load("sprites/logo.png");
	buttonStartGame.setText("Start Game");
	buttonStartGame.setFontSize(36);
	buttonStartGame.setForegroundColor(ofColor(0, 192, 0));
	buttonStartGame.setBackgroundColor(ofColor(64, 64, 64));
	buttonStartGame.setPosition(ofVec2f(logoBounds.getCenter().x - buttonStartGame.getWidth() / 2, logoBounds.getBottom() + 20));

	ofAddListener(buttonStartGame.clicked, this, &ScreenGalaga::startGame);
}
void ScreenGalaga::startGame() {
	loadGame();
	gameRunning = true;
}
void ScreenGalaga::loadGame() {
	for (int i = 0; i < activePlayers.size(); i++) {
		if (activePlayers[i]) {
			createPlayerShip(controllers[i], i, playerColor[i], i * 50 + 20, getGameBounds().getBottom());
		}
	}
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

bool ScreenGalaga::createPlayerShip(Controller * controller, int playerId, ofColor playerColor, double x, double y) {
	if (controller->isSetup()) {
		GalagaShip * player = new GalagaShip(controller, playerId, getGameBounds(), x, y);
		player->setOverlayColor(playerColor);
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
	updateBackground();
	if (gameRunning)
		updateGame();
	else
		updateMenu();
	
}
void ScreenGalaga::updateMenu() {
	updateControllers();
	buttonStartGame.update();
	for (int i = 0; i < controllers.size(); i++) {
		if (controllers[i]->getSerial()->available()) {
			char command = controllers[i]->getSerial()->readByte();
			if (command == 'B') {
				activePlayers[i] = !activePlayers[i];
			}
		}
	}
}
void ScreenGalaga::updateGame() {
	updatePlayers();
	updateItems();
	updatePlayerShots();
	updateEnemies();
	updateEnemyShots();
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
			bool v = vec[i]->isDisposed();
			//if (vec[i]->isDisposed()) {
			if (v) {
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
void ScreenGalaga::addPlayerShot(ofVec3f &value) {
	Missile *m = new Missile(getGameBounds(), value.z, -1, value.x, value.y);
	//ofAddListener(m->isOffScreen, this, &ScreenGalaga::removePlayerShot);
	playerShot.push_back(m);
	shots++;
	//misses = shots - hits;
	soundShoot.play();
}
void ScreenGalaga::updatePlayerShots()
{

	cleanVectorItems(playerShot);

	misses = shots - hits;
	size_t i = 0;
	for (i; i < playerShot.size(); i++) {
		playerShot[i]->update();


		size_t j = 0;
		for (j; j < enemies.size(); j++) {
			if (!enemies[j]->isDestroyed() && enemies[j]->getBounds().intersects(playerShot[i]->getBounds())) {
				enemies[j]->hit();
				if (enemies[j]->isDestroyed()) 
					soundExplosion.play();
				((Missile *)playerShot[i])->setDestroyed(true);
				hits++;
				//*getScores() = *getScores() + 1;
				score = score + 10;
				break;
			}
		}
	}

}

void ScreenGalaga::updateItems()
{
	cleanVectorItems(items);

	for (size_t i = 0; i < items.size(); i++) {
		items[i]->update();
	}
}

void ScreenGalaga::createEnemyShip(double x, double y)
{
	ofRectangle b = getGameBounds();
	EnemyShip *ship = new EnemyShip(getGameBounds(), b.getLeft() + x, b.getTop() - 50);
	enemies.push_back(ship);
	ofAddListener(ship->destroyed, this, &ScreenGalaga::removeEnemy);
	ofAddListener(ship->firedShot, this, &ScreenGalaga::addEnemyShot);
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
	while (count < enemies.size() && active < 2 && active < enemies.size() && enemies.size()>0) {
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
			if (!enemies[i]->isDestroyed() && enemies[i]->getBounds().intersects(players[j]->getBounds())) {
				enemies[i]->hit();
				if (enemies[i]->isDestroyed())
					soundExplosion.play();
				players[j]->hit();
				if (players[j]->isDestroyed())
					soundExplosion.play();
			}
		}
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

void ScreenGalaga::draw()
{
	drawBackground();
	if (gameRunning)
		drawGame();
	else
		drawMenu();
}
void ScreenGalaga::drawMenu() {
	ofSetColor(255, 255, 255);
	logo.draw(logoBounds);
	buttonStartGame.draw();

	std::string text = "";
	int lastX = getGameBounds().getLeft();
	int lastY = buttonStartGame.getBounds().getBottom() + 25;

	ofRectangle bounds;
	int padding = 3;

	for (int i = 0; i < activePlayers.size(); i++) {
		text = "Player " + to_string(i);
		bounds.set(lastX, lastY, font.stringWidth(text) + padding * 2, font.stringHeight(text) + padding * 2);

		if (activePlayers[i])
			ofSetColor(ofColor(0, 255, 0));
		else
			ofSetColor(ofColor(255, 0, 0));

		ofNoFill();
		ofDrawRectangle(bounds);

		ofSetColor(playerColor[i]);
		font.drawString(text, bounds.getLeft() + padding, bounds.getBottom() - padding);

		lastX = bounds.getRight() + 2 * padding;
	}
}
void ScreenGalaga::drawGame() {
	drawPlayers();
	drawItems();
	drawPlayerShots();
	drawEnemies();
	drawEnemyShots();

	ScreenGame::draw();

	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Hits: " + std::to_string(hits), 220, 20);
	ofDrawBitmapString("Misses: " + std::to_string(misses), 370, 20);
	ofDrawBitmapString("Shots: " + std::to_string(shots), 520, 20);
	ofDrawBitmapString("Lives: " + std::to_string(lives), 670, 20);
	ofDrawBitmapString("Score: " + std::to_string(score), 820, 20);
	ofDrawBitmapString("Level: " + level, 970, 20);
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

void ScreenGalaga::drawPlayers()
{
	ofSetColor(255);
	for (size_t i = 0; i < players.size(); i++) {
		players[i]->draw();
	}
}
void ScreenGalaga::drawPlayerShots()
{
	ofSetColor(255);
	for (size_t i = 0; i < playerShot.size(); i++) {
		playerShot[i]->draw();
	}
}

void ScreenGalaga::drawItems()
{
	ofSetColor(255);
	for (size_t i = 0; i < items.size(); i++) {
		items[i]->draw();
	}
}

void ScreenGalaga::drawEnemies()
{
	ofSetColor(255);
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->draw();
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
	if (!gameRunning)
		buttonStartGame.keyPressed(key);
}
void ScreenGalaga::keyReleased(int key)
{
	if (!gameRunning)
		buttonStartGame.keyReleased(key);
}
void ScreenGalaga::mouseMoved(int x, int y)
{
	if (!gameRunning)
		buttonStartGame.mouseMoved(x, y);
}
void ScreenGalaga::mousePressed(int x, int y, int button)
{
	if (!gameRunning)
		buttonStartGame.mousePressed(x, y, button);
}
void ScreenGalaga::mouseReleased(int x, int y, int button)
{
	if (!gameRunning)
		buttonStartGame.mouseReleased(x, y, button);
}

