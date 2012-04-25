#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    openni.setup();
}

//--------------------------------------------------------------
void testApp::update(){
    ofBackground(0, 0, 0);
    openni.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	openni.draw();
}

//--------------------------------------------------------------
void testApp::exit(){
    // this often does not work -> it's a known bug -> but calling it on a key press or 
    // anywhere that isnt std::aexit() works...press 'x' to shutdown cleanly...
    openni.exit();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
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

