//
//  ofApp.cpp
//  Frequency
//
//  Code by Andreas Müller from NoiseWorkshop
//
//  Commented and reformatted by Haley Van Camp on 4/28/15.
//

#include "ofApp.h"


// --------------------------------
void ofApp::setup()
{
    fontSmall.loadFont("Fonts/DIN.otf", 8 ); // load type of font at size 8
}

// --------------------------------
void ofApp::draw()
{
    // set background color with a circular gradient
    ofBackgroundGradient( ofColor(55), ofColor(0), OF_GRADIENT_CIRCULAR );
    
    ofEnableAlphaBlending(); // turn on alpha blending
    
    // As we are feeding values measured in pixels, the frequency value will be pretty small
    // remaps input of mouse position 0, width to a number between .0001 to .05
    frequency = ofMap( ofGetMouseX(),  0, ofGetWidth(),  0.0001, 0.05 );
    
    // Draw ticks at each unit edge
    // uses ceil to make value an integer
    numTicks = ceil(ofGetWidth() * frequency); // number between 1/10 and 50
    areaCovered = numTicks; // setting areaCovered to numTicks
    if( numTicks <= 5 ) { numTicks *= 10; } // if numTicks is <= 5 it is multipled by 10 so there are 10 decimal numbers between each integer
    
    // draws the lines and the numbers at the top
    for( int i = 0; i < numTicks; i++ )
    {
        // remaps noisePos from 0, numTicks input to 0, areaCovered output
        noisePos = ofMap( i, 0, numTicks, 0, areaCovered);
        screenX = noisePos * (1.0/frequency);
        
        top = ofVec2f( screenX, 0); // initalizes top
        bot = ofVec2f( screenX, ofGetHeight()); // initializes bottom
        
        // Brighter white lines at unit edges (0,1,2) and less bright at fractionals (0.1,0.2, etc), but only if we are zoomed in enough
        if( (abs(fmodf(noisePos, 1.0)) <= 0) && areaCovered < 18 )  { ofSetColor( ofColor::white, 90 ); } else { ofSetColor( ofColor::white, 30 );  }
        
        ofLine( top, bot); // draw line at top, bottom
        
        textPos = ofVec2f(top + ofVec2f(4,20)); // initializing textPos of number
        fontSmall.drawString( ofToString(noisePos), textPos.x, textPos.y ); // prints the number at the tick
    }
    
    // Compute a noise position for each pixels x position, taking a frequency value into account
    noiseMagnitude = 300; // initializing noiseMagnitude
    ofMesh mesh;
    mesh.setMode( OF_PRIMITIVE_LINE_STRIP ); // set mesh with line strip
    res = ofGetWidth(); // initializing res to width
    // builds a vector mesh containing points from 0 to the width of screen
    for( int i = 0; i < res; i++ )
    {
        // remaps pos input of 0, res to output width and height * .5f
        pos = ofVec2f( ofMap( i, 0, res, 0, ofGetWidth() ), ofGetHeight() * 0.5f );
        
        // setting noisePos to pos.x multiplied by frequency
        noisePos = (pos.x * frequency);
        noiseValue = ofSignedNoise( noisePos ); // ofSignedNoise gives us a value -1.1
        
        // setting drawPos
        drawPos = ofVec2f(pos + ofVec2f(0,noiseValue * noiseMagnitude));
        
        mesh.addVertex( drawPos ); // adding drawPos to mesh
    }
    
    ofSetColor( ofColor::white ); // setting color
    mesh.draw(); // drawing mesh
}

// --------------------------------
void ofApp::keyPressed( int key )
{
    // does nothing
    if( key == ' ' )
    {
    }
}
