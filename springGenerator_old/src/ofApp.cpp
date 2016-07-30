#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    fbo.allocate(500, 500, GL_RGBA);
    image.load("pattern07.png");
    
    imageCv.setFromPixels(image.getPixelsRef());
    imageCv.blurGaussian(blurGaussian);
    
    int grid = 500;
    int spacing = 1;
    
    for(int row = 0; row < grid; row++){
        for(int col = 0; col < grid; col++){
            ofVec3f v = ofVec3f(col*spacing, row*spacing, 0);
            mesh.addVertex(v);
            center.x += v.x;
            center.y += v.y;
            center.z += v.z;
            
            //bind mesh edges
            if(row < grid -1 && col < grid -1){
                int i = col + row*grid;
                mesh.addIndex(i);
                mesh.addIndex(i+1);
                mesh.addIndex(i+1+grid);
                
                mesh.addIndex(i);
                mesh.addIndex(i+1+grid);
                mesh.addIndex(i+grid);
            }
        }
    }
    
    center.x /= (float)(grid*grid);
    center.y /= (float)(grid*grid);
    center.z /= (float)(grid*grid);
    
    cam.setDistance(500);
    
    glEnable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
//    fbo.begin();
    ofSetColor(255);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofColor col1 = ofColor(0,0,0), col2 = ofColor(255,255,255);
    ofBackgroundGradient(col1, col2);
    ofPushMatrix();
    ofScale(0.5, 0.5);
    image.draw(0, 0);
    imageCv.draw(500, 0);
    ofPopMatrix();
//    fbo.end();
    
//    fbo.draw(0, 0);
    pixels = imageCv.getPixels();
    int w = pixels.getWidth();
    int h = pixels.getHeight();
    
    cam.lookAt(center);
    cam.begin();

    vector<ofVec3f>& verts = mesh.getVertices();

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    if (loop){
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
                ofColor color = pixels.getColor(x, y);
                verts[x + y*w].z += color.r / 5;
            }
        }
        loop = !loop;
    }
    ofSetColor(100);
    mesh.drawWireframe();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'l') loop = !loop;
    
    if (key == ' ') mesh.save(ofToString(ofGetMonth()) +
                              ofToString(ofGetDay()) +
                              ofToString(ofGetHours()) +
                              ofToString(ofGetMinutes()) +
                              ofToString(ofGetSeconds()) + ".ply");
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
