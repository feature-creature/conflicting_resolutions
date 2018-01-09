/*
 * author: Luke Demarest
 * title: conflicting resolutions
 * license: GPLv3
 * about:
 *
 * When considering the screen, through the lens of exploratory projection mapping, one can easily overlook the rectangle as a lively surface for creative work;
labeling it too quickly as a particularly square shape. The most pressing implementation questions are likely cornered at the topic of dimension and/or resolution, but not much more.
That alone seems suffecient reason to explore and tease out the subtle harmonies and conflicts within the rectangle's resolutions.

When considering the rectangular screen and its resolution, one must also consider the camera and its resolution. The two forms are seemingly intertwined.
So much of the intertwined communication between rectangular boxes and round lenses focuses and finds its roots on mapping human behavior and making simplified models of our complex reality.
A lot of this communication, and increasingly so with the turn from analog video to digital ip cameras, is in the form of survalience systems.
I read Axis Security's manual for implementing your own survalience system to gain insight into what shapes some of these forms.

Three classifications of resolution:

Detection registers if a human is present and has a necessary minimum resolution of 4X4 pixels across a standard 16 inch human face.
Recognition registers if a the same human as before is present and has a necessary minimum resolution of 20X20 pixels across a standard 16 inch human face.
Identification registers a specific human to a clarity 'beyond a reasonable doubt' and has a necessary minimum resolution of 80x80 pixels across a standard human face in poor enviroments.

As the manaul states the aim of building a survalience system is "creating a simplified models of a complex reality".
So much of science and the arts is based on approximation as are survalience systems, however, we often see the image, the screen, and the camera as arbitors of truth, sometimes regardless of the resolution or the conflict it brings.
Conflicting resolutions looks at the distingushing classifications of survalience, mapping humans to their abstracted elemental resolutions. Asking where is the line between the vague, the abstract, and the unique.
Numerous images in the work highlight the unconsious bias programmed into a contemporary technology: facial recognition software, where the accuracy of detection, recognition, and identifaction can drop based on factors like race of the software writers and users.

references:

https://www.axis.com/files/feature_articles/ar_perfect_pixel_count_55971_en_1402_lo.pdf
https://www.theguardian.com/technology/2017/may/28/joy-buolamwini-when-algorithms-are-racist-facial-recognition-bias
https://www.amazon.co.uk/Picking-Cotton-Memoir-Injustice-Redemption/dp/0312599536

" Ogle said. "Gee, it's really a shame that-" "That our political system revolves
around such trivial matters. Aaron, please do not waste my time and yours by voicing the obvious."
"Sorry."
"That's how it is, and how it will be until high-definition television becomes the norm." "Then what will
happen?"
"All of the politicians currently in power will be voted out of office and we will have a completely new
power structure. Because high-definition television has a flat gamma curve and higher resolution, and
people who look good on today's television will look bad on HDTV and voters will respond accordingly.
Their oversized pores will be visible, the red veins in their noses from drinking too much, the artificiality of
their TV-friendly hairdos will make them all look, on HDTV, like country-and-western singers. A new
generation of politicians will take over and they will all look like movie stars, because HDTV will be a
great deal like film, and movie stars know how to look good on film."

- Neal Stephenson, Interface, p 60 - http://www.gtfo.org/temp/Stephenson,%20Neal%20&%20Frederick%20George%20-%20Interface.pdf


*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // initialize background
    bgColor = 150;
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(bgColor);
    ofSetColor(255);
    pixelAlpha = 255;

    //initialize grid resolution
    numOfXTiles = 80;
    numOfYTiles = 80;

    growthSpeed = 10;

    // initialize 'pixels'
    objSize = 4;

    // initialize grid spacing
    spacingX = ofGetWidth()/numOfXTiles;
    spacingY = ofGetHeight()/numOfYTiles;

    // initial source data
    pixelBorder = 1.125;
    faceIt = ofRandom(0,9);
    face.load(ofToString(faceIt)+".jpeg");

    // initialize interaction
    growth = false;
    analyze = false;
    sceneFactor = 0;
    elapsed = ofGetElapsedTimef();


}

//--------------------------------------------------------------
void ofApp::update(){

    elapsed = ofGetElapsedTimef();

    // load random image on restart
    if(elapsed == 0 || elapsed == 1){
        faceIt = ofRandom(0,9);
        face.clear();
        face.load(ofToString(faceIt)+".jpeg");
    }

    if(elapsed < 30){
        // detection - 0-30 (30 sec)
        detection();
        if(elapsed > 12 && elapsed < 20){
            // visualize analysis
            analyze = elapsed % 3 ==0 ? true : false;
        }
        if(elapsed > 20 && elapsed < 30){
            // visualize analysis
            analyze = elapsed % 2 ==0 ? true : false;
        }
    }else if(elapsed > 29 && elapsed < 80){
        // recognition - 30 - 70 (40 sec)
        recognition();
        // visualize analysis
        if(elapsed > 65){
            analyze = elapsed % 3 ==0 ? true : false;
        }
    }else{
    // identification - 70 - 160 (90)
        identification();
        if(elapsed >= 130){
            growth = true;
        }
    }


    // prepare next classification
    if(ofGetElapsedTimeMillis() >= 0 && ofGetElapsedTimeMillis() < 60){
        changeScene();
    }
    if(ofGetElapsedTimeMillis() >= 30000 && ofGetElapsedTimeMillis() < 30060){
        changeScene();
    }
    if(ofGetElapsedTimeMillis() >= 80000 && ofGetElapsedTimeMillis() < 80060){
        changeScene();
    }
    if(elapsed >= 160){
        growth = false;
        changeScene();
        ofResetElapsedTimeCounter();
    }
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

            // initial grid translation
            ofPushMatrix();
            ofPushStyle();
            ofTranslate(locX,locY);
            float angle = atan2(ofGetHeight()/2 - locY,ofGetWidth()/2 - locX);
            float shapeDist = ofDist(ofGetWidth()/2,ofGetHeight()/2,locX,locY);

            ofPushMatrix();
            // rotate in the (opposite + 180) direction from the window center
            ofRotate(ofRadToDeg(angle) + 180);
            float liner = shapeDist - (ofGetElapsedTimef()-sceneFactor)*growthSpeed;
            // color data from source image
            ofColor gray = face.getColor(x*(80/numOfXTiles),y*(80/numOfYTiles));

            // identifaction ornimentation
            if(growth){
                ofPushMatrix();
                // sinusoudally move towards in space in relation to window center
                float liner = ofMap(shapeDist,0,ofGetWidth()/2,0,HALF_PI) - ofGetElapsedTimef() ;
                float siner = sin(liner);
                if(liner < shapeDist){
                ofTranslate(ofMap(siner, PI, HALF_PI, 0, spacingX/1.25)-(spacingX*0.5),0);
                ofSetColor(255,20);
                ofRotate(-1*(ofRadToDeg(angle) + 180));
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofDrawRectangle(0,0,objSize,objSize);
                ofPopMatrix();
                }
            }

            // translate white pixel if in the process of forming the grid
            if(liner > 0){
                ofTranslate(liner,0);
                ofSetColor(255,30);

            }else{
                // static, colored pixel
                ofSetColor(gray,pixelAlpha);
            }

            // rotate object orientation back to standard orientation
            ofRotate(-1*(ofRadToDeg(angle) + 180));
            ofSetRectMode(OF_RECTMODE_CENTER);

            // analysis visualization outlines
            if(analyze && liner <= 0){
                ofPushStyle();
                ofSetColor(200,40);
                ofDrawRectangle(0,0,objSize*pixelBorder,objSize*pixelBorder);
                ofPopStyle();
            }

            // the pixel
            ofDrawRectangle(0,0,objSize,objSize);

            ofPopMatrix();

            ofPopStyle();
            ofPopMatrix();
        }
    }
}

void ofApp::clearWindow(){
    ofSetColor(150);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
}

void ofApp::changeScene(){
    sceneFactor = ofGetElapsedTimef();
}

void ofApp::detection(){
    clearWindow();
    numOfXTiles = 4;
    numOfYTiles = 4;
    objSize = 155;
    spacingX = ofGetWidth()/numOfXTiles;
    spacingY = ofGetHeight()/numOfYTiles;
    growthSpeed = 40;
    pixelBorder = 1.125;
}

void ofApp::recognition(){
    clearWindow();
    numOfXTiles = 20;
    numOfYTiles = 20;
    spacingX = ofGetWidth()/numOfXTiles;
    spacingY = ofGetHeight()/numOfYTiles;
    objSize = 20;
    growthSpeed = 20;
    pixelBorder = 1.25;
}

void ofApp::identification(){
    clearWindow();
    numOfXTiles = 80;
    numOfYTiles = 80;
    spacingX = ofGetWidth()/numOfXTiles;
    spacingY = ofGetHeight()/numOfYTiles;
    objSize = 4;
    growthSpeed = 10;
    pixelBorder = 2;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // save screenshot as png
    if(key == 's'){
        ofSaveScreen(ofToString(ofGetFrameNum())+".png");
    }
    // testing image change
    if(key == '3'){
            faceIt = ofRandom(0,9);
            face.clear();
            face.load(ofToString(faceIt)+".jpeg");
    }
    // testing visualization ornimentation
    if(key == '4'){
        growth = !growth;
    }


}

