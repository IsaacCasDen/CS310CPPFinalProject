#pragma once

#include "ofRectangle.h"
#include "ofVec2f.h"

class Game {
    public:
        ofRectangle getBounds();

        Game(ofVec2f size);

        void startGame();
        void exitGame();

        void updateGame();
        void drawGame();

    protected:
        void dispose();

    private:
        ofRectangle bounds;
};