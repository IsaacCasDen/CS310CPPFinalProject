//#ifndef GAME_H
//#define GAME_H

#pragma once


#include "ofRectangle.h"
#include "ofVec2f.h"
#include "ofTrueTypeFont.h"
#include "ofSerial.h"
#include "Screen.h"
#include "ScreenMenu.h"
#include "ScreenGame.h"
#include "ofEvent.h"

class Game {
    public:

		ofEvent<void> closed;

		static ofTrueTypeFont getFontLarge() {
			if (!hasFontLarge) {
				fontLarge.load("arial.ttf", 60, true, true);
				fontLarge.setLineHeight(34.0);
				fontLarge.setLetterSpacing(1.037);
				hasFontLarge = true;
			}
			return fontLarge;
		}
		static ofTrueTypeFont getFontMedium() {
			if (!hasFontMedium) {
				fontMedium.load("arial.ttf", 30, true, true);
				fontMedium.setLineHeight(18.0f);
				fontMedium.setLetterSpacing(1.037);
				hasFontMedium = true;
			}
			return fontMedium;
		}
		static ofTrueTypeFont getFontSmall() {
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

		static ofColor getOfColor()
		{
			return currentColor;
		}

		static void setOfColor(ofColor value)
		{
			currentColor = value;
			ofSetColor(value);
		}

		

    protected:
        void dispose();
		bool isGameRunning();
		void setGameRunning(bool isRunning);
		void setActiveScreen(Screen * screen);

		bool hasScreen();

    private:
        ofRectangle bounds;

		bool _hasScreen; // Not keeping changes
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

		void onGameClosed();
};

//#endif