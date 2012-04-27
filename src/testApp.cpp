#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    openni.setup();
    box.build();
    box.width   = ofGetWidth();
    box.height  = ofGetHeight();
    box.depth   = ofGetWidth()*2;
}

//--------------------------------------------------------------
void testApp::update(){
    ofBackground(0, 0, 0);
    openni.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
    glEnable(GL_DEPTH_TEST);
    
    
//    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//    cam.setDistance( 4000 );
    cam.begin();
    ofSetColor(255, 255, 255, 30);
    box.draw();
    
    openni.draw3dUsers();
//    openni.drawCenter();
    
//    cout << g_worldToProjective( ofPoint(1,1,1) ) << endl;
//    projectiveToWorld
    
    cam.end();
    
    glDisable(GL_DEPTH_TEST);
    
    ofScale(.5,.5);
	openni.draw();
    
//    
//    openni.drawCenter();
    
    
    
}

//--------------------------------------------------------------
void testApp::exit(){
    // this often does not work -> it's a known bug -> but calling it on a key press or 
    // anywhere that isnt std::aexit() works...press 'x' to shutdown cleanly...
    openni.exit();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key) {
            
        case 'f':
            ofToggleFullscreen();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

