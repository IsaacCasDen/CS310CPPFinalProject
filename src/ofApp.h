#pragma once

#include "ofMain.h"
#include "GalagaShip.h"
#include "Missile.h"
#include <vector>
#include "Game.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    vector<GalagaShip*> galaga_ship;
    vector<Missile*> missiles;
    ofSerial serial;
    bool port;

	private:
		Game game;


};
