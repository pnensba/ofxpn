//# -*- mode: C++; coding: utf-8-*-
#pragma once

#include "ofMain.h"


class testApp : public ofBaseApp{
	
 public:

  void setup();
  void update();
  void draw();
	
  void keyPressed  (int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  
  ofImage images[100000];
  ofSoundPlayer sounds[100000];

  int Nimgs,Nsnds,nimg,nsnd, rota;

  float timer, image_timer, image_duration, silence_timer, silence_duration;
  bool silence_trigger;
  ofPoint pt;
  ofPoint scaleSize(float pw, float ph, float ww, float wh);
  
};
