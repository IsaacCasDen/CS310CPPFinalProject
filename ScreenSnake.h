#pragma once
#include "ScreenGame.h"
#include "ofSerial.h"
#include <vector>

class ScreenSnake :
	public ScreenGame
{
public:

	ScreenSnake();
	ScreenSnake(Game *game, ofVec2f size);
	~ScreenSnake();

	virtual void update();
	virtual void draw();

	void drawApples();
	void drawSnake();

	void createApple();
	void createApple(bool override);

	ofPolyline getSnakeBoundingBox(std::vector<ofVec4f> points);
	ofPolyline getSnakeBoundingBox(std::vector<ofVec2f> points);

	void updateSnakes();
	void updateSnakes(size_t beginAt);
    void readCommand(char command);
	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

	void createSnake();

protected:
	static const int APPLE_RADIUS = 8;
	static const int CREATE_APPLE_SECONDS = 16;
    bool createPlayerShip(std::string devicePath, double x, double y);
	static const int SNAKE_WIDTH = 3;
	static const int SNAKE_LENGTH = 3;
	static const int SNAKE_SPEED = 3;
	static const int SNAKE_GROWTH_STEP = 3;

private:
	int playerDirection = 0;
	std::vector<ofVec3f> apples;
	std::vector<std::vector<ofVec4f> *> snakes;

	bool shouldCreateApple();
	int lastAppleCreated = 0;
	float tick = 0;
    bool port;
    ofSerial serial;
    std::vector<ofSerialDeviceInfo> devices;
};

