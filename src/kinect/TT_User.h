//
//  TT_User.h
//  openNi recorder
//
//  Created by Thomas Eberwein on 19/06/2012.
//  Copyright 2012 Thomas Traum Ltd. All rights reserved.
//

#ifndef openNi_recorder_TT_User_h
#define openNi_recorder_TT_User_h

#pragma once
#include "ofxOpenNI.h"

class TT_User {
    
    ofxOpenNIUser * niuser;
    XnUserID        id;
    
public:
    
    TT_User( ofxOpenNIUser * _niuser, XnUserID _id ){
        niuser = _niuser;
        id = _id;
    }
    
    ~TT_User() {
        ofLogNotice( "TT-NI" ) << "deleted user " << id;
    }
    
    void update() 
    {
    }
    
    void draw() 
    {
//        niuser->drawSkeleton();
//        ofLogNotice("TT") << "TT_USER " << id << " " << niuser->getNumJoints();
        
        for(int j = 0; j < niuser->getNumJoints(); j++){
            ofxOpenNIJoint & joint = niuser->getJoint((Joint)j);
            
//            cout << joint.getName() << endl;
            
            if (j==0) {
                ofSetColor( 255,0,0);
                //                ofLogNotice("TT") << "getWorldPosition:      " << joint.getWorldPosition();
                //                ofLogNotice("TT") << "getProjectivePosition: " << joint.getProjectivePosition();
            } else {
                ofSetColor( 255,255,255);
            }
            
//            ofBox(joint.getWorldPosition(), 20);
            ofCircle( joint.getWorldPosition(), 20 ); 
            
            //do something with the joint, or:
            if(joint.isParent()){ // ie., it's like a limb...
                // ...do something with the "limb"
                ofSetColor( 255,255,0);
                ofLine(ofVec3f(joint.getWorldPosition()), ofVec3f(joint.getParent().getWorldPosition()));
            }
        }
    }
    
    XnUserID getID()
    {
        return id;
    }
    
};

#endif
