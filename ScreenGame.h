#pragma once
#include "Screen.h"
#include "SpriteObject.h"
#include <vector>

class Game;

class ScreenGame :
	public Screen
{
public:

	ScreenGame();
	ScreenGame(Game *game, ofVec2f size);
	~ScreenGame();

	void update();
	void draw();

	ofRectangle getGameNameDrawBounds(ofRectangle area);

	void drawGameName(ofRectangle area);

	ofRectangle getGameLevelDrawBounds(ofRectangle area);

	void drawGameLevel(ofRectangle area);

	ofRectangle * getLivesDrawBounds(ofRectangle area);

	void drawLives(ofRectangle area);

	ofRectangle * getScoreDrawBounds(ofRectangle area);

	void drawScore(ofRectangle area);

	std::string getGameName();

	int getScore();
	int getScore(int index);
	int * getScores();
	int * getLives();
	int getLives(int index);
	std::string getGameLevel();

	virtual void keyPressed(int key) = 0;
	virtual void keyReleased(int key) = 0;
	virtual void mouseMoved(int x, int y)=0;
	virtual void mousePressed(int x, int y, int button)=0;
	virtual void mouseReleased(int x, int y, int button)=0;

protected:

	const double HEIGHT_HEADER = 75;
	const double HEIGHT_FOOTER = 75;

	void setGameName(std::string value);

	void addPlayer();

	bool showGameName = false;

	bool hasScores = false;
	void setScore(int value);
	void setScore(int index, int value);
	void addScore(int value);
	void addScore(int index, int value);

	bool hasLives = false;
	void setLives(int value);
	void setLives(int index, int value);
	void addLives(int value);
	void addLives(int index, int value);

	bool hasGameLevel = false;
	void setGameLevel(std::string value);

	ofRectangle areaHeader;
	ofRectangle areaGame;
	ofRectangle areaFooter;

private:
	
	std::string gameName;
	std::vector<double> scores;
	std::vector<double> lives;
	std::string gameLevel;
};
