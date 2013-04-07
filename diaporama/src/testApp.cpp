//# -*- mode: C++; coding: utf-8-*-
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){ 
  //// utils
  char tmpstr[2000];
  ofFile f = ofFile();
  ofDirectory dir = ofDirectory();
  /// indexes
	rota = 0;
  nimg = 0;
  nsnd = 9;
  image_duration = 0.1;
  image_timer = 0;
  silence_timer = 0;
  silence_trigger = false;
  //// LOAD IMAGES
  string rep_images = "intelligentsia/images/";
  dir.open(rep_images);
  dir.allowExt("jpg");
  dir.listDir();
  Nimgs = dir.numFiles();
  cout << Nimgs << endl;
  
  for (int i = 0; i < Nimgs; i++){
    sprintf(tmpstr, "%s_%dx%d.jpeg",dir.getPath(i).c_str(), ofGetScreenWidth(), ofGetScreenHeight());

    if (f.doesFileExist(tmpstr)) images[i].loadImage(tmpstr);
    else {
      images[i].loadImage(dir.getPath(i));
      pt = scaleSize(images[i].width, images[i].height, ofGetScreenWidth(), ofGetScreenHeight());
      images[i].resize(pt.x,pt.y);
      cout << "will save" << tmpstr << endl;
      images[i].saveImage(tmpstr);
    }
    cout << dir.getPath(i) << endl;
  };

  //// LOAD SOUND
  string rep_sounds = "intelligentsia/sons/";
  dir.open(rep_sounds);
  dir.allowExt("wav");
  dir.listDir();
  Nsnds = dir.numFiles();
  cout << Nsnds << endl;
  
  for (int i = 0; i < Nsnds; i++){
      sounds[i].loadSound(dir.getPath(i));
      cout << dir.getPath(i) << endl;
  };
  sounds[nsnd].play();


  // GRAPHICS
  ofHideCursor();
  ofSetFrameRate(120);
  ofSetVerticalSync(true);

}

//--------------------------------------------------------------
void testApp::update(){	
  ofBackground(0);
}

//--------------------------------------------------------------
void testApp::draw() {
  ofImage im;
  
  timer = ofGetElapsedTimef();
  im = images[nimg];
  im.rotate90(rota);  
  im.draw((ofGetScreenWidth()-im.width)/2,(ofGetScreenHeight()-im.height)/2);
  if ((timer-image_timer)>image_duration) {
    nimg++; if (nimg==Nimgs) nimg=0;
    image_timer = timer;
	rota+=0.1;
  }
  
  if (sounds[nsnd].getIsPlaying()==false) {
    if (silence_trigger==false) { 
      // sound just ended 
      silence_trigger = true; 
      silence_timer = timer;
      silence_duration = ofRandom(10,120);
      cout << silence_duration << endl;
    }
    else {
      if ((timer-silence_timer)>silence_duration) {
	nsnd++; if (nsnd==Nsnds) nsnd=0;
	sounds[nsnd].play();
	silence_trigger = false;
      }
    }
  }
}
//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
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

ofPoint testApp::scaleSize(float pw, float ph, float ww, float wh){
  float dw = ww/pw;
  float dh = wh/ph;
  float D = ww/wh;
  float d = pw/ph;
  float dt, nw, nh;
  if (D>d) {
    dt = dw*d/D;
    nw = pw*dh;
    nh = ph*dh;
  } else {
    dt = dh*D/d;
    nw = pw*dw;
    nh = ph*dw;
  }
  // rescale in right dimensions
  if (nw > ww) {nh = ww/nw*nh; nw = ww;}
  if (nh > wh) {nw = wh/nh*nw; nh = wh;}
  return ofPoint(int(nw), int(nh));
}

