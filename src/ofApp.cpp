#include "ofApp.h"

void ofApp::setup(){
    
    bLearnBackground = false;
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
    
    colorImg.allocate(320,240);
    grayImage.allocate(320,240);
    grayBg.allocate(320,240);
    grayDiff.allocate(320,240);
	
	minBlobSize = 1;
	maxBlobSize = 10;
	blobNum = 1;

	sender.setup(HOST, SPORT); //set up sender
}

void ofApp::update(){
    vidGrabber.update();
    //do we have a new frame?
    if (vidGrabber.isFrameNew()){
        colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg; // convert our color image to a grayscale image
        //if (bLearnBackground == true) {
        //    grayBg = grayImage; // update the background image
        //    bLearnBackground = false;
        //}
        //grayDiff.absDiff(grayBg, grayImage);
        //grayDiff.threshold(30);
        //contourFinder.findContours(grayDiff, 5, (340*240)/4, 4, false, true);
		
		contourFinder.findContours(grayImage, minBlobSize, maxBlobSize, blobNum, false, true);
    }
}

void ofApp::draw(){
    ofSetHexColor(0xffffff);
    //colorImg.draw(0, 0, 320, 240);
    //grayDiff.draw(0, 240, 320, 240);
	grayImage.draw(0, 0, 320, 240);
    ofDrawRectangle(320, 0, 320, 240);
    contourFinder.draw(320, 0, 320, 240);
    ofColor c(255, 255, 255);
    for(int i = 0; i < contourFinder.nBlobs; i++) {
		//ss << "Blob: ";
		if(contourFinder.blobs.size() > 0) {
			centroid = contourFinder.blobs.at(i).centroid;
			//ofRectangle r = contourFinder.blobs.at(i).boundingRect;
			//r.x += 320; r.y += 240;
			c.setHsb(i * 64, 255, 255);
			ofSetColor(c);
			//ofDrawRectangle(r);
			ofDrawCircle(centroid, 20);
			//ss << centroid << endl;
			blobLog = ofToString(centroid);

            ofxOscMessage m;
            m.setAddress("/position");
            m.addStringArg(blobLog);
            sender.sendMessage(m);

		} else {
			//ss << " NOT FOUND." << endl;
			blobLog = " NOT FOUND.";
		}
    }
	//ofDrawBitmapString( ss.str().c_str(), 20, 20);
	ofDrawBitmapString("Blob: " + blobLog, 10, 260);
}

void ofApp::keyPressed(int key) {
    bLearnBackground = true;
}
