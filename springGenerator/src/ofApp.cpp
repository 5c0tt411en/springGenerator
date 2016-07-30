#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    lastImage.load("00_image/pattern03.png");
    currentImage.load("00_image/pattern04.png");
    ofBackground(0);

    gui.setup();
    
    gui.add(lkMaxLevel.set("lkMaxLevel", 3, 0, 8));
    gui.add(lkMaxFeatures.set("lkMaxFeatures", 200, 1, 1000));
    gui.add(lkQualityLevel.set("lkQualityLevel", 0.01, 0.001, .02));
    gui.add(lkMinDistance.set("lkMinDistance", 4, 1, 16));
    gui.add(lkWinSize.set("lkWinSize", 8, 4, 64));
    gui.add(usefb.set("Use Farneback", true));
    gui.add(fbPyrScale.set("fbPyrScale", .5, 0, .99));
    gui.add(fbLevels.set("fbLevels", 4, 1, 8));
    gui.add(fbIterations.set("fbIterations", 2, 1, 8));
    gui.add(fbPolyN.set("fbPolyN", 7, 5, 10));
    gui.add(fbPolySigma.set("fbPolySigma", 1.5, 1.1, 2));
    gui.add(fbUseGaussian.set("fbUseGaussian", false));
    gui.add(fbWinSize.set("winSize", 32, 4, 64));
    
    curFlow = &fb;
}

void ofApp::update(){
    if (calc) {
        if(usefb) {
            curFlow = &fb;
            fb.setPyramidScale(fbPyrScale);
            fb.setNumLevels(fbLevels);
            fb.setWindowSize(fbWinSize);
            fb.setNumIterations(fbIterations);
            fb.setPolyN(fbPolyN);
            fb.setPolySigma(fbPolySigma);
            fb.setUseGaussian(fbUseGaussian);
        } else {
            curFlow = &lk;
            lk.setMaxFeatures(lkMaxFeatures);
            lk.setQualityLevel(lkQualityLevel);
            lk.setMinDistance(lkMinDistance);
            lk.setWindowSize(lkWinSize);
            lk.setMaxLevel(lkMaxLevel);
        }
        
        // you can use Flow polymorphically
    curFlow->calcOpticalFlow(lastImage, currentImage);
    calc = false;
    }
}

void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()) + "fps");
    ofPushMatrix();
    ofTranslate(250, 10);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255);
    lastImage.draw(0, 0, 100, 100);
    currentImage.draw(100, 0, 100, 100);
    ofNoFill();
    ofSetColor(0, 122, 122, 255);
    ofDrawRectangle(-1, 111, 502, 502);
    ofFill();
    ofSetColor(255, 50);
    currentImage.draw(0, 110, 500, 500);
    ofSetColor(63, 210, 133, 50);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    curFlow->draw(0,110,500,500);
    ofPopMatrix();
    gui.draw();
}

void ofApp::keyPressed(int key) {
    if (key == 'c') calc = true;
    if (key == 'r') curFlow->resetFlow();
}