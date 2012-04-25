//
//  ofxOpenNITT.cpp
//  openNiSample007
//
//  Created by Thomas Eberwein on 25/04/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "ofxOpenNITT.h"

//--------------------------------------------------------------
void ofxOpenNITT::setup() {
    
    ofSetLogLevel(OF_LOG_NOTICE);
    
    openNIDevice.setup();
    //openNIDevice.setLogLevel(OF_LOG_VERBOSE);
    openNIDevice.addDepthGenerator();
    openNIDevice.addImageGenerator();
    openNIDevice.addUserGenerator();
    
    openNIDevice.setRegister(true); // register depth to image
    openNIDevice.setMirror(true);
    
    openNIDevice.setMaxNumUsers(2); // defualt is 4
    //    openNIDevice.setUseMaskTextureAllUsers(true);
    //    openNIDevice.setUsePointCloudsAllUsers(true);
    //    openNIDevice.setPointCloudDrawSizeAllUsers(3); // sets the size the points are drawn on screen (in pixels)
    //    openNIDevice.setPointCloudResolutionAllUsers(2); // sets the step between pixels and point cloud eg., 1 is every pixel, 2 is every second pixel etc
    
	openNIDevice.start();
    
    ofxOpenNIUser user;
    user.setUseMaskTexture(true);
    user.setUsePointCloud(true);
    user.setPointCloudDrawSize(2); // this is the size of the glPoint that will be drawn for the point cloud
    user.setPointCloudResolution(2); // this is the step size between points for the cloud -> eg., this sets it to every second point
    openNIDevice.setBaseUserClass(user); // this becomes the base class on which tracked users are created
    // allows you to set all tracked user properties to the same type easily
    
    debug_draw = true;
    ofAddListener( ofEvents.keyPressed, this, &ofxOpenNITT::keyPressedEvent );
}

//--------------------------------------------------------------
void ofxOpenNITT::update(){
    ofBackground(0, 0, 0);
    openNIDevice.update();
}

//--------------------------------------------------------------
void ofxOpenNITT::draw()
{
	ofSetColor(255, 255, 255);
//    drawUsers();
//    draw3dUsers();
    if ( debug_draw ) drawDebug();    // do some drawing of user clouds and masks

	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate());
	ofDrawBitmapString(msg, 20, 506);
}

//--------------------------------------------------------------
void ofxOpenNITT::drawUsers()
{
    ofPushMatrix();
    ofScale(ofGetWidth()/openNIDevice.getWidth(), ofGetHeight() / openNIDevice.getHeight() );
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    int numUsers = openNIDevice.getNumTrackedUsers();
    for (int nID = 0; nID < numUsers; nID++){
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(nID);
        user.drawMask();
        user.drawSkeleton();
        
        ofPushMatrix();
        ofTranslate(320, 240, -1000);
        user.drawPointCloud();
        ofPopMatrix();
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofxOpenNITT::draw3dUsers()
{
    //    ofEnableAlphaBlending();
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();

    int numUsers = openNIDevice.getNumTrackedUsers();
    for (int nID = 0; nID < numUsers; nID++){
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(nID);
        ofPushStyle();
        ofSetColor(255, 0, 0);
//        ofLogNotice("TT") << user.getCenter();
        ofPoint p = user.getCenter(); //*-1;
        p.rotate( 180, ofVec3f(1,1,1));
//        ofLogNotice("TT") << p;
        ofCircle( p, 200 );
        ofPopStyle();
    }

    glPopMatrix();
    //    ofDisableAlphaBlending();
    glDisable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void ofxOpenNITT::draw3dUser()
{
//    ofLogNotice("TT") << user.getCenter();
    
}


//--------------------------------------------------------------
void ofxOpenNITT::drawDebug()
{
    openNIDevice.drawDebug(); // debug draw does the equicalent of the commented methods below
    //openNIDevice.drawDepth(0, 0, 640, 480);
    //openNIDevice.drawImage(640, 0, 640, 480);
    //openNIDevice.drawSkeletons(640, 0, 640, 480);
}

//--------------------------------------------------------------
void ofxOpenNITT::exit(){
    // this often does not work -> it's a known bug -> but calling it on a key press or 
    // anywhere that isnt std::aexit() works...press 'x' to shutdown cleanly...
    openNIDevice.stop();
}

//--------------------------------------------------------------
void ofxOpenNITT::keyPressedEvent(ofKeyEventArgs & args)
{
    switch (args.key) {
        case '1':
            if ( debug_draw ) debug_draw = false;
            else debug_draw = true;
            break;
        case 'x':
            openNIDevice.stop();
            break;
    }
}

