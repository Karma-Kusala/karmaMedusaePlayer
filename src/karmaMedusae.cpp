//
//  karmaMedusae.cpp
//  karmaMedusaePlayer
//
//  Created by Daan de Lange on 13/12/13.
//  Copyright 2013 Karma Kusala. All rights reserved.
//

#include "karmaMedusae.h"

karmaMedusae::karmaMedusae(){
	
	// remember params
	nTentacles = 8;
	angleSpan = 360;
	
	// create tentacles
	tentacles = new karmaTentacle*[ nTentacles ]; // creates an empty array of pointers
	for (int i = 0; i < nTentacles; i++){
		int angle = (int) 0-((360-angleSpan)/2) + (angleSpan/nTentacles)*i;
		tentacles[i] = new karmaTentacle( angle );
	}
	
	karmaLogo.loadImage("logo.png");
}

void karmaMedusae::update(){
	// update tentacles
	for (int i = 0; i < nTentacles; i++){
		tentacles[i]->update();
	}
}

void karmaMedusae::draw(){
	// draw the tentacle
	
	ofPushMatrix();
	
	// translate
	ofTranslate(cos(ofNoise(ofGetElapsedTimef()/2))*100, sin(ofGetElapsedTimef()/3)*70);
	
	// setup drawing environment
	//ofSetHexColor(0xffffff);
	ofFill();
	//ofSetHexColor(0xffffff);
	ofSetColor(255, 200);
	
	// draw tentacles
	for (int i = 0; i < nTentacles; i++){
		tentacles[i]->draw();
	}
	
	karmaLogo.draw(-karmaLogo.width/2,-karmaLogo.height/2);
	
	ofPopMatrix();
}