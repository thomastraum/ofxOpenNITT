//
//  TT_Box.h
//  ghost
//
//  Created by Thomas Eberwein on 24/04/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"

class TT_Box : public ofNode {
    
    ofFloatColor    c;
    
public:
    
    TT_Box() {
        width   = 1;
        height  = 1;
        depth   = 1;
        c       = ofFloatColor( 0.7,0.7,0.7,1);
    }
    
    ofMesh          mesh;
    
    int             width;
    int             height;
    int             depth;
    
    void            build();
    virtual void    customDraw();
    void            drawBox();
    
    void            setColor( ofFloatColor color );
    ofFloatColor    getColor();
    
};