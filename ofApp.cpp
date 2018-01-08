
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

    growthSpeed = 40;

    // initialize 'pixels'
    ofSetCircleResolution(50);
    objSize = 70;

    // initialize grid spacing
    // 600/81 = 7.4
    spacingX = ofGetWidth()/numOfXTiles;
    spacingY = ofGetHeight()/numOfYTiles;

    face.load("ts-eliot-crop.jpeg");

    growth = true;
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

            //ENTER
            if(growth){
            ofPushMatrix();
            ofRotate(ofRadToDeg(angle) + 180);
            // different timing scaling for each stage
            // start time over at each new iteration
            float liner = shapeDist - ofGetElapsedTimef()*growthSpeed ;
            float siner = sin(liner);
            ofColor gray = face.getColor(x*(80/numOfXTiles),y*(80/numOfYTiles));
            if(liner > 0){
            ofTranslate(liner,0);
            ofSetColor(255,30);
//            ofSetColor(gray,30);
            }else{
            ofSetColor(gray);
            }
            ofDrawCircle(0,0,objSize);
            // rotate object orientation back to standard
//            ofRotate(-1*(ofRadToDeg(angle) + 180));
//            ofSetRectMode(OF_RECTMODE_CENTER);
//            ofDrawRectangle(0,0,objSize,objSize);
            ofPopMatrix();

            //EXIT
            }else{

                ofPushMatrix();
                ofRotate(ofRadToDeg(angle) + 180);
                // different timing scaling for each stage
                // start time over at each new iteration
                float liner = ofMap(shapeDist,0,ofGetWidth()/2,0,HALF_PI) + ofGetElapsedTimef()*3 ;
                float siner = sin(liner);
                ofColor gray = face.getColor(x*(80/numOfXTiles),y*(80/numOfYTiles));

                if(liner < shapeDist){
                ofTranslate(liner,0);
                ofSetColor(255,30);
                ofRotate(-1*(ofRadToDeg(angle) + 180));
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofDrawRectangle(0,0,objSize,objSize);
                ofPopMatrix();
                }
            }


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

void ofApp::validate(){
    ofSetColor(255);
}

void ofApp::invalidate(){
    ofSetColor(0);
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
        growthSpeed = 40;
    }
    if(key == '2'){
        clearWindow();
        numOfXTiles = 20;
        numOfYTiles = 20;
        spacingX = ofGetWidth()/numOfXTiles;
        spacingY = ofGetHeight()/numOfYTiles;
        objSize = 10;
        growthSpeed = 20;
    }
    if(key == '3'){
        clearWindow();
        numOfXTiles = 80;
        numOfYTiles = 80;
        spacingX = ofGetWidth()/numOfXTiles;
        spacingY = ofGetHeight()/numOfYTiles;
        objSize = 2;
        growthSpeed = 10;
    }
    if(key == '4'){
        growth = !growth;
    }


}

