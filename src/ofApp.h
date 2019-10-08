#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream> 
#include "ofxGui.h"
using namespace std;

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	float interpolate(float x, float y,float z , float accuracy);
	vector<ofVec3f> bezier_curve(vector<ofVec3f>& anchor, float accuracy);
	ofxIntSlider accuracy;
	ofxButton clearBtn;
	ofxButton drawBtn;
	ofxPanel gui;
	std::vector<ofVec3f> controlPts;
	bool drawPressed;
	ofImage anchor_image;

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};