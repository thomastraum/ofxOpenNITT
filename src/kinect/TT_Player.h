//
//  TT_Player.h
//  openNi recorder
//
//  Created by Thomas Eberwein on 18/06/2012.
//  Copyright 2012 Thomas Traum Ltd. All rights reserved.
//

#ifndef openNi_recorder_TT_Player_h
#define openNi_recorder_TT_Player_h

#pragma once
#include "ofxOpenNI.h"
#include "TT_PlayerEvents.h"

class TT_Player {
    
    ofxOpenNI   openNIPlayer;
    int         draw_width;
    int         draw_height;
    bool        draw_debug; 

protected:
    
    
    //--------------------------------------------------------------
    void exit( ofEventArgs & arg )
    {
        openNIPlayer.stop();
    }
    
    //--------------------------------------------------------------
    void keyPressed( ofKeyEventArgs & arg )
    {
        switch (arg.key) {
                
            case '.':
                draw_debug = !draw_debug;
                break;
                
            default:
                break;
        }
    }
    
public:
    
    TT_Player() {
        
        openNIPlayer.setup();
//        openNIPlayer.start();
        openNIPlayer.addDepthGenerator();
        openNIPlayer.addImageGenerator();
        openNIPlayer.setRegister(true);
        openNIPlayer.setMirror(true);
        openNIPlayer.addUserGenerator();
        openNIPlayer.setMaxNumUsers(4);
        
	    ofAddListener(ofEvents().exit, this, &TT_Player::exit);
	    ofAddListener(ofEvents().keyPressed, this, &TT_Player::keyPressed);
        
        draw_width = 400 *2;
        draw_height = 300;
        draw_debug = false;
        
        ofAddListener( ofxOpenNIUserEventDispatcher,this,&TT_Player::userEvent );
    }
    
    //--------------------------------------------------------------
    void update( )
    {
        openNIPlayer.update();
    }
    
    //--------------------------------------------------------------
    void draw()
    {
        if ( draw_debug ) {
            ofPushStyle();
            ofPushMatrix();
            ofSetColor(255, 255, 255);
            openNIPlayer.drawDebug(0, 0, draw_width, draw_height );
            ofPopMatrix();
            ofPopStyle();
        }
    }
    
    //--------------------------------------------------------------
    void play( string _oniFileName )
    {
        openNIPlayer.startPlayer( _oniFileName );
        openNIPlayer.addUserGenerator();
        openNIPlayer.setMaxNumUsers(4);
        
//	    ofAddListener(ofEvents().update, this, &TT_Player::update);
//	    ofAddListener(ofEvents().draw, this, &TT_Player::draw);
    }
    
    //--------------------------------------------------------------
    void stop()
    {
//        openNIPlayer.stopPlayer();
//	    ofRemoveListener(ofEvents().update, this, &TT_Player::update);
//	    ofRemoveListener(ofEvents().draw, this, &TT_Player::draw);
    }
    
    //--------------------------------------------------------------
    void userEvent(ofxOpenNIUserEvent & event)
    {
        ofLogNotice( "TT-NI" ) << "TT_Player::userEvent ------------------------:";
        
        /*       
         enum UserStatusType {
         USER_TRACKING_STOPPED = 0,
         USER_TRACKING_STARTED,
         USER_CALIBRATION_STOPPED,
         USER_CALIBRATION_STARTED,
         USER_SKELETON_LOST,
         USER_SKELETON_FOUND
         };
         
         int deviceID;
         UserStatusType userStatus;
         XnUserID id;
         int timestampMillis;
         */
        
        ofLogNotice() << getUserStatusAsString(event.userStatus) << " for user " << event.id << " from device " << event.deviceID;
        
        // the event.id is 1 when the index in the vector is 0
        // we just use the vector index of 0 as better suited for us 
        
        if ( event.userStatus == USER_SKELETON_FOUND ) {
            TT_NewUserEvent new_user = TT_NewUserEvent( &openNIPlayer.getTrackedUser(event.id-1), event.id-1 );
            ofNotifyEvent(TT_NewUserDispatcher, new_user);
        }
        
        if ( event.userStatus == USER_TRACKING_STOPPED ) {
            TT_UserLostEvent user_lost = TT_UserLostEvent( &openNIPlayer.getTrackedUser(event.id-1), event.id-1 );
            ofNotifyEvent(TT_UserLostEventDispatcher, user_lost);
        }
        
        
    }
};


#endif
