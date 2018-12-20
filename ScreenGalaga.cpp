
#include "ScreenGalaga.h"

bool ScreenGalaga::isTransition()
{
	return 
		soundGameStart.isPlaying()||
		soundNextLevel.isPlaying()||
		soundWonLevel.isPlaying()||
		soundPerfectLevel.isPlaying();
}

ScreenGalaga::ScreenGalaga()
{
    
}

ScreenGalaga::ScreenGalaga(Game * game, ofVec2f size) : ScreenGame(game, size)
{
	font.load("fonts/emulogic.ttf", 24, true, true);
	fontTitle.load("fonts/emulogic.ttf", 16, true, true);
	fontValue.load("fonts/emulogic.ttf", 12, true, true);

	areaHeader = ofRectangle(0, 0, size.x, HEIGHT_HEADER);
	areaFooter = ofRectangle(0, size.y - HEIGHT_FOOTER, size.x, HEIGHT_FOOTER);
	areaGame = ofRectangle(0, areaHeader.getBottom(), size.x, size.y - (areaHeader.getHeight() + areaFooter.getHeight()));

    hits = *getScores();
    shots = 0;
    misses = 0;
    score = *getScores();
    //lives = *getLives();

	createStarField();

	loadSounds();
	loadMenu();
}
void ScreenGalaga::updateControllers() {
	/*
	if (createPlayerShip(devices[i].getDevicePath(), devices[i].getDeviceID(), i * 50 + 20, areaGame.getBottom())) {
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

	soundGameStart.load("sounds/gamestart.mp3");
	soundGameStart.setMultiPlay(false);

	soundNextLevel.load("sounds/challengestart.mp3");
	soundNextLevel.setMultiPlay(false);

	soundWonLevel.load("sounds/challengewon.mp3");
	soundWonLevel.setMultiPlay(false);

	soundPerfectLevel.load("sounds/challengeperfect.mp3");
	soundPerfectLevel.setMultiPlay(false);
}
void ScreenGalaga::loadMenu() {

	double logoWidth = 2000;
	double logoHeight = 1121;
	double logoSizeX = areaGame.getWidth()*0.75;
	double logoSizeY = areaGame.getHeight()*0.75;
	double logoSize = min(logoSizeX, logoSizeY);

	logoBounds.x = areaGame.getCenter().x;
	logoBounds.width = logoSize;
	logoBounds.height = logoHeight * logoSize / logoWidth;
	logoBounds.x -= logoBounds.getWidth() / 2;
	logoBounds.y = areaGame.getTop();

	logo.load("sprites/logo.png");
	buttonStartGame.setText("Start Game");
	buttonStartGame.setFontSize(36);
	buttonStartGame.setForegroundColor(ofColor(0, 192, 0));
	buttonStartGame.setBackgroundColor(ofColor(64, 64, 64));
	buttonStartGame.setPosition(ofVec2f(logoBounds.getCenter().x - buttonStartGame.getWidth() / 2, logoBounds.getBottom() + 20));

	ofAddListener(buttonStartGame.clicked, this, &ScreenGalaga::startGame);
}
void ScreenGalaga::startGame() {
	if (loadGame()) {
		soundGameStart.play();
		gameRunning = true;
	}
}
bool ScreenGalaga::loadGame() {
	bool value = false;
	for (int i = 0; i < activePlayers.size(); i++) {
		if (activePlayers[i]) {
			if (createPlayerShip(controllers[i], i, playerColor[i], i * 50 + 20, areaGame.getBottom())) {
				value = true;
			}
		}
	}
	enemyShot.clear();
	playerShot.clear();
	items.clear();
	enemies.clear();
	level = 0;
	nextLevel();
	return value;
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
	ofRectangle b = areaGame;
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
		bool hasPlayer = false;
		for (int i = 0; i < players.size(); i++) {
			if (((GalagaShip *)players[i])->isController(controller)) {
				((GalagaShip *)players[i])->reset();
				hasPlayer = true;
				break;
			}
		}
		if (!hasPlayer) {
			GalagaShip * player = new GalagaShip(controller, playerId, areaGame, ofVec2f(x, y), ofVec2f(x, y));
			player->setOverlayColor(playerColor);
			ofAddListener(player->firedShot, this, &ScreenGalaga::addPlayerShot);
			//ofAddListener(player->destroyed, this, &ScreenGalaga::removePlayer);
			players.push_back(player);
		}
		return true;
	}
	return false;
}
void ScreenGalaga::createEnemyShips(int count) {
	createEnemyShips(count, 0, 0);
}
void ScreenGalaga::createEnemyShips(int count, int healthBonus, double speedBonus) {

	int row = 0, col = 0;

	while (count > 0) {
		createEnemyShip(col * 52 + 100, row * 50 + 100, healthBonus, speedBonus);
		count--;
		col++;
		if (col > 21) {
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
	if (!isTransition()) {
		if (newLevel) {
			soundNextLevel.play();
			nextLevel();
			newLevel = false;
		}
	}
	if (!isTransition()) {
		
		updateItems();
		updatePlayerShots();
		updateEnemies();
		updateEnemyShots();
	}
}

void ScreenGalaga::nextLevel()
{
	maxActive = 2 + level / 3;
	level++;
	createEnemyShips(level*5,max(0,(int)(level/6)),max(0,(int)(level/8)));

}
void ScreenGalaga::gameOver() {
	gameRunning = false;
}

void ScreenGalaga::updateBackground() {
	ofRectangle b = areaGame;
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

	bool hasPlayers = false;
	for (size_t i = 0; i < players.size(); i++) {
		players[i]->update();
		if (((GalagaShip *)players[i])->getLifeCount() >= 0)
			hasPlayers = true;
	}
	if (!hasPlayers)
		gameOver();
}
void ScreenGalaga::addPlayerShot(ofVec3f &value) {
	if (isTransition()) return;
	Missile *m = new Missile(areaGame, value.z, -1, value.x, value.y);
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
				if (enemies[j]->isDestroyed()) {
					soundExplosion.play();
					for (int k = 0; k < players.size(); k++) {
						if (((Missile *)playerShot[i])->getPlayerId() == ((GalagaShip *)players[k])->getPlayerId()) {
							((GalagaShip *)players[k])->addScore(((EnemyShip *)enemies[j])->getPointValue());
							break;
						}
					}
				}
					
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

void ScreenGalaga::createEnemyShip(double x, double y, int healthBonus, double speedBonus)
{
	ofRectangle b = areaGame;
	EnemyShip *ship = new EnemyShip(areaGame, ofVec2f(0, 0), ofVec2f(b.getLeft() + x, b.getTop() + y));
	ship->addMaxDamage(healthBonus);
	ship->addMaxSpeed(speedBonus);
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
	while (count < enemies.size() && active < maxActive && active < enemies.size() && enemies.size()>0) {
		count++;
		int i = ofRandom(0, enemies.size() - 1);
		if (!((EnemyShip *)enemies[i])->isActive) {
			((EnemyShip *)enemies[i])->isActive = true;
			active++;
		}
	}

	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->update();
		if (!enemies[i]->isDestroyed()) {
			for (size_t j = 0; j < players.size(); j++) {
				if (!players[j]->isDestroyed()) {
					if (enemies[i]->getBounds().intersects(players[j]->getBounds())) {
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
	}

	if (enemies.size() <= 0 && !newLevel) {
		soundWonLevel.play();
		newLevel = true;
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
	Missile *m = new Missile(areaGame, -1, value.x, value.y);
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
	ofSetColor(0, 0, 0);
	ofFill();
	ofDrawRectangle(areaHeader);
	ofDrawRectangle(areaFooter);

	ofSetColor(255, 255, 255);
	logo.draw(logoBounds);
	buttonStartGame.draw();

	std::string text = "";
	int lastX = areaGame.getLeft();
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
	drawHeader();
	drawFooter();
	if (!isTransition()) {
		drawItems();
		drawPlayerShots();
		drawEnemies();
		drawEnemyShots();
	}
	
}
void ScreenGalaga::drawHeader() {
	ofSetColor(0, 0, 0);
	ofFill();
	ofDrawRectangle(areaHeader);
	
	std::string text;
	double padding = 3;
	double indexPos = areaHeader.getWidth() / players.size();
	double c;
	double y = areaHeader.getTop() + padding;
	ofRectangle itemBounds;

	if (players.size() > 0) {
		text = "Score";
		for (int i = 0; i < players.size(); i++) {
			ofSetColor(playerColor[i]);
			c = ((indexPos*(i + 1)) - (indexPos*(i))) / 2;
			itemBounds.width = fontTitle.stringWidth(text);
			itemBounds.height = fontTitle.stringHeight(text);
			itemBounds.x = c - itemBounds.getWidth() / 2;
			itemBounds.y = y + padding;
			fontTitle.drawString(text, itemBounds.x, itemBounds.y + itemBounds.height);
		}
		y = itemBounds.getBottom() + padding;
		for (int i = 0; i < players.size(); i++) {
			text = to_string(((GalagaShip *)players[i])->getScore());
			ofSetColor(playerColor[i]);

			c = ((indexPos*(i + 1)) - (indexPos*(i))) / 2;
			itemBounds.width = fontValue.stringWidth(text);
			itemBounds.height = fontValue.stringHeight(text);
			itemBounds.x = c - itemBounds.getWidth() / 2;
			itemBounds.y = y + padding;
			fontValue.drawString(text, itemBounds.x, itemBounds.y + itemBounds.height);
		}
	}
	
	

	//ofDrawBitmapString("Hits: " + std::to_string(hits), 220, 20);
	//ofDrawBitmapString("Score: " + std::to_string(score), 820, 20);

	//ofDrawBitmapString("Misses: " + std::to_string(misses), 370, 20);
	//ofDrawBitmapString("Shots: " + std::to_string(shots), 520, 20);
	//ofDrawBitmapString("Level: " + level, 970, 20);
}

void ScreenGalaga::drawFooter()
{
	ofSetColor(0, 0, 0);
	ofFill();
	ofDrawRectangle(areaFooter);

	std::string text;
	double padding = 3;
	double indexPos = areaFooter.getWidth() / players.size();
	double c;
	double y = areaFooter.getTop() + padding;
	ofRectangle itemBounds;

	if (players.size() > 0) {
		for (int i = 0; i < players.size(); i++) {
			GalagaShip * player = (GalagaShip *)players[i];
			text = "Player " + to_string(player->getPlayerId());
			ofSetColor(playerColor[i]);
			c = ((indexPos*(i + 1)) - (indexPos*(i))) / 2;
			itemBounds.width = fontTitle.stringWidth(text);
			itemBounds.height = fontTitle.stringHeight(text);
			itemBounds.x = c - itemBounds.getWidth() / 2;
			itemBounds.y = y + padding;
			fontTitle.drawString(text, itemBounds.x, itemBounds.y + itemBounds.height);
		}
		y = itemBounds.getBottom() + padding;
		for (int i = 0; i < players.size(); i++) {
			GalagaShip * player = (GalagaShip *)players[i];
			ofSetColor(playerColor[i]);
			c = ((indexPos*(i + 1)) - (indexPos*(i))) / 2;
			itemBounds.width = 24;
			itemBounds.height = 24;
			itemBounds.x = (c - (player->getLifeCount()*(itemBounds.getWidth() + padding) / 2));
			itemBounds.y = y;
			
			for (int j = 0; j < player->getLifeCount(); j++) {
				itemBounds.x += (itemBounds.getWidth() + padding);
				player->getSprite().draw(itemBounds);
			}
			
		}
		/*
		y = itemBounds.getBottom() + padding;
		for (int i = 0; i < players.size(); i++) {
			GalagaShip * player = (GalagaShip *)players[i];
			text = to_string(((GalagaShip *)players[i])->getScore());
			ofSetColor(playerColor[i]);
			c = ((indexPos*(i + 1)) - (indexPos*(i))) / 2;
			itemBounds.width = 36;
			itemBounds.height = 36;
			itemBounds.x = (c - (player->getLifeCount()*(itemBounds.getWidth() + padding) / 2));
			itemBounds.y = y;
		}
		y = itemBounds.getBottom() + padding;
		*/
	}
}

void ScreenGalaga::drawBackground() {
	ofSetColor(ofColor(0, 0, 0));
	ofFill();
	ofDrawRectangle(areaGame);

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

