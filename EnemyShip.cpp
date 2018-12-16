#include "EnemyShip.h"
#include "ofMain.h"


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
EnemyShip::EnemyShip(ofRectangle gameBounds, double x, double y):Ship(gameBounds,x,y)
{
	setSize(ofVec2f( DEFAULT_WIDTH, DEFAULT_HEIGHT));

	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	
	sprites[0].load("galaga_enemy1_1.png");
	sprites[1].load("galaga_enemy1_2.png");
	setSpriteSetEnd(1);

    setTicksPerSprite(ofGetFrameRate()/8);
    count = 0;
}
void EnemyShip::update()
{
	if (cycleSprite()) {
		tick = 0;
		nextSprite();
	}
	else
		tick++;
	
    float radius = 10;
    ofVec2f finalPos;
    float theta = 0.0f;
    float dx;
    float radians = (PI*theta)/180;
    ofVec2f pos = getBounds().getPosition();

    count++;
    cout << count << endl;
    float dy;
    int j;
    //theta = 45;
    for (int i=0; i<10; i++) {
        dx = 0.01+0.1*(cos((i*PI)/4));
        //float dx = 0.01 + 3*radians;
        dy = 0.01+0.1*(cos((i*PI)/4));
        
        //float dy = 0.01 + 3*radians;
        j = i;
    }
    if(count > 3000){
        dx = 0.01+0.1*(-cos((j*PI)/4));
    }
    else if (dx >= 3000 && dx <= 3500){
        dx = 0;
    }
    else if(count > 6000){
        count = 0;
    }
    pos.x += dx;
    pos.y += dy;
    setPosition(pos);
//    switch (movePattern) {
//        case 0:
//            if (pos.y < 50)
//                setPosition(getMovePattern1_NextPos(false, pos));
//            else
//                movePattern = 2;
//                setPosition(getMovePattern2_NextPos(false, pos));
//            break;
//        case 1:
//
//            break;
//        case 2:
//            if (pos.y < gameBounds.getBottom())
//                setPosition(getMovePattern3_NextPos(false, pos));
//            else
//                movePattern = 1;
//                setPosition(getMovePattern2_NextPos(false, pos));
//            break;
//    }
}//update()

void EnemyShip::draw()
{
	ofSetColor(getOverlayColor().lerp(getCurrDamageOverlay(), 0.5f));
	getSprite().draw(getBounds());
}
void EnemyShip::polar_to_cartesian(float radius, float theta){
    getBounds().x = radius*cos(theta);
    getBounds().y = radius*sin(theta);
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

ofVec2f EnemyShip::getMovePattern1_NextPos(bool isReflected, ofVec2f currentPos)
{
    ofVec2f value = currentPos;
	if (isReflected)
		value.y -= 5;
	else 
		value.y += 5;

	return value;
}

ofVec2f EnemyShip::getMovePattern2_NextPos(bool isReflected, ofVec2f currentPos)
{
	ofVec2f value = currentPos;

	// Move right to left in holding pattern;

	return value;
}

ofVec2f EnemyShip::getMovePattern3_NextPos(bool isReflected, ofVec2f currentPos)
{
	ofVec2f value = currentPos;
	return value;
}
