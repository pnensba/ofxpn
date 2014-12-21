//# -*- mode: C++; coding: utf-8-*-
#pragma once
#include "ofMain.h"

class vrxImg {
public:
  ~vrxImg();
  vrxImg();
  vrxImg(string path, int x, int y);
  
  ofImage img;
  string path;
  int w, h;
  float x,y,ang,scale;

  void draw(int alpha);
};
