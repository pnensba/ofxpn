//# -*- mode: C++; coding: utf-8-*-
#pragma once

#include "ofMain.h"
#include "vrximg.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxJSONElement.h"


class testApp : public ofBaseApp{

public:
  ~testApp();
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void exit();

  // variables
  char tmpstr[255];

  int const static NN = 336;

  ofImage rouleau[NN];
  unsigned char * pix;
  int Ws[NN];
  int Hpix;


  int W,H, N, in, n, T, D, prevmx, y;
  int color;
  float d, x;


};


