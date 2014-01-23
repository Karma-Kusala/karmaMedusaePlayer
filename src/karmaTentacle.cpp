//
//  karmaTentacle.cpp
//  karmaMedusaePlayer
//
//  Created by Daan de Lange on 13/12/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#include "karmaTentacle.h"
#include <cmath>

karmaTentacle::karmaTentacle(int _direction){
	length = 300;
	diameter = 40;
	parts= 10; // complexity
	flexibility = 160; // angle in degrees
	speed = 0.9f;
	direction = _direction; // angle
	
	// pre-calc this one
	step = length*1.0f/parts;
	
	noise = std::abs((direction-180));//*ofRandom(.0f, 99.0f);
	
	// tentacle appearance
	//tentacle.setStrokeHexColor(0x000000);
	tentacle.setFilled(true);
	tentacle.setFillColor(ofColor(255,190));
	tentacle.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
	//tentacle.setStrokeWidth(0);
}

void karmaTentacle::update(){
	int i = 0;
	vector<ofPoint> tentacleCenterPoints, tentacleContourPoints;
	tentacleCenterPoints.resize(parts);
	tentacleContourPoints.resize(parts*2-1);
	while(i < parts){
		// calc some variants
		float scale = .1f + ( 1- (i/(parts*1.0f)))*.9f;
		float invertedScale = .2f + (i/(parts))*.8f;
		float width = diameter*scale;
		
		// tips change more acording to noise
		// begins start more according to frameNb stuff
		float currentAngleChange =
			sin( (ofGetFrameNum()+noise)*speed /((i%4+4)*10.0f)+i/2.0f )*flexibility*invertedScale*.9 +
			ofSignedNoise( ofGetElapsedTimef() /((i%4+4)*10.0f)+i/2.0f )*flexibility*scale*.1;
		//float mandalaAngleChange = ofSignedNoise( ofGetElapsedTimef()*4.3 /((i%4+4)*10.0f)+i/2.0f )*flexibility*scale;
		
		// first loop ? just set the first points
		if(i==0){
			// create start points
			tentacleCenterPoints[i] = ofVec2f(0,0);
			tentacleContourPoints[0] = ofVec2f(-width/2,0);
			tentacleContourPoints[1] = ofVec2f( width/2,0);
			
			// create next point (so we can transmit angle)
			tentacleCenterPoints[i+1] = tentacleCenterPoints[i] + ofPoint( cos(ofDegToRad(90+currentAngleChange) ), sin(ofDegToRad(90+currentAngleChange) ) ) * step;
			
			i++;
			continue;
		}
		
		// init some variables
		ofVec2f prevCenter, currentCenter, nextCenter;
		prevCenter = tentacleCenterPoints[i-1];
		currentCenter = tentacleCenterPoints[i]; // should use pointers here
		
		// get new rotation
		ofVec2f origin(-1,0); // 0 degree angle comparison point
		float prevAngle = origin.angle(ofVec2f(prevCenter-currentCenter));
		float currentAngle = prevAngle + currentAngleChange;
		
		// calc new center
		nextCenter = currentCenter + ofVec2f( cos(ofDegToRad(currentAngle) ), sin(ofDegToRad(currentAngle) ) ) * step;
		
		// last one? (tip of tentacle)
		if(i+1==parts){
			tentacleContourPoints[i*2]=currentCenter;
			i++;
			continue;
		}
		
		// remember nextCenter point
		tentacleCenterPoints[i+1] = nextCenter;
		
		// get bissector angle depending on previous rotation angle
		float bisectorAngle = prevAngle+90+currentAngleChange/2;
		//cout << prevAngle << endl;
		
		//ofCircle(currentCenter, 2);
		
		ofSetHexColor(0xff0000);
		
		ofPoint tmpContourDist = ofVec2f( cos(ofDegToRad(bisectorAngle) ), sin(ofDegToRad(bisectorAngle) ) ) * width/2;
		
		//ofLine(currentCenter+ofPoint(ofGetWidth()/2,0), currentCenter+tmpContourDist+ofPoint(ofGetWidth()/2,0));
		
		tentacleContourPoints[i*2] = currentCenter + tmpContourDist;
		tentacleContourPoints[i*2+1] = currentCenter + tmpContourDist*-1;
		
		i++;
	}
	
	// build path	
	tentacle.clear();
	tentacle.curveTo(tentacleCenterPoints[0]);

	// draw contour (1-3-5-7-9-11-12-10-8-6-4-2-0)(reversed)
	i = 0;
	int dir = 2;
	while(i >= 0){//< tentacleContourPoints.size() ){
		tentacle.curveTo( tentacleContourPoints[i] );
		//ofCircle( tentacleContourPoints[i] ,2);
		
		// reached top ?
		if( i==tentacleContourPoints.size()-1 ){
			i-=1;
			dir = -2; // invert dir
		}
		
		else i+=dir;
		
	}
	
	tentacle.curveTo(tentacleCenterPoints[1]);
	tentacle.close();
	
	//cout << tentacle.getCommands().toString();
	
	/*/ draw tentacle center points (for debugging)
	 i = 0;
	 while(i < tentacleCenterPoints.size() ){
	 ofCircle( tentacleCenterPoints[i], 2 );
	 //cout << tentacleCenterPoints[i].x << endl;//
	 i++;
	 } // */
}

void karmaTentacle::draw(){
	ofPushMatrix();
	ofRotateZ(direction);
	tentacle.draw();
	ofPopMatrix();
}