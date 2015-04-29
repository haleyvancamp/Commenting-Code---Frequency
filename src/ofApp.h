//  Code by Andreas MŸller from NoiseWorkshop
//
//  Commented and reformatted by Haley Van Camp on 4/28/15.

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
	public:
    // declaring functions
    void setup();
    void draw();
    void keyPressed(int key);
    
    // declaring variables
    float frequency, areaCovered, noisePos, noiseValue, screenX, noiseMagnitude;
    int numTicks, res;
    ofVec2f top, bot, textPos, pos, drawPos;
    ofTrueTypeFont fontSmall;
    
	
};
