//# -*- mode: C++; coding: utf-8-*-
#include "testApp.h"

testApp::~testApp(){
    
};

void testApp::setup(){
    
    W = ofGetScreenWidth();
    H = ofGetScreenHeight();
    Hpix = 4727;
    ofSetVerticalSync(true);
    ofHideCursor();    
    /////////////////////////// SETUP MONTAGE
    ofDirectory dir("");
    dir.allowExt("jpg");
    dir.listDir();
    dir.sort();
    N = dir.numFiles(); // Number of Images
    for (int i = 0; i < N; i++){
        rouleau[i].setUseTexture(false);
        rouleau[i].loadImage(dir.getPath(i));
        rouleau[i].resize(rouleau[i].width*2.0f/3.0f,Hpix*2.0f/3.0f);
        Ws[i] = rouleau[i].width;
        cout<<i<<" "<<rouleau[i].isUsingTexture()<<"\n";
    };
    Hpix *= 2.0f/3.0f;
    cout << Hpix;
    rouleau[0].setUseTexture(true);
    rouleau[0].reloadTexture();
    rouleau[1].setUseTexture(true);
    rouleau[1].reloadTexture();
    rouleau[2].setUseTexture(true);
    rouleau[2].reloadTexture();
    /////////////////////////// SETUP SCROLLING
    
    n = 0; // number of
    D = 0; // decalage cumulatif
    d = 1; // decalage
    
    y = Hpix /2;
}



// || current image | next image | hidden image||
//          n              n+1         n+2

void testApp::update(){
    /////////////////////////// COMPUTE MONTAGE
    
    D-=d; // scrolling out (to the left)
    
    if (D<-Ws[n]) { // current image disappears => load hidden image
        D = 0;
        // release current image
        rouleau[n].setUseTexture(false);
        rouleau[n].getTextureReference().clear();
        rouleau[n].update();
        
        if (n+3 < N) { // "normal process"
            // load hidden image
            rouleau[n+3].setUseTexture(true);
            rouleau[n+3].reloadTexture();
            n += 1;
        }
        else if (n == N-3) { // three images left
            // load hidden image
            rouleau[0].setUseTexture(true);
            rouleau[0].reloadTexture();
            n += 1;
        }
        else if (n == N-2) { // two images left
            // load hidden image
            rouleau[1].setUseTexture(true);
            rouleau[1].reloadTexture();
            n += 1;
        }
        else if (n == N-1) { // one image left
            // load hidden image
            rouleau[2].setUseTexture(true);
            rouleau[2].reloadTexture();
            n = 0;
        }
         
        cout << n << endl;
    }
    T = D;
    
}

void testApp::draw(){
    in = n;
    ofSetColor(255);
    while (T<=W) {
        rouleau[in].draw(T,-y);
        T += Ws[in];
        in += 1;
        if (in>(N-1)) {
            in=0;
        };
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == ' ') d=0;
    if(key == 'w') d = -1;
    if(key == 'x') d = 1;
}
void testApp::keyReleased(int key){}


//--------------------------------------------------------------
void testApp::mousePressed(int mx, int my, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int mx, int my, int button){
    my = my;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int mx, int my, int button){
    y += ofGetPreviousMouseY()-my;
    if (y<0) y = 0;
    if (y > Hpix-H) y = Hpix-H;
}

//--------------------------------------------------------------
void testApp::mouseMoved(int mx, int my ){
}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}

void testApp::exit(){
    for (int i = 0; i < N; i++){
        rouleau[i].clear();
    };
}

