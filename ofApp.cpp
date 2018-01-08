
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // initialize background
    bgColor = 150;
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(bgColor);
    ofSetColor(255);

    //initialize grid resolution
    numOfXTiles = 4;
    numOfYTiles = 4;

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
            ofTranslate(locX,locY);
            float angle = atan2(ofGetHeight()/2 - locY,ofGetWidth()/2 - locX);
            float shapeDist = ofDist(ofGetWidth()/2,ofGetHeight()/2,locX,locY);


            // growth pixels
            // rotate in the (opposite + 180) direction from the window center
            // translate sinusoidally from the direction of the window's center
            ofPushMatrix();
            ofRotate(ofRadToDeg(angle) + 180);
            float liner = ofGetElapsedTimef() + ofMap(shapeDist,0,ofGetWidth()/2,0,HALF_PI);
            float siner = sin(liner);
            ofTranslate(ofMap(siner, -0.45, 1, 0, spacingX/2)-(spacingX*0.5),0);
            ofSetColor(255,30);
            ofDrawCircle(0,0,objSize);
            ofPopMatrix();

            // static pixels
            // color
            ofColor gray = face.getColor(x*(80/numOfXTiles),y*(80/numOfYTiles));
            ofSetColor(gray);
            ofDrawCircle(0,0,objSize);



            ofPopStyle();
            ofPopMatrix();
        }
    }


    // center seed circle
//    ofSetColor(255);
//    ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,objSize);
}

void ofApp::clearWindow(){
    ofSetColor(150);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // save screenshot as png
    if(key == 's'){
        ofSaveScreen(ofToString(ofGetFrameNum())+".png");
    }

    if(key == '1'){
        clearWindow();
        numOfXTiles = 4;
        numOfYTiles = 4;
        objSize = 70;
        spacingX = ofGetWidth()/numOfXTiles;
        spacingY = ofGetHeight()/numOfYTiles;
    }
    if(key == '2'){
        clearWindow();
        numOfXTiles = 20;
        numOfYTiles = 20;
        spacingX = ofGetWidth()/numOfXTiles;
        spacingY = ofGetHeight()/numOfYTiles;
        objSize = 10;
    }
    if(key == '3'){
        clearWindow();
        numOfXTiles = 80;
        numOfYTiles = 80;
        spacingX = ofGetWidth()/numOfXTiles;
        spacingY = ofGetHeight()/numOfYTiles;
        objSize = 2;
    }


}

