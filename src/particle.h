//
//  particle.h
//  basic 3d scene 1
//
//  Created by Thomas Eberwein on 14/06/2012.
//  Copyright 2012 Thomas Traum Ltd. All rights reserved.
//

#ifndef basic_3d_scene_1_particle_h
#define basic_3d_scene_1_particle_h

#pragma once
#include "ofMain.h"
#include "ofxOpenNITypes.h"

class Particle {
    

public:
    
    
    int x;
    int y;
    int z;
    
    Joint joint_type;
    
    Particle(){};
    
    
};


#endif
