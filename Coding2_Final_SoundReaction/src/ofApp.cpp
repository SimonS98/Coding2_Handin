#include "ofApp.h"

const int B = 256;
float spectrum[B];
float radius = 1000;
float velocity = 0.5;
int bandRadius = 2;
int bandVelocity = 100;

const int cloudNum = 1000;

float offx[cloudNum], offy[cloudNum];
ofVec3f position[cloudNum];
float bg_transparent = 255;
float time0 = 0;
float dist = 45;

//--------------------------------------------------------------
void ofApp::setup(){
    music1.loadSound("眠,Lopu$ - Blame You.mp3", true );
    music1.setLoop(false);
    music2.loadSound("马友友; Stuart Duncan; Edgar Meyer; Chris Thile; Yo-Yo Ma, Stuart Duncan, Edgar Meyer & Chris Thile - Quarter Chicken Dark.mp3", true );
    music2.setLoop(false);

    for (int i=0; i<B; i++) {
        spectrum[i] = 0.0f;
    }
    
    for (int r = 0; r < cloudNum; r++){
        offx[r] = ofRandom(0,1000);
        offy[r] = ofRandom(0,1000);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
    float *value = ofSoundGetSpectrum(B);
    
    for ( int i=0; i<B; i++ ) {
        spectrum[i] *= 0.96;
        spectrum[i] = max( spectrum[i], value[i] );
    }
    

    
    float time = ofGetElapsedTimef();
    float dt = time - time0;
    dt = ofClamp( dt, 0.0, 0.1 );
    time0 = time;
    
    radius = ofMap(spectrum[bandRadius], 1, 3, 400, 1600, true);
    velocity = ofMap(spectrum[bandVelocity], 0, 0.1, 0.02, 0.9);

    for (int s=0; s<cloudNum; s++) {
        offx[s] += velocity * dt;
        offy[s] += velocity * dt;
        position[s].x = ofSignedNoise( offx[s] ) * radius;
        position[s].y = ofSignedNoise( offy[s] ) * radius;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    float time = ofGetElapsedTimef();
    float rtime = fmod(time,10);
    float gtime = fmod(time,14);
    float btime = fmod(time,6);

    float Rtime = ofMap(rtime, 1, 9, 50, 180);
    float Gtime = ofMap(gtime, 1, 13, 50, 180);
    float Btime = ofMap(btime, 1, 5, 50, 180);
    
    
    //ofBackground( 255, 255, 255 );
    ofBackground( 0, 0, 0 );
    //ofBackground( 255-rtime, 255-gtime, 255-btime );


    ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2 );
    

    for (int i=0; i<cloudNum; i++) {
        ofSetColor( 230-position[i].x-Rtime, 200-position[i].y-Gtime, 255-Btime, fabs(255 - bg_transparent) );

        //ofSetColor(255,255,255, fabs(80 - bg_transparent));
        ofFill();
        ofCircle( position[i], 2 );
    }


    for (int j=0; j<cloudNum; j++) {
        for (int k=j+1; k<cloudNum; k++) {
            if ( ofDist( position[j].x, position[j].y, position[k].x, position[k].y )
                < dist ) {
                //ofSetColor( 160, 160, 160, fabs(130 - bg_transparent) );
                ofSetColor( 160-position[j].x, 200-position[j].y, 210, fabs(200 - bg_transparent) );

                    ofLine( position[j], position[k] );
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            music1.play();
            break;
        case '2':
            music2.play();
            break;
        case 'p':
            music1.setPaused(true);
            music2.setPaused(true);

            break;
        case 'o':
            music1.setPaused(false);
            music2.setPaused(false);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
