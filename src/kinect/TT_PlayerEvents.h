//
//  TT_PlayerEvents.h
//  openNi recorder
//
//  Created by Thomas Eberwein on 19/06/2012.
//  Copyright 2012 Thomas Traum Ltd. All rights reserved.
//

#ifndef openNi_recorder_TT_PlayerEvents_h
#define openNi_recorder_TT_PlayerEvents_h

#include "ofxOpenNI.h"
#include "ofEvents.h"

//--------------------------------------------------------------
class TT_NewUserEvent {
        
public:
    
    ofxOpenNIUser * user;
    XnUserID id;

    TT_NewUserEvent( ofxOpenNIUser * _user, XnUserID _id ):user(_user),id(_id){}
    
};

extern ofEvent<TT_NewUserEvent> TT_NewUserDispatcher;

//--------------------------------------------------------------
class TT_UserLostEvent {
    
public:
    
    ofxOpenNIUser * user;
    XnUserID id;
    
    TT_UserLostEvent( ofxOpenNIUser * _user, XnUserID _id ):user(_user),id(_id){}
    
};

extern ofEvent<TT_UserLostEvent> TT_UserLostEventDispatcher;

#endif
