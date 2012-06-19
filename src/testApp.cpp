#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
    player.play( "test.oni" );
}

//--------------------------------------------------------------
void testApp::update(){
    
    player.update();
    user_manager.update();
}

//--------------------------------------------------------------
void testApp::draw(){

    player.draw();
    
    cam.begin();
    ofSetColor( 255,0,255 );
    ofBox( 0,0,0, 50 );
    user_manager.draw();
    cam.end();
}

//--------------------------------------------------------------
void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}