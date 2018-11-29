#pragma once

#include "ofMain.h"
#include "../Game.h"

#include "GalagaShip.h"
#include <vector>
class ofApp : public ofBaseApp{

	public:
		ofApp();
		~ofApp();

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
		void exit();

	private:
		Game game;

		vector<GalagaShip*> galaga_ship;
		ofSerial serial;
		bool port;
};
