#include "ScreenGame.h"
#include "Game.h"

ScreenGame::ScreenGame()
{
	
}
ScreenGame::ScreenGame(Game * game, ofVec2f size) : Screen(game, size)
{
}

ScreenGame::~ScreenGame()
{
}

void ScreenGame::update()
{
	
}

void ScreenGame::draw()
{
}

ofTrueTypeFont getGameNameFont() {
	return Game::getFontSmall();
}
ofRectangle ScreenGame::getGameNameDrawBounds(ofRectangle area) {
	ofRectangle bounds;
	bounds.width = getGameNameFont().stringWidth(getGameName());
	bounds.height = getGameNameFont().stringHeight(getGameName());
	bounds.x = area.getCenter().x - bounds.width / 2;
	bounds.y = area.y + bounds.height + 3;

	return bounds;
}
void ScreenGame::drawGameName(ofRectangle area) {
	if (!showGameName) return;
	ofSetColor(0, 0, 0);
	std::string text = getGameName();
	ofRectangle bounds = getGameNameDrawBounds(area);
	getGameNameFont().drawString(text, bounds.x, bounds.y);
}

ofTrueTypeFont getGameLevelFont() {
	return Game::getFontSmall();
}
ofRectangle ScreenGame::getGameLevelDrawBounds(ofRectangle area) {
	ofRectangle bounds;
	bounds.width = getGameLevelFont().stringWidth(getGameLevel());
	bounds.height = getGameLevelFont().stringHeight(getGameLevel());
	bounds.x = area.getCenter().x - bounds.width / 2;
	bounds.y = area.y + bounds.height + 3;

	return bounds;
}
void ScreenGame::drawGameLevel(ofRectangle area) {
	if (!hasGameLevel) return;
	ofSetColor(0, 0, 0);
	std::string text = getGameLevel();
	ofRectangle bounds = getGameLevelDrawBounds(area);
	getGameLevelFont().drawString(text, bounds.x, bounds.y);
}

ofTrueTypeFont getLivesFont() {
	return Game::getFontSmall();
}
ofRectangle * ScreenGame::getLivesDrawBounds(ofRectangle area) {
	ofRectangle * bounds = new ofRectangle[lives.size()];
	int * vals = getLives();
	for (size_t i = 0; i < lives.size(); i++) {
		double
			width = getLivesFont().stringWidth(to_string(vals[i])),
			height = getLivesFont().stringHeight(to_string(vals[i])),
			x = 3,
			y = 3;
		ofRectangle val = ofRectangle(x, y, width, height);
		bounds[i] = val;
	}

	return bounds;
}
void ScreenGame::drawLives(ofRectangle area) {
	if (!hasLives) return;

}

ofTrueTypeFont getScoreFont() {
	return Game::getFontSmall();
}
ofRectangle * ScreenGame::getScoreDrawBounds(ofRectangle area) {
	ofRectangle * bounds = new ofRectangle[scores.size()];
	int * vals = getScores();
	for (size_t i = 0; i < scores.size(); i++) {
		double
			width = getScoreFont().stringWidth(to_string(vals[i])),
			height = getScoreFont().stringHeight(to_string(vals[i])),
			x = 3,
			y = 3;
		ofRectangle val = ofRectangle(x, y, width, height);
		bounds[i] = val;
	}

	return bounds;
}
void ScreenGame::drawScore(ofRectangle area) {
	if (!hasScores) return;
	ofFill();
	ofSetColor(ofColor(0, 0, 0));
	ofRectangle * s = getScoreDrawBounds(area);
	double width = 0;
    s[0].x = area.getRight()-s[0].width;
    s[0].y = area.getTop()-s[0].height;
    //ofDrawBitmapString("Hits: ", 20, 20);
    //ofDrawRectangle(10, 10, 10, 10);
//    for (size_t i = scores.size() - 1; i >= 0; i--)
//        width += s[i].getWidth() + 3;
		
	//getScoreFont().drawString(to_string(getScore()), area.getWidth() - offset + s[i].x, area.getTop() + s[i].height + s[i].y);
}

std::string ScreenGame::getGameName()
{
	return gameName;
}

int * ScreenGame::getScores()
{
	int * values = new int[scores.size()];
	for (size_t i = 0; i < scores.size(); i++)
		values[i] = scores[i];

	return values;
}

int ScreenGame::getScore()
{
	return scores[0];
}

int ScreenGame::getScore(int index)
{
	return scores[index];
}

int * ScreenGame::getLives()
{
    //setLives(3);
	int * values = new int[lives.size()];
	for (size_t i = 0; i < scores.size(); i++)
		values[i] = lives[i];

	return values;
}

int ScreenGame::getLives(int index)
{
	return lives[index];
}

std::string ScreenGame::getGameLevel()
{
	return gameLevel;
}

void ScreenGame::mouseMoved(int x, int y)
{

}

void ScreenGame::mousePressed(int x, int y, int button)
{

}

void ScreenGame::mouseReleased(int x, int y, int button)
{

}

void ScreenGame::setGameName(std::string value)
{
	gameName = value;
}

void ScreenGame::addPlayer()
{
	scores.push_back(0);
	lives.push_back(0);

}

void ScreenGame::setScore(int value)
{
	scores[0] = value;
}

void ScreenGame::setScore(int index, int value)
{
	scores[index] = value;
}

void ScreenGame::addScore(int value)
{
	scores[0] += value;
}

void ScreenGame::addScore(int index, int value)
{
	scores[index] += value;
}

void ScreenGame::setLives(int value)
{
	lives[0] = value;
}

void ScreenGame::setLives(int index, int value)
{
	lives[index] = value;
}

void ScreenGame::addLives(int value)
{
	lives[0] += value;
}

void ScreenGame::addLives(int index, int value)
{
	lives[index] += value;
}

void ScreenGame::setGameLevel(std::string value)
{
	gameLevel = value;
}
