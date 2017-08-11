#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"

#define HOST "192.168.205.220" //processing ip
//#define RPORT 12000 //incoming
#define SPORT 12000 //outgoing
//#define NUM_MSG_STRINGS 1

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

    ofxOscSender sender;
};
