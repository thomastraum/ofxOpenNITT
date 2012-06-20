//
//  TT_BoxGui.h
//  particles 3d 5
//
//  Created by Thomas Eberwein on 19/02/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once 
#include "TT_Box.h"
#include "ofxSimpleGuiToo.h"

class TT_BoxGui : public TT_Box {
    
    float   gui_smoothing;
    ofFloatColor color;
    ofFloatColor prev_color;
    
public:
    
    TT_BoxGui() {
        gui_smoothing = .8;
        color = ofFloatColor(1,1,1,1);
        prev_color = color;
    }
    
    void customDraw()
    {
        TT_Box:drawBox();
        
        if ( color != prev_color ) {
            prev_color = color;
            setColor( color );
        }
    }
    
    void addSettings( ofxSimpleGuiToo & _gui )
    {
        _gui.addTitle( "Box Colors" );
        _gui.addSlider( "Box Red", color.r, 0,1).setSmoothing( gui_smoothing );
        _gui.addSlider( "Box Green", color.g, 0,1).setSmoothing( gui_smoothing );
        _gui.addSlider( "Box Blue", color.b, 0,1).setSmoothing( gui_smoothing );
        _gui.addSlider( "Box Alpha", color.a, 0,1).setSmoothing( gui_smoothing );
    }
    
};