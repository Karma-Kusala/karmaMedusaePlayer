//
//  karmaMedusae.h
//  karmaMedusaePlayer
//
//  Created by Daan de Lange on 13/12/13.
//  Copyright 2013 Karma Kusala. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "karmaTentacle.h"

class karmaMedusae : public ofBaseApp{
	public:
		void update();
		void draw();
		karmaMedusae(); // constructor
	
private:
	int nTentacles;
	int angleSpan;
	//vector<karmaTentacle> tentacles;
	karmaTentacle** tentacles;
	
	ofImage karmaLogo;
};
