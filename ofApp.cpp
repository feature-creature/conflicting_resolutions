
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // initialize background
    bgColor = 150;
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(bgColor);
    ofSetColor(255);

    //initialize grid resolution
    numOfXTiles = 4; // 80-2,20-4,4-10
    numOfYTiles = 4; // 80-2,20-4,4-10

    // initialize 'pixels'
    ofSetCircleResolution(50);
    objSize = 70;

    // initialize grid spacing
    // 600/81 = 7.4
    spacingX = ofGetWidth()/numOfXTiles;
    spacingY = ofGetHeight()/numOfYTiles;

    face.load("ts-eliot-crop.jpeg");
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

    // background ghosting
    ofPushStyle();
    ofSetColor(bgColor,50);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofPopStyle();

    //pixels
    // iterate over rows
    for(int x = 1; x <= numOfXTiles; x++)
    {
        // iterate over current row's columns
        for(int y = 1; y <= numOfYTiles; y++)
        {
            // determine location of current pixel
            float locX = x*spacingX -spacingX/2;
            float locY = y*spacingY -spacingY/2;

            ofPushMatrix();
            ofPushStyle();
            // color
            ofColor gray = face.getColor(x*(80/numOfXTiles),y*(80/numOfYTiles));
            ofSetColor(gray);
//            if(x == 1 || y == 1 || x == numOfXTiles || y == numOfYTiles || y == numOfYTiles/2 ||x == numOfXTiles/2){ofSetColor(255,0,0);}
            // set location of current pixel
            ofTranslate(locX,locY);
            float angle = atan2(ofGetHeight()/2 - locY,ofGetWidth()/2 - locX);
            float shapeDist = ofDist(ofGetWidth()/2,ofGetHeight()/2,locX,locY);

            ofDrawCircle(0,0,objSize);


            // rotate in the (opposite + 180) direction from the window center
            ofRotate(ofRadToDeg(angle) + 180);
            // translate sinusoidally from the direction of the window's center
            ofTranslate(ofMap(sin(ofGetElapsedTimef() + ofMap(shapeDist,0,ofGetWidth()/2,PI,0)), 0, 1, 0, spacingX/1.25)-(spacingX*0.5),0);

//            ofSetColor(255,50);
//            ofDrawCircle(0,0,objSize);

            ofPopStyle();
            ofPopMatrix();
        }
    }

    // center seed circle
//    ofSetColor(255);
//    ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,objSize);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // save screenshot as png
    if(key == 's'){
        ofSaveScreen(ofToString(ofGetFrameNum())+".png");
    }

    if(key == '1'){
        numOfXTiles = 4;
        numOfYTiles = 4;
        objSize = 70;
        spacingX = ofGetWidth()/numOfXTiles;
        spacingY = ofGetHeight()/numOfYTiles;
    }
    if(key == '2'){
        numOfXTiles = 20;
        numOfYTiles = 20;
        spacingX = ofGetWidth()/numOfXTiles;
        spacingY = ofGetHeight()/numOfYTiles;
        objSize = 10;
    }
    if(key == '3'){
        numOfXTiles = 80;
        numOfYTiles = 80;
        spacingX = ofGetWidth()/numOfXTiles;
        spacingY = ofGetHeight()/numOfYTiles;
        objSize = 2;
    }


}
