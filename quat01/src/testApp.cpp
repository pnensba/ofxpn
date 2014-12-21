#include "testApp.h"

ofPoint px = ofPoint(1,0,0);
ofPoint py = ofPoint(0,1,0);
ofPoint pz = ofPoint(0,0,1);
float scale = 0.1;

//--------------------------------------------------------------
void testApp::setup(){
    
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableSmoothing();
    ofSetupScreenOrtho(ofGetWindowWidth(), ofGetWindowHeight(), OF_ORIENTATION_DEFAULT, true, -10, 10);
    ofTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5);
    ofScale(ofGetWindowWidth()*scale,-ofGetWindowHeight()*scale,-scale);
    /*
     ofRotateY(-15);
     ofRotateX(15);
     ofRotateZ(15);
     */
    //ofDrawGrid(10, 100, false, false, false, true);
    //ofDrawAxis(1);
    //ofDrawRotationAxes(0.2);
    //ofDrawGridPlane(10);
    
    ofVec3f axis;
    float angle;
    qrot.getRotate(angle, axis);
	
	//apply the quaternion's rotation to the viewport and draw the sphere
	ofRotate(angle, axis.x, axis.y, axis.z);
    
    ofSetColor(255,0,0);
    ofLine(ofPoint(0,0,0), px);
    ofDrawBitmapString("x", px+0.1);
    ofSetColor(0,255,0);
    ofLine(ofPoint(0,0,0),py);
    ofDrawBitmapString("y", py-0.1);
    ofSetColor(0,0,255);
    ofLine(ofPoint(0,0,0),pz);
    ofDrawBitmapString("z", pz+0.1);
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
    if (button==0){
        ofQuaternion qy((x-ofGetPreviousMouseX()), ofVec3f(0,1,0));
        ofQuaternion qx((y-ofGetPreviousMouseY()), ofVec3f(1,0,0));
        qrot *= qx*qy;
    }
    
    if (button==2){
        ofQuaternion qz((x-ofGetPreviousMouseX()), ofVec3f(0,0,1));
        qrot *= qz;
        
        scale += (float)(ofGetPreviousMouseY()-y)/(ofGetWindowHeight()/2);
        if (scale<0) scale = 0.0001;
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if (button==1) qrot *= qrot.inverse();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}