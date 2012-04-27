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
    
    openNIDevice.setMaxNumUsers(4); // defualt is 4
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
	ofDrawBitmapString(msg, 20, ofGetHeight()-25);
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

void ofxOpenNITT::drawCenter()
{   
    int numUsers = openNIDevice.getNumTrackedUsers();
    for (int nID = 0; nID < numUsers; nID++){
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(nID);
        ofPoint p = user.getCenter();
        ofLogNotice("TT") << p;
        ofSetColor(255, 255, 255);
        ofBox(p.x,p.y,-500, 50);
    }
}

//--------------------------------------------------------------
void ofxOpenNITT::draw3dUsers()
{
    
//    ofPoint p1 = ofPoint( 10,10,10 );
//    ofPoint projective = g_worldToProjective( p1 ); 
//    cout << "projective: " << projective << endl;
//    ofPoint world = openNIDevice.projectiveToWorld(p1);
//    cout << "world: " << world << endl;
    
    
    glEnable(GL_DEPTH_TEST);
    ofPushStyle();
    glMatrixMode(GL_PROJECTION);
    ofPushMatrix();
    
    float flipped[] = {
        1, 0, 0, 0,
        0, 1, 0, 0, 
        0, 0, -1, 0,
        0, 0, 0, 1
    };
    glMultMatrixf( flipped );

    for(int i = 0; i < openNIDevice.getNumTrackedUsers(); i++){
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        for(int j = 0; j < user.getNumJoints(); j++){
            ofxOpenNIJoint & joint = user.getJoint((Joint)j);
            
//            cout << joint.getName();
  
            if (j==0) {
                ofSetColor( 255,0,0);
//                ofLogNotice("TT") << "getWorldPosition:      " << joint.getWorldPosition();
//                ofLogNotice("TT") << "getProjectivePosition: " << joint.getProjectivePosition();
            } else {
                ofSetColor( 255,255,255);
            }
            
            ofBox(joint.getWorldPosition(), 20);
            
            //do something with the joint, or:
            if(joint.isParent()){ // ie., it's like a limb...
                // ...do something with the "limb"
                ofSetColor( 255,255,0);
                ofLine(ofVec3f(joint.getWorldPosition()), ofVec3f(joint.getParent().getWorldPosition()));
            }
        }
    }
    
//    int numUsers = openNIDevice.getNumTrackedUsers();
//    for (int nID = 0; nID < numUsers; nID++){
//        ofxOpenNIUser & user = openNIDevice.getTrackedUser(nID);
//        ofPoint p = user.getCenter();
//        ofLogNotice("TT") << p;
//        ofSetColor(255, 255, 0);
//        ofBox(p, 100);
//        ofSetColor(0, 0, 255);
//        ofBox(p.x,p.y,0, 100);
//    }
    
    ofPopMatrix();
    ofPopStyle();
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

ofPoint ofxOpenNITT::kinectSpaceToWorldSpace( ofPoint p )
{
    // this assumes a 640 x 480 resolution as per above defines
//    ofPoint projective;
//    projective.x = COEFX * p.x / p.z + HALFWIDTH;
//    projective.y = HALFHEIGHT - COEFY * p.y / p.z;
//    projective.z = p.z;
//    return projective;
    
    // this assumes a 640 x 480 resolution as per above defines
    ofPoint projective;
    projective.x = COEFX * p.x / p.z + HALFWIDTH;
    projective.y = HALFHEIGHT - COEFY * p.y / p.z;
    projective.z = p.z;
    return projective;
    
    
}





