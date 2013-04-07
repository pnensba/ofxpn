//# -*- mode: C++; coding: utf-8-*-
#include "vrximg.h"
#include "ofMain.h"

vrxImg::vrxImg() {};
vrxImg::~vrxImg() {};

vrxImg::vrxImg(string ppath, int xx, int yy)
{
  // xx and yy : North-East position
  path = ppath; 
  x = xx; y = yy;
  ang = 0;
  scale = 1;

  img.loadImage(path);
  w = img.width;
  h = img.height;
};

void vrxImg::draw(int alpha)
{
  ofPushMatrix();
  ofSetColor(255,255,255,alpha);
  ofTranslate(x,y);
  ofRotateZ(ang);
  img.draw(0,0, w,h);
  ofPushStyle();
  ofNoFill();
  ofSetLineWidth(2);
  ofSetColor(200,200,200,alpha/3.);
  ofRect(0,0, w,h);
  ofPopStyle();
  ofPopMatrix();
};


