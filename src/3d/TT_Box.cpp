//
//  TT_Box.cpp
//  ghost
//
//  Created by Thomas Eberwein on 24/04/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "TT_Box.h"

void TT_Box::build()
{
    float h = 1;
    
    mesh.clear();
    
    ofVec3f vertices[] = {
        ofVec3f(+h,-h,+h), ofVec3f(+h,-h,-h), ofVec3f(+h,+h,-h), ofVec3f(+h,+h,+h),
        ofVec3f(+h,+h,+h), ofVec3f(+h,+h,-h), ofVec3f(-h,+h,-h), ofVec3f(-h,+h,+h),
        ofVec3f(+h,+h,+h), ofVec3f(-h,+h,+h), ofVec3f(-h,-h,+h), ofVec3f(+h,-h,+h),
        ofVec3f(-h,-h,+h), ofVec3f(-h,+h,+h), ofVec3f(-h,+h,-h), ofVec3f(-h,-h,-h),
        ofVec3f(-h,-h,+h), ofVec3f(-h,-h,-h), ofVec3f(+h,-h,-h), ofVec3f(+h,-h,+h),
        ofVec3f(-h,-h,-h), ofVec3f(-h,+h,-h), ofVec3f(+h,+h,-h), ofVec3f(+h,-h,-h)
    };
    mesh.addVertices(vertices,24);
    
    
    static ofFloatColor colors[] = {
        ofFloatColor( 1,0,0 ), ofFloatColor( 1,1,0 ), ofFloatColor( 0,1,0 ), ofFloatColor( 0,1,1 ),
        ofFloatColor( 0,0,1 ), ofFloatColor( 1,0,0 ), ofFloatColor( 1,1,0 ), ofFloatColor( 0,1,0 ), 
        ofFloatColor( 0,1,1 ), ofFloatColor( 1,0,0 ), ofFloatColor( 1,1,0 ), ofFloatColor( 0,1,0 ), 
        ofFloatColor( 0,1,1 ), ofFloatColor( 1,0,0 ), ofFloatColor( 1,1,0 ), ofFloatColor( 0,1,0 ), 
        ofFloatColor( 0,1,1 ), ofFloatColor( 1,0,0 ), ofFloatColor( 1,1,0 ), ofFloatColor( 0,1,0 ), 
        ofFloatColor( 0,1,1 ), ofFloatColor( 1,0,0 ), ofFloatColor( 1,1,0 ), ofFloatColor( 0,1,0 ) 
    };
    mesh.addColors( colors, 24 );
    
    static ofVec3f normals[] = {
        ofVec3f(+1,0,0), ofVec3f(+1,0,0), ofVec3f(+1,0,0), ofVec3f(+1,0,0),
        ofVec3f(0,+1,0), ofVec3f(0,+1,0), ofVec3f(0,+1,0), ofVec3f(0,+1,0),
        ofVec3f(0,0,+1), ofVec3f(0,0,+1), ofVec3f(0,0,+1), ofVec3f(0,0,+1),
        ofVec3f(-1,0,0), ofVec3f(-1,0,0), ofVec3f(-1,0,0), ofVec3f(-1,0,0),
        ofVec3f(0,-1,0), ofVec3f(0,-1,0), ofVec3f(0,-1,0), ofVec3f(0,-1,0),
        ofVec3f(0,0,-1), ofVec3f(0,0,-1), ofVec3f(0,0,-1), ofVec3f(0,0,-1)
    };
    mesh.addNormals(normals,24);
    
    static ofVec2f tex[] = {
        ofVec2f(1,0), ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1),
        ofVec2f(1,1), ofVec2f(1,0), ofVec2f(0,0), ofVec2f(0,1),
        ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0), ofVec2f(0,0),
        ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0),
        ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0),
        ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0)
    };
    mesh.addTexCoords(tex,24);
    
    static ofIndexType indices[] = {
        0,1,2, // right top left
        0,2,3, // right bottom right
        4,5,6, // bottom top right
        4,6,7, // bottom bottom left	
        8,9,10, // back bottom right
        8,10,11, // back top left
        12,13,14, // left bottom right
        12,14,15, // left top left
        16,17,18, // ... etc
        16,18,19,
        20,21,22,
        20,22,23
    };
    mesh.addIndices(indices,36);
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
}

void TT_Box::customDraw()
{
    drawBox();
}

void TT_Box::drawBox()
{
    ofEnableAlphaBlending();
    glEnable(GL_DEPTH_TEST);
    
    glPushMatrix();
    ofScale( width,height,depth );
    mesh.draw();
    glPopMatrix();
    
    glDisable(GL_DEPTH_TEST);
    ofDisableAlphaBlending();
}

void TT_Box::setColor( ofFloatColor _c )
{
    //    c = ofFloatColor( 0.1,0.1,0.1,0.1);
    c = _c;

    for (int i=0; i<24; i++) {
        mesh.setColor( i, _c );
    }
    
}

ofFloatColor TT_Box::getColor()
{
    return c;
}