//
//  ofxOpenNITT_User.h
//  openNiSample007
//
//  Created by Thomas Eberwein on 25/04/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofxOpenNI.h"

class ofxOpenNITT_User : public ofxOpenNIUser {
    
    
    
public:
    
    void drawSkeletonInsideWorld()
    {
        ofPushStyle();
        
        for(int i = 0; i < joints.size(); i++) {
            ofPoint p = joints[i].getWorldPosition();
            ofBox(p, 50);
        }
        
        ofPopStyle();
    }
    
};