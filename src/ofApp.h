#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    bool bLearnBackground;
    
    stringstream ss;
    ofVec3f centroid;
    string blobLog;
    
    int minBlobSize;
    int maxBlobSize;
    int blobNum;
    ofVideoGrabber vidGrabber;
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImage, grayBg, grayDiff;
    ofxCvContourFinder contourFinder;
};
