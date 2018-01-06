
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // initialize background
    bgColor = 150;
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(bgColor);
    ofSetColor(255);

    //initialize grid resolution
    numOfXTiles = 80; // 80,20,4
    numOfYTiles = 80; // 80,20,4

    // initialize grid spacing
    spacingY = ofGetHeight()/numOfYTiles;
    spacingX = ofGetWidth()/numOfXTiles;

    // initialize 'pixels'
    objSize = 2;
    objMovementDist = spacingX;
    ofSetCircleResolution(50);
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

    // center the shapes
    // width-gridsize/2
    ofTranslate(((ofGetWidth()-(spacingX*numOfXTiles))/2) + (spacingX/2),((ofGetHeight()-(spacingY*numOfYTiles))/2) + (spacingY/2));
    // iterate over grid rows
    for(int x = 0; x < numOfXTiles; x++)
    {
        // iterate over current row's columns
        for(int y = 0; y < numOfYTiles; y++)
        {
            // determine current pixel's location
            float locX = x*spacingX;
            float locY = y*spacingY;

            ofPushMatrix();
            ofPushStyle();

            // debugging
            if(x == numOfXTiles - 1|| x == 0 || y == numOfYTiles - 1 || y == 0 || x == numOfXTiles/2 || y == numOfYTiles/2 || x == numOfXTiles/2 - 1 || y == numOfYTiles/2 - 1){
                ofSetColor(0);
            }else{
                ofSetColor(255);
            }

            ofTranslate(locX,locY);
            ofDrawCircle(0,0,objSize);

            ofPopStyle();
            ofPopMatrix();
        }
    }
}
