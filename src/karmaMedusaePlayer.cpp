#include "karmaMedusaePlayer.h"

//--------------------------------------------------------------
void karmaMedusaePlayer::setup(){
	ofSetVerticalSync(true);
	
	ofSetFrameRate(60);
	ofHideCursor();
	
	// create the medusae
	medusae = new karmaMedusae();
	
	// load movies
	moviesFolder.listDir("videos/");

	if( moviesFolder.size() ){
		scannedMovies.resize(moviesFolder.size());
		
		currentMovie = (int)( ofRandom(0, moviesFolder.size() ));
		player.setPixelFormat(OF_PIXELS_RGB);
		player.loadMovie( moviesFolder.getPath( currentMovie ) ); // loads first video in memory
		updateMovieDimensions( player.getWidth(), player.getHeight() );
		player.play();
		player.setVolume(0);
		player.setLoopState(OF_LOOP_NONE);
		cout << "Starting with video #" << currentMovie << "/" << moviesFolder.size() << endl;
	}
	
}

//--------------------------------------------------------------
void karmaMedusaePlayer::update(){
	ofHideCursor();
	// set FPS in window title
	string str = "framerate is ";
	str += ofToString(ofGetFrameRate(), 2)+"fps";
	ofSetWindowTitle(str);
	
	medusae->update();
	
	player.update();
	
	if( player.getIsMovieDone()) {
		currentMovie++;
		if(currentMovie >= moviesFolder.size()) currentMovie = 0; // rewind?
		
		cout << "Loading movie: " << moviesFolder.getPath( currentMovie) << endl;
		player.loadMovie( moviesFolder.getPath( currentMovie) ); // loads first video in memory
		updateMovieDimensions( player.getWidth(), player.getHeight() );
		player.play(); // relaunch play
	}
	
}

//--------------------------------------------------------------
void karmaMedusaePlayer::draw(){
	// erase
	ofBackground(128);
	ofSetColor(255);
	player.draw(currentMovieOffset.x, currentMovieOffset.y, currentMovieDimensions.x, currentMovieDimensions.y);
	
	// draw tentacle
	ofPushMatrix();
	
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	medusae->draw();
	
	ofPopMatrix();
}

//--------------------------------------------------------------
void karmaMedusaePlayer::keyPressed(int key){
	if(key == 'f' || key =='F'){
		ofToggleFullscreen();
		updateMovieDimensions( player.getWidth(), player.getHeight() );
	}
}

//--------------------------------------------------------------
void karmaMedusaePlayer::keyReleased(int key){

}

//--------------------------------------------------------------
void karmaMedusaePlayer::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void karmaMedusaePlayer::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void karmaMedusaePlayer::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void karmaMedusaePlayer::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void karmaMedusaePlayer::windowResized(int w, int h){

}

//--------------------------------------------------------------
void karmaMedusaePlayer::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void karmaMedusaePlayer::dragEvent(ofDragInfo dragInfo){ 

}

// pre-calculates some video-specific variables
void karmaMedusaePlayer::updateMovieDimensions(float mw, float mh){
	float videoRatio = mh * 1.0f / mw;
	float screenRatio =  ofGetHeight() *1.0f / ofGetWidth();
	
	// currentMovie larger than screen
	if(videoRatio < screenRatio){
		currentMovieDimensions = ofPoint( mw *( ofGetHeight()/ mh ) , ofGetHeight() );
		currentMovieOffset = ofPoint( (int) ((ofGetWidth()-currentMovieDimensions.x)/2), 0);
	}
	// currentMovie smaller than the screen
	else {
		currentMovieDimensions = ofPoint( ofGetWidth(), mh *( ofGetWidth()/mw ) );
		currentMovieOffset = ofPoint( 0, (int) ((ofGetHeight()-currentMovieDimensions.y)/2) );
	}
}