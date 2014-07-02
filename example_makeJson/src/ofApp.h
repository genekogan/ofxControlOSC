#pragma once

#include "ofMain.h"
#include "ofxControlOSC.h"


class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ofxControlOSC controlOsc;
};
