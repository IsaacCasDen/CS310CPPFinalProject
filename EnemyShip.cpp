#include "EnemyShip.h"
#include "ofMain.h"


int EnemyShip::getPointValue()
{
	return 100 * getMaxDamage()*getSpeed();
}

//EnemyShip::EnemyShip(ofRectangle gameBounds, double x, double y):SpriteObject(gameBounds)
//{
//    setPosition(ofVec2f(x, y));
//    setSize(ofVec2f( DEFAULT_WIDTH, DEFAULT_HEIGHT));
//
//    sprites.push_back(ofImage());
//    sprites.push_back(ofImage());
//
//    sprites[0].load("galaga_enemy1_1.png");
//    sprites[1].load("galaga_enemy1_2.png");
//
//    setTicksPerSprite(ofGetFrameRate()/8);
//
//}
EnemyShip::EnemyShip(ofRectangle gameBounds, ofVec2f position, ofVec2f targetPosition):Ship(gameBounds,position,targetPosition)
{
	setSize(ofVec2f( DEFAULT_WIDTH, DEFAULT_HEIGHT));

	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	
	sprites[0].load("sprites/galaga_enemy1_1.png");
	sprites[1].load("sprites/galaga_enemy1_2.png");
	sprites[2].load("sprites/explode_1.gif");
	sprites[3].load("sprites/explode_2.gif");
	sprites[4].load("sprites/explode_3.gif");
	sprites[5].load("sprites/explode_4.gif");
	sprites[6].load("sprites/explode_5.gif");
	sprites[7].load("sprites/explode_6.gif");
	sprites[8].load("sprites/explode_7.gif");
	sprites[9].load("sprites/explode_8.gif");


	setSpriteSetEnd(1);

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
		
	moveTick++;
	ofVec2f pos = getBounds().getPosition();
		switch (movePattern) {
		case 0:
			if (getBasePosition().x!=pos.x || getBasePosition().y != pos.y)
				setPosition(getMovePattern1_NextPos(false, pos));
			else {
				movePattern = 1;
				setPosition(getMovePattern2_NextPos(false, pos));
				moveTick = 0;
			}
			break;
		case 1:
			if (isActive) {
				if (pos.y < gameBounds.getBottom())
					setPosition(getMovePattern2_NextPos(false, pos));
				else {
					movePattern = 2;
					setPosition(getMovePattern3_NextPos(false, pos));
					moveTick = 0;
				}
			}
			break;
		case 2:
			movePattern = 0;
			setPosition(getMovePattern3_NextPos(false, pos));
			moveTick = 0;
			/*
			if (pos.y < gameBounds.getBottom())
				setPosition(getMovePattern3_NextPos(false, pos));
			else {
				movePattern = 0;
				setPosition(getMovePattern1_NextPos(false, pos));
				moveTick = 0;
			}
			*/
			break;
		}
}

void EnemyShip::draw()
{
	ofSetColor(getOverlayColor().lerp(getCurrDamageOverlay(), 0.5f));
	getSprite().draw(getBounds());
	if (spriteIndex == 9)
	{
		isDisposed(true);
	}
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

int EnemyShip::getTicksToFire()
{
    return ticksToFire;
}

void EnemyShip::setTicksToFire(int value)
{
    ticksToFire = value;
}

bool EnemyShip::shouldFire()
{
    return false;// (ticks > ticksToFire);
}

void EnemyShip::fire()
{
    //ofNotifyEvent(shotFired);
}

void EnemyShip::_destroyed()
{
	setTicksPerSprite(ofGetFrameRate() / 6);
	setSpriteSetStart(2);
	setSpriteSetEnd(9);
}

ofVec2f EnemyShip::getMovePattern1_NextPos(bool isReflected, ofVec2f currentPos)
{
	ofVec2f value = currentPos;
	ofVec2f base = getBasePosition();
	double val;

	if (value.x != base.x) {
		val = base.x - value.x;
		if (val < 0)
			value.x += max(-getSpeed(), val);
		else if (val>0) {
			value.x += min(getSpeed(), val);
		}
		
	}
	if (value.y != base.y) {
		val = base.y - value.y;
		if (val < 0)
			value.y += max(-getSpeed(), val);
		else if (val > 0) {
			value.y += min(getSpeed(), val);
		}
	}

	return value;
}

ofVec2f EnemyShip::getMovePattern2_NextPos(bool isReflected, ofVec2f currentPos)
{
	ofVec2f value = currentPos;

	value.x += cos(PI*(.01*getSpeed())*moveTick);
	value.y += getSpeed(); //sin(PI*.001*moveTick);
	return value;
}

ofVec2f EnemyShip::getMovePattern3_NextPos(bool isReflected, ofVec2f currentPos)
{
	ofVec2f value = currentPos;

	if (!isDestroyed())
		value.y = gameBounds.getTop() - getBounds().height;

	return value;
}
