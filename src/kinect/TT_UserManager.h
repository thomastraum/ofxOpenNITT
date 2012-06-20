//
//  TT_UserManager.h
//  openNi recorder
//
//  Created by Thomas Eberwein on 19/06/2012.
//  Copyright 2012 Thomas Traum Ltd. All rights reserved.
//

#ifndef openNi_recorder_TT_UserManager_h
#define openNi_recorder_TT_UserManager_h

#pragma once
#include "ofxOpenNI.h"
#include "TT_PlayerEvents.h"
#include "TT_User.h"

class TT_UserManager {
    
    vector<TT_User*>    users;
    
public:
    
    TT_UserManager(){
        ofAddListener( TT_UserLostEventDispatcher,this,&TT_UserManager::deleteUser );
        ofAddListener( TT_NewUserDispatcher,this,&TT_UserManager::createNewUser );
    }
    
    //--------------------------------------------------------------
    void update() 
    {
        vector<TT_User*>::iterator it = users.begin();
        while( it != users.end() ) {
            TT_User * u = *it;
            u->update();
            it++;
        }
    }
    
    //--------------------------------------------------------------
    void draw() 
    {   

        vector<TT_User*>::iterator it = users.begin();
        while( it != users.end() ) {
            TT_User * u = *it;
            u->draw();
            it++;
        }
        
        
//        ofPushStyle();
//        glEnable(GL_DEPTH_TEST);
//        
////        glMatrixMode(GL_PROJECTION);
////        ofPushMatrix();
////
////        float flipped[] = {
////            1, 0, 0, 0,
////            0, 1, 0, 0, 
////            0, 0, 1, 0,
////            0, 0, 0, 1
////        };
////        glMultMatrixf( flipped );
//        
//        vector<TT_User*>::iterator it = users.begin();
//        while( it != users.end() ) {
//            TT_User * u = *it;
//            u->draw();
//            it++;
//        }
////        glLoadIdentity();
////        glMatrixMode(GL_PROJECTION);
////        ofPopMatrix();
//        
//        glDisable(GL_DEPTH_TEST);
//        ofPopStyle();
    }
    
protected:
    
    //--------------------------------------------------------------
    void createNewUser( TT_NewUserEvent & event ) 
    {
        ofLogNotice("TT-NI") << "TT_UserManager::createNewUser ---------------------------- ";
        ofLogNotice("TT-NI") << event.user->getDebugInfo();
        
        // Sometimes we can get a new user event twice for the same user //
        deleteUser( event.id );
        
        TT_User * user = new TT_User( event.user, event.id );
        users.push_back( user );
    }
    
    //--------------------------------------------------------------
    void deleteUser( TT_UserLostEvent & event )
    {
        ofLogNotice("TT-NI") << "TT_UserManager::deleteUser ---------------------------- ";
        ofLogNotice("TT-NI") << event.user->getDebugInfo();
        
        deleteUser( event.id );
    }
    
    //--------------------------------------------------------------
    void deleteUser( int _id )
    {
        vector<TT_User*>::iterator it = users.begin();
        while( it != users.end() ) {
            TT_User * u = *it;
            if( u->getID() == _id ) {
                delete * it;  
                it = users.erase(it);
            } else {
                it++;
            }
        }
    }
    
};

#endif
