#include "ScreenSnake.h"
#include "Game.h"
#include <math.h>

ScreenSnake::ScreenSnake()
{
}

ScreenSnake::ScreenSnake(Game * game, ofVec2f size) : ScreenGame(game, size)
{
	setGameName("Snake");
	addPlayer();

	setScore(0);
	hasScores = true;
	createApple(true);

	setLives(3);
	hasLives = true;
	
	setGameLevel("Level 1");
	hasGameLevel = true;
    
    port = serial.setup("tty.usbmodem143101", 9600);
    if (port)
    {
        cout << "Port OK!" << endl;
    }
    else if(!port)
    {
        cout << "Port NOT OK!" << endl;
    }
    
}

ScreenSnake::~ScreenSnake()
{
}

void ScreenSnake::update()
{
	ScreenGame::update();
	if (snakes.size()==0)
		createSnake();
	updateSnakes();
	tick++;
	createApple();
    if (serial.available()) {
        char command = serial.readByte();
        
        readCommand(command);
        std::cout << command << std::endl;
    }
}

void ScreenSnake::draw()
{
	ScreenGame::draw();
	

	drawApples();
	drawSnake();
}
void ScreenSnake::drawApples() {
	Game::setOfColor(ofColor(255, 0, 0));
	ofFill();
	for (int i = 0; i < apples.size(); i++) {
		ofDrawCircle(apples[i].x, apples[i].y, 0, apples[i].z);
	}
}
void ScreenSnake::drawSnake() {
	Game::setOfColor(ofColor(0, 0, 0));
	ofFill();
	for (int i = 0; i < snakes.size(); i++) {
		//getSnakeBoundingBox(*snakes[i]).draw();
		for (int j = 0; j < snakes[i]->size(); j++) {
			ofVec4f point = (*snakes[i])[j];
			ofDrawRectangle(point.x, point.y, SNAKE_WIDTH, SNAKE_WIDTH);
		}
	}
}


void ScreenSnake::keyPressed(int key)
{
//    if (snakes.size() == 0) return;
//    int oldDir = snakes[0]->at(0).z;
//    int newDir = 0;
//    switch (key) {
//    case KEY_LEFT:
//        // Direction Left;
//        newDir = 0;
//        break;
//    case KEY_UP:
//        // Direction Up;
//        newDir = 1;
//        break;
//    case KEY_RIGHT:
//        // Direction Right;
//        newDir = 2;
//        break;
//    case KEY_DOWN:
//        // Direction Down;
//        newDir = 3;
//        break;
//    }
//
//    if (newDir!=((oldDir+2)%4))
//        snakes[0]->at(0).z = newDir;
}
void ScreenSnake::readCommand(char command){
    //ofSetFrameRate(200);
    if (snakes.size() == 0) return;
    int oldDir = snakes[0]->at(0).z;
    int newDir = 0;
    switch (command) {
        case 'L':
            // Direction Left;
            cout << command << endl;
            newDir = 0;
            break;
        case 'U':
            cout << command << endl;
            // Direction Up;
            newDir = 1;
            break;
        case 'R':
            cout << command << endl;
            // Direction Right;
            newDir = 2;
            break;
        case 'D':
            cout << command << endl;
            // Direction Down;
            newDir = 3;
            break;
    }
    
    if (newDir!=((oldDir+2)%4))
        snakes[0]->at(0).z = newDir;
}
void ScreenSnake::keyReleased(int key)
{
}

void ScreenSnake::mouseMoved(int x, int y)
{
}

void ScreenSnake::mousePressed(int x, int y, int button)
{
}

void ScreenSnake::mouseReleased(int x, int y, int button)
{
}

void ScreenSnake::createSnake() {

	ofRectangle bounds = getGameBounds();
	std::vector<ofVec4f> *vec = new std::vector<ofVec4f>;
	ofVec4f pos;
	pos.y = SNAKE_WIDTH + bounds.y;
	pos.z = 0;
	pos.w = SNAKE_LENGTH;
	pos.x = bounds.getWidth() - SNAKE_WIDTH; vec->push_back(pos);
	for (int i = 0; i < (pos.w/SNAKE_WIDTH); i++) {
		pos.x = pos.x + SNAKE_WIDTH; vec->push_back(pos);
		pos.x = pos.x + SNAKE_WIDTH; vec->push_back(pos);
	}

	snakes.push_back(vec);
}

void ScreenSnake::createApple()
{
	createApple(false);
}
void ScreenSnake::createApple(bool override)
{
	if (!shouldCreateApple())
		if (!override) return;
	tick = 0;
	double
		x = ofRandom(getGameBounds().getLeft() + APPLE_RADIUS, getGameBounds().getRight() - APPLE_RADIUS),
		y = ofRandom(getGameBounds().getTop() + APPLE_RADIUS, getGameBounds().getBottom() - APPLE_RADIUS);

	apples.push_back(ofVec3f(x, y, APPLE_RADIUS));
}

ofPolyline ScreenSnake::getSnakeBoundingBox(std::vector<ofVec4f> points) {
	ofPolyline line;
	
	for (int i = 0; i < points.size(); i++) {
		line.addVertex(ofVec3f(points[i].x, points[i].y,0));
		
	}
	
	return line;
}
void ScreenSnake::updateSnakes() {
	updateSnakes(0);
}
void ScreenSnake::updateSnakes(int beginAt) {
	bool rerun=false;
	int i=beginAt;
	for (i = beginAt; i < snakes.size(); i++) {
		std::vector<ofVec4f> *snake = snakes[i];
		ofVec4f head = snake->at(0);
		bool recheckApples = false;
		do {
			for (int j = 0; j < apples.size(); j++) {
				ofRectangle apple = ofRectangle(apples[j].x, apples[j].y, APPLE_RADIUS, APPLE_RADIUS);
				ofRectangle sn = ofRectangle(head.x,head.y,SNAKE_WIDTH,SNAKE_WIDTH);
				if (apple.intersects(sn)) {
					addScore(1);
					head.w += SNAKE_WIDTH;
					apples.erase(apples.begin() + j);
					if (apples.size() == 0)
						createApple(true);
					else
						recheckApples = true;
				}
			}
		} while (recheckApples);
		switch ((int)head.z) {
			case 0:
				snake->insert(snake->begin(), ofVec4f(head.x - SNAKE_SPEED, head.y, head.z, head.w));
				break;
			case 1:
				snake->insert(snake->begin(), ofVec4f(head.x, head.y - SNAKE_SPEED, head.z, head.w));
				break;
			case 2:
				snake->insert(snake->begin(), ofVec4f(head.x + SNAKE_SPEED, head.y, head.z, head.w));
				break;
			case 3:
				snake->insert(snake->begin(), ofVec4f(head.x, head.y + SNAKE_SPEED, head.z, head.w));
				break;
		}
		if (head.x<getGameBounds().getLeft()|| head.y<getGameBounds().getTop() || head.x + SNAKE_WIDTH>getGameBounds().getRight() || head.y + SNAKE_WIDTH>getGameBounds().getBottom()) {
			rerun = true;
			snakes.erase(snakes.begin() + i);
			break;
		}
		else {
			snake->resize(head.w);
		}

		/*if (head.x<0) {
			float v1 = head.x;
			std::cout << v1;
		}
		else if (head.y < 0) {
			float v1 = head.y;
			std::cout << v1;
		}
		else if (head.x + SNAKE_WIDTH > getGameBounds().getHeight()) {
			float v1 = head.x+SNAKE_WIDTH;
			float v2 = getGameBounds().getHeight();
			std::cout << v1 << endl << v2;
		}
		else if (head.y + SNAKE_WIDTH > getGameBounds().getWidth()) {
			float v1 = head.y + SNAKE_WIDTH;
			float v2 = getGameBounds().getWidth();
			std::cout << v1 << endl << v2;
		}
		else {
			snake->resize(head.w);
		}*/
	}
	if (rerun) {
		updateSnakes(i);
	}
}

bool ScreenSnake::shouldCreateApple()
{
	return (tick/ofGetFrameRate()) > CREATE_APPLE_SECONDS;
}
