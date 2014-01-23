//
//  karmaTentacle.h
//  karmaMedusaePlayer
//
//  Created by Daan de Lange on 13/12/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"

class karmaTentacle : public ofBaseApp{
	public:
		void update();
		void draw();
		karmaTentacle(int _direction);// constructor
	
	private:
		int length;
		int diameter;
		int parts;
		float flexibility;
		float speed;
		float direction;
		float step;
		float noise;
	
		ofPath tentacle;
		
};
