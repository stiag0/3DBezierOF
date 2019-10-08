#include "ofApp.h"
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Bezier 3D");
	gui.setup();
	gui.add(accuracy.setup("t", 5555, 1, 15000));
	gui.add(clearBtn.setup("erase"));
	gui.add(drawBtn.setup("draw"));
	ofSetFrameRate(60);
	drawPressed = false;
	anchor_image.load("targetmin.png");
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	if (clearBtn) {
		drawPressed = false;
		controlPts.clear();
	}

	if (drawBtn)
		drawPressed = true;

	if (drawPressed) {
		std::vector<ofVec3f> end = bezier_curve(controlPts, accuracy);
		if (end.size() > 1) {
			ofSetColor(ofColor::black);
			for (unsigned int i = 0; i < controlPts.size() - 1; ++i) {
				ofDrawLine(controlPts[i].x, controlPts[i].y, controlPts[i + 1].x, controlPts[i + 1].y);
				anchor_image.draw(controlPts[i].x, controlPts[i].y);
			}
			ofSetColor(ofColor::blue);
			for (unsigned int i = 0; i < end.size(); ++i) {
				ofCircle(end[i].x, end[i].y,end[i].z, 1);
			}
		}
	}
	gui.draw();
}

//-----------M----------------------------------

float ofApp::interpolate(float pos1, float pos2,float pos3,float accuracy) {
	return (1 - accuracy) * pos1 + accuracy * pos2 + accuracy * pos3;
}

vector<ofVec3f> ofApp::bezier_curve(vector<ofVec3f>& anchor, float accuracy) {
	if (anchor.size() <= 2)
		return anchor;

	vector<ofVec3f> end;

	for (float i = 0.f; i < accuracy; ++i) {
		float t = i / accuracy;

		vector<ofVec3f> temp(anchor);

		while (temp.size() > 2) {
			vector<ofVec3f> temp2;
			for (unsigned int j = 1; j < temp.size(); ++j)
				temp2.push_back(ofVec3f(interpolate(temp[j - 2].x, temp[j-1].x,temp[j].x, t),
					interpolate(temp[j - 2].y, temp[j-1].y,temp[j].y, t),
					interpolate(temp[j - 2].z, temp[j - 1].z, temp[j].z, t)));
			//interpolation only on 2 points?
			temp.swap(temp2);
		}
		end.push_back(temp.front());
	}
	return end;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	controlPts.push_back(ofVec3f(x, y, 1));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
