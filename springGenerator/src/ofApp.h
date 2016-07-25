#pragma once

#include "ofMain.h"
#define WIDTH 30
#define HEIGHT 30
#define NUM WIDTH * HEIGHT

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofVboMesh mesh;
    ofVec3f point[NUM];
    ofLight light;
    ofEasyCam cam;
    const float scale = 400;
    float xNoise, yNoise, zNoise;
    
    ofVec3f center;
    ofShader sineShader, noiseShader;
    int waveDirection, waveFrequency;
    float noiseAmount;
    
    ofFbo fbo;
    ofImage image;
    ofVec2f grid, space;
    ofPixels pixels;
    
    bool loop;
};
