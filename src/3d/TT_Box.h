//
//  TT_Box.h
//  ghost
//
//  Created by Thomas Eberwein on 24/04/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"

#define WIDTH 1
#define HEIGHT 1
#define DEPTH 1

class TT_Box : public ofNode {
    
    ofFloatColor    c;
    
public:
    
    TT_Box() {
        width   = WIDTH;
        height  = HEIGHT;
        depth   = DEPTH;
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