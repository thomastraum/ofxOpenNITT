//
//  ofxOpenNITT.h
//  openNiSample007
//
//  Created by Thomas Eberwein on 25/04/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

//#ifndef _ofxOpenNITT
//#define _ofxOpenNITT

#pragma once
#include "ofMain.h"
#include "ofxOpenNI.h"

class ofxOpenNITT {

private:
    
    ofxOpenNI openNIDevice;
    
    bool debug_draw;
    void drawDebug();
    
    void drawUsers();
    
public:
    
    ofxOpenNITT(){};
    
    void setup();
    void update();
    
    void draw();
    void draw3dUsers();
    void draw3dUser();
    
    void exit();
    void keyPressedEvent( ofKeyEventArgs & args );
    
    
};

//#endif