#include "EnemyShip.h"
#include "ofMain.h"

EnemyShip::EnemyShip(ofRectangle gameBounds, double x, double y):SpriteObject(gameBounds)
{
	setPosition(ofVec2f(x, y));
	setSize(ofVec2f( DEFAULT_WIDTH, DEFAULT_HEIGHT));

	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	
	sprites[0].load("galaga_enemy1_1.png");
	sprites[1].load("galaga_enemy1_2.png");

	setTicksPerSprite(ofGetFrameRate()/8);

}

void EnemyShip::update()
{
	if (cycleSprite()) {
		tick = 0;
		nextSprite();
	}
	else
		tick++;
		
	setPosition(ofVec2f(getBounds().x+1, getBounds().y));
}

void EnemyShip::draw()
{
	getSprite().draw(getBounds());
}

EnemyShip::~EnemyShip()
{
}

void EnemyShip::keyPressed(int key)
{
}

void EnemyShip::keyReleased(int key)
{
}

void EnemyShip::mouseMoved(int x, int y)
{
}

void EnemyShip::mousePressed(int x, int y, int button)
{
}

void EnemyShip::mouseReleased(int x, int y, int button)
{
}

bool EnemyShip::cycleSprite()
{
	return getTicksperSprite() < tick;
}