#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() 
{
    player.play( "test.oni" );
    for ( int i=0; i<100; i++ ) {
        Particle * p = new Particle();
        p->x = ofRandom( -ofGetWidth(), ofGetWidth() );
        p->y = ofRandom( -ofGetHeight(), ofGetHeight() );
        p->z = ofRandom( -ofGetWidth(), ofGetWidth() );
        particles.push_back( p );
    }
    
    box.build();
    
    
    width = ofGetWidth();
	height = ofGetHeight();
    
    box.width   = 3000;
    box.height  = 1500;
    box.depth   = 4000;
    
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update(){
    
    player.update();
    user_manager.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    cam.setDistance(width);
    cam.begin();
    glEnable(GL_DEPTH_TEST);
    
    box.draw();
    
    ofPushMatrix();
//    glMatrixMode(GL_MODELVIEW);
//    float flipped[] = {
//        1, 0, 0, 0,
//        0, 1, 0, 0, 
//        0, 0, -1, 0,
//        0, 0, 0, 1
//    };
//    glMultMatrixf( flipped );
    
    user_manager.draw();
    
    ofPopMatrix();
    glMatrixMode(GL_PROJECTION);
    
    drawParticles();
    
    glDisable(GL_DEPTH_TEST);
    cam.end();
    
    
    player.draw();
    
    ofSetColor( 0x000000 );
	ofDrawBitmapString
	(
	 "fps :: " + ofToString(ofGetFrameRate()),
	 20,
	 20
	 );
}

void testApp::drawParticles()
{
    vector<Particle*>::iterator it = particles.begin();
    while ( it != particles.end() ) {
        Particle * p = *it;
        ofSetColor(255, 255, 0);
        ofCircle( p->x, p->y, p->z, 10);
        it++;
    }
}

//--------------------------------------------------------------
void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
            
        default:
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}