#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void clearWindow();
    void validate();
    void invalidate();

    int bgColor;
    int numOfXTiles;
    int numOfYTiles;
    int spacingX;
    int spacingY;
    int startingX;
    int startingY;
    int objSize;
    int objMovementDist;

    int initialWidth;
    int initialHeight;

    ofImage face;
    bool growth;
    int growthSpeed;
};
