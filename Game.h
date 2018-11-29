//#ifndef GAME_H
//#define GAME_H

#pragma once

#include "ofRectangle.h"
#include "ofVec2f.h"
#include "Drawable.h"
#include "Screen.h"
#include "ScreenMenu.h"

class Game {
    public:

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

		virtual void mouseMoved(int x, int y);
		virtual void mousePressed(int x, int y, int button);
		virtual void mouseReleased(int x, int y, int button);

    protected:
        void dispose();
		bool isGameRunning();
		void setGameRunning(bool isRunning);

		bool hasScreen();
		void hasScreen(bool value);

    private:
        ofRectangle bounds;
		bool _isGameRunning = false;

		bool _hasScreen = false;
		Screen *activeScreen;

		static bool hasFontLarge;
		static bool hasFontMedium;
		static bool hasFontSmall;

		static ofTrueTypeFont fontLarge;
		static ofTrueTypeFont fontMedium;
		static ofTrueTypeFont fontSmall;

};

//#endif