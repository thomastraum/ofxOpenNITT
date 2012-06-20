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
#include "particle.h"

class TT_User {
    
    ofxOpenNIUser * niuser;
    XnUserID        id;
    
    ofMatrix4x4     trans, scale;
    
    vector<Particle*> particles;
    
public:
    
    //--------------------------------------------------------------
    TT_User( ofxOpenNIUser * _niuser, XnUserID _id ){
        niuser = _niuser;
        id = _id;
        
        scale.makeScaleMatrix(ofVec3f(1,1,-1) );
        // I made those up
        trans.makeTranslationMatrix(ofVec3f(0,0,1500));
        
        initParticles();
    }
    
    //--------------------------------------------------------------
    ~TT_User() {
        ofLogNotice( "TT-NI" ) << "deleted user " << id;
    }
    
    //--------------------------------------------------------------
    void initParticles()
    {
        for(int i = 0; i < niuser->getNumJoints(); i++){
            
            ofxOpenNIJoint & joint = niuser->getJoint((Joint)i);
            
            if ( joint.getType() == JOINT_TORSO ||
                joint.getType() == JOINT_HEAD ||
                joint.getType() == JOINT_LEFT_ELBOW || 
                joint.getType() == JOINT_LEFT_HAND || 
                joint.getType() == JOINT_RIGHT_ELBOW || 
                joint.getType() == JOINT_RIGHT_HAND || 
                joint.getType() == JOINT_LEFT_KNEE || 
                joint.getType() == JOINT_LEFT_FOOT ||
                joint.getType() == JOINT_RIGHT_KNEE ||
                joint.getType() == JOINT_RIGHT_FOOT ) {
                Particle * p = new Particle();
                particles.push_back(p);
                p->joint_type = joint.getType();
            }
        }
    }
    
    //--------------------------------------------------------------
    void update() 
    {
        int i = 0;
        ofPoint point;
        vector<Particle*>::iterator it = particles.begin();
        while( it != particles.end() ){
            
            Particle * p = *it;
            ofxOpenNIJoint & joint = niuser->getJoint( p->joint_type );
            
                point = translateToAppSpace( joint.getWorldPosition() );
                p->x = point.x;
                p->y = point.y;
                p->z = point.z;
                
            it++;
        }
        
    }
    
    //--------------------------------------------------------------
    void draw() 
    {
        vector<Particle*>::iterator it = particles.begin();
        while( it != particles.end() ) {
            Particle * p = *it;
            ofSetColor( 255,255,255);
            ofCircle(p->x, p->y, p->z, 20 );
            it++;
        }
        
//        for(int j = 0; j < niuser->getNumJoints(); j++){
//            ofxOpenNIJoint & joint = niuser->getJoint((Joint)j);
//            
//            if (j==0) {
//                ofSetColor( 255,0,0);
//                ofLogNotice("TT") << "getWorldPosition:      " << joint.getWorldPosition();
//                ofLogNotice("TT") << "translateToAppSpace:      " << translateToAppSpace( joint.getWorldPosition() ); 
////                ofLogNotice("TT") << "getProjectivePosition:      " << joint.getProjectivePosition(); // * multiplyVec;
//            } else {
//                ofSetColor( 255,255,255);
//            }
//            
//            ofCircle( translateToAppSpace( joint.getWorldPosition() ) , 20 ); 
//            
//            //do something with the joint, or:
//            if(joint.isParent()){ // ie., it's like a limb...
//                // ...do something with the "limb"
//                ofSetColor( 255,255,0);
//                ofLine( translateToAppSpace(joint.getWorldPosition()), translateToAppSpace(joint.getParent().getWorldPosition()) );
//            }
//        }
    }
    
    //--------------------------------------------------------------
    ofVec3f translateToAppSpace( ofVec3f _point )
    {
        ofVec3f newPoint = _point * scale * trans;
        return newPoint; //newPoint;
    }
    
    //--------------------------------------------------------------
    XnUserID getID()
    {
        return id;
    }
    
};

#endif


/*
 
 FOR REF
 
 // start at root joint
 JOINT_TORSO = 0,
 JOINT_NECK,
 JOINT_HEAD,
 
 // left arm + shoulder
 JOINT_LEFT_SHOULDER,
 JOINT_LEFT_ELBOW,
 JOINT_LEFT_HAND,
 
 // right arm + shoulder
 JOINT_RIGHT_SHOULDER,
 JOINT_RIGHT_ELBOW,
 JOINT_RIGHT_HAND,
 
 // left leg
 JOINT_LEFT_HIP,
 JOINT_LEFT_KNEE,
 JOINT_LEFT_FOOT,
 
 // right leg
 JOINT_RIGHT_HIP,
 JOINT_RIGHT_KNEE,
 JOINT_RIGHT_FOOT,
 
 JOINT_COUNT,
 JOINT_UNKOWN
 */
