#ifndef _TEST_APP
#define _TEST_APP

#pragma once
#include "ofMain.h"
#include "TT_Player.h"
#include "TT_UserManager.h"

class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void windowResized(int w, int h);
    
    ofEasyCam       cam;
    
    TT_Player       player;
    TT_UserManager  user_manager;
};

#endif
