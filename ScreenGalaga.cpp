
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
        for (int i = 0; i < devices.size(); i++) {
            //
            // 143101
            for (int j = 0; j < devNames.size(); j++) {
                if (devices[i].getDeviceName().find(devNames[j]) != std::string::npos) {
                    if (createPlayerShip(devices[i].getDevicePath(), i * 50 + 20, getGameBounds().getBottom())) {
                        
                    }
                    break;
                };
            }
        }
    }
    
    createEnemyShips(99);
}

bool ScreenGalaga::createPlayerShip(std::string devicePath, double x, double y)
{
	ofSerial *serial = new ofSerial();
	if (serial->setup(devicePath, 10)) {
		GalagaShip *player = new GalagaShip(serial, getGameBounds(), x, y);
		player->setOverlayColor(
			ofColor(
				ofRandom(128,255),
				ofRandom(128,255),
				ofRandom(128,255)
			)
		);
		ofAddListener(player->firedShot, this, &ScreenGalaga::addPlayerShot);
		players.push_back(player);
		return true;
	}
	return false;
}

void ScreenGalaga::createEnemyShips(int count) {

	int row = 0, col = 0;

	while (count > 0) {
		createEnemyShip(col * 52 + 20, row * 50 + 10);
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
}

void ScreenGalaga::update()
{
	ScreenGame::update();
	updatePlayers();
	updateItems();
	updatePlayerShots();
	updateEnemies();
	updateEnemyShots();
}

void ScreenGalaga::draw()
{
	ScreenGame::draw();
	drawPlayers();
	drawItems();
	drawPlayerShots();
	drawEnemies();
	drawEnemyShots();
}

void ScreenGalaga::updatePlayers()
{
	for (int i = 0; i < players.size(); i++) {
		players[i]->update();
	}
}

void ScreenGalaga::drawPlayers()
{
	for (int i = 0; i < players.size(); i++) {
		players[i]->draw();
	}
}

void ScreenGalaga::addPlayerShot(ofVec2f &value) {
	Missile *m = new Missile(getGameBounds(), -1, value.x, value.y);
	ofAddListener(m->isOffScreen, this, &ScreenGalaga::removePlayerShot);
	playerShot.push_back(m);
}

void ScreenGalaga::removePlayerShot(Missile &value)
{
	for (int i = 0; i < playerShot.size(); i++) {
		if (playerShot[i] == &value) {
			playerShot.erase(playerShot.begin() + i);
			break;
		}
	}
}

void ScreenGalaga::updatePlayerShots()
{
	bool repeatShot;
	int i = 0;
	do {
		repeatShot = false;
		for (i; i < playerShot.size(); i++) {
			playerShot[i]->update();

			bool repeatEnemy;
			int j = 0;
			do {
				repeatEnemy = false;
				for (j; j < enemies.size(); j++) {
					if (enemies[j]->getBounds().intersects(playerShot[i]->getBounds())) {
						enemies.erase(enemies.begin() + j);
						repeatEnemy = true;
						repeatShot = true;
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
	for (int i = 0; i < playerShot.size(); i++) {
		playerShot[i]->draw();
	}
}

void ScreenGalaga::updateItems()
{
	for (int i = 0; i < items.size(); i++) {
		items[i]->update();
	}
}

void ScreenGalaga::drawItems()
{
	ofSetColor(255);
	for (int i = 0; i < items.size(); i++) {
		items[i]->draw();
	}
}

void ScreenGalaga::removeEnemy(EnemyShip & value)
{
}

void ScreenGalaga::updateEnemies()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update();
	}
}

void ScreenGalaga::drawEnemies()
{
	ofSetColor(255);
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->draw();
	}
}

void ScreenGalaga::updateEnemyShots()
{
	for (int i = 0; i < enemyShot.size(); i++) {
		enemyShot[i]->update();
	}
}

void ScreenGalaga::drawEnemyShots()
{
	ofSetColor(255);
	for (int i = 0; i < enemyShot.size(); i++) {
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
	enemies.push_back(new EnemyShip(getGameBounds(), b.getLeft()+x, b.getTop() + y));
}

void ScreenGalaga::createMissile(double x, double y)
{
}
