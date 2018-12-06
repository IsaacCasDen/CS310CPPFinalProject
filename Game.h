//#ifndef GAME_H
//#define GAME_H

#pragma once


#include "ofRectangle.h"
#include "ofVec2f.h"
#include "ofTrueTypeFont.h"
#include "ofSerial.h"
#include "Drawable.h"
#include "Screen.h"
#include "ScreenMenu.h"
#include "ScreenGame.h"

class Game {
    public:

		/*void loadFontLarge();
		void loadFontMedium();
		void loadFontSmall();*/

		/*ofTrueTypeFont getFontLarge();
		ofTrueTypeFont getFontMedium();
		ofTrueTypeFont getFontSmall();*/

		static ofTrueTypeFont Game::getFontLarge() {
			if (!hasFontLarge) {
				fontLarge.load("arial.ttf", 60, true, true);
				fontLarge.setLineHeight(34.0);
				fontLarge.setLetterSpacing(1.037);
				hasFontLarge = true;
			}
			return fontLarge;
		}
		static ofTrueTypeFont Game::getFontMedium() {
			if (!hasFontMedium) {
				fontMedium.load("arial.ttf", 30, true, true);
				fontMedium.setLineHeight(18.0f);
				fontMedium.setLetterSpacing(1.037);
				hasFontMedium = true;
			}
			return fontMedium;
		}
		static ofTrueTypeFont Game::getFontSmall() {
			if (!hasFontSmall) {
				fontSmall.load("arial.ttf", 20, true, true);
				fontSmall.setLineHeight(12.0f);
				fontSmall.setLetterSpacing(1.037);
				hasFontSmall = true;
			}
			return fontSmall;
		}

		ofRectangle getBounds();

		Game();
        Game(ofVec2f size);

        void startGame();
        void exitGame();

        void update();
        void draw();

		void loadScreenMenu();
		void loadScreenGame();

		virtual void mouseMoved(int x, int y);
		virtual void mousePressed(int x, int y, int button);
		virtual void mouseReleased(int x, int y, int button);

		ofColor Game::getOfColor()
		{
			return currentColor;
		}

		void Game::setOfColor(ofColor value)
		{
			currentColor = value;
			ofSetColor(value);
		}

    protected:
        void dispose();
		bool isGameRunning();
		void setGameRunning(bool isRunning);

		bool hasScreen();
		void hasScreen(bool value);

    private:
        ofRectangle bounds;
		bool _isGameRunning = false;

		bool _hasScreen = false; // Not keeping changes
		int currentScreenIndex = 0;
		int lastScreenIndex = 0;
		Screen *activeScreen = nullptr;
		Screen *newScreen = nullptr;
		
		static bool hasFontLarge;
		static bool hasFontMedium;
		static bool hasFontSmall;

		static ofTrueTypeFont fontLarge;
		static ofTrueTypeFont fontMedium;
		static ofTrueTypeFont fontSmall;

		ofSerial serial;
		bool port;

		static ofColor currentColor;
};

//#endif