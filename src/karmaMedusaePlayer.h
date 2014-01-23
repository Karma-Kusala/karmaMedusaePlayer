#pragma once

#include "ofMain.h"
#include "karmaMedusae.h"

class karmaMedusaePlayer : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		karmaMedusae *medusae;
		ofVideoPlayer player;
		ofDirectory moviesFolder;
		vector<string> scannedMovies;
		int currentMovie;
		ofPoint currentMovieDimensions, currentMovieOffset;
	
		void updateMovieDimensions(float mw, float mh);
	
};
