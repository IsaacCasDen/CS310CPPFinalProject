#include "EnemyShip.h"
#include "ofMain.h"

EnemyShip::EnemyShip(ofRectangle gameBounds, double x, double y):Ship(gameBounds,x,y)
{
	setSize(ofVec2f( DEFAULT_WIDTH, DEFAULT_HEIGHT));

	sprites.push_back(ofImage());
	sprites.push_back(ofImage());
	
	sprites[0].load("galaga_enemy1_1.png");
	sprites[1].load("galaga_enemy1_2.png");
	setSpriteSetEnd(1);

	setTicksPerSprite(ofGetFrameRate()/8);
    
    
}

void EnemyShip::update()
{
    ofVec2f pos = ofVec2f(getBounds().x, getBounds().y);
	if (cycleSprite()) {
		tick = 0;
		nextSprite();
	}
	else
		tick++;

//    pct = 10;
//    pos.x = (1-pct) * pos.x + (pct) * pos.x;
//    pos.y = (1-pct) * pos.y + (pct) * pos.y;
//    pct += 0.1f;
//    if (pct > 1){
//        pct = 0;
//    }
    //float xpos = ofMap(sin(ofGetElapsedTimef()*2), 1, -14.1, 0.5, ofGetWidth());//-1 to 1.1
    //ofSetFrameRate(200);
    float xpos = getBounds().x;
    float ypos = getBounds().y;
    if(tick == 10){
        xpos += sin(45)*20;
        ypos += sin(45)*20;
    }
    //xpos = getBounds().x + sin(-45)*20;
    if(ypos > gameBounds.getBottom()){
        ypos = 0;
    }
    setPosition(ofVec2f(xpos, ypos));
    

		
	

}

void EnemyShip::draw()
{

    ofRectangle b = getBounds();
    //interpolate(percent);
    ofSetColor(getOverlayColor().lerp(getCurrDamageOverlay(), 0.5f));
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
