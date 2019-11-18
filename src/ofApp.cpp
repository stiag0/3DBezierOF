#include "ofApp.h"
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	bLearnBackground = false;
	
	//webCam.setup(400, 400);
	webCam.setVerbose(true);
	webCam.initGrabber(320, 240);
	colorImg.allocate(320, 240);
	grayImage.allocate(320, 240);
	grayBg.allocate(320, 240);
	grayDiff.allocate(320, 240);
	
	// directional light
	directionalLight.setDirectional();
	directionalLight.setSpecularColor(ofColor(255));
	directionalLight.setDiffuseColor(ofColor(255));
	directionalLight.setAmbientColor(ofColor(100));

	ofEnableDepthTest();
	ofSetVerticalSync(true);
	//ofBackground(70, 70, 70);
	cam.setDistance(10);

	ofSetWindowTitle("Bezier3D");
	gui.setup();
	gui.add(accuracy.setup("t", 5555, 1, 15000));
	gui.add(clearBtn.setup("erase"));
	gui.add(drawBtn.setup("draw"));

	ofSetFrameRate(60);
	drawPressed = true;
	//anchor_image.load("targetmin.png");
}

//--------------------------------------------------------------
void ofApp::update() {
	webCam.update();
	if (webCam.isFrameNew()) {
		colorImg.setFromPixels(webCam.getPixels());
		grayImage = colorImg; // convert our color image to a grayscale image
		if (bLearnBackground == true) {
			grayBg = grayImage; // update the background image
			bLearnBackground = false;
		}
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(30);
		contourFinder.findContours(grayDiff, 5, (340 * 240) / 4, 4, false, true);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetHexColor(0xffffff);
	colorImg.draw(0, 0, 320, 240);
	grayDiff.draw(0, 240, 320, 240);
	ofDrawRectangle(320, 0, 320, 240);
	contourFinder.draw(320, 0, 320, 240);
	ofColor c(255, 255, 255);
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		ofRectangle r = contourFinder.blobs.at(i).boundingRect;
		r.x += 320; r.y += 240;
		c.setHsb(i * 64, 255, 255);
		ofSetColor(c);
		ofDrawRectangle(r);
	}
	webCam.draw(1600,0);
	cam.begin();
	gui.draw();
	
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
				//anchor_image.draw(controlPts[i].x, controlPts[i].y);
				ofDrawSphere(controlPts[i].x, controlPts[i].y,10);
			}
			ofSetColor(ofColor::blue);
			for (unsigned int i = 0; i < end.size(); ++i) {
				ofCircle(end[i].x, end[i].y, 1);
			}
		}
	}
	
	cam.end();
}

//-----------M----------------------------------

float ofApp::interpolate(float pos1, float pos2, float accuracy) {
	return (1 - accuracy) * pos1 + accuracy * pos2;
}

vector<ofVec3f> ofApp::bezier_curve(vector<ofVec3f>& anchor, float accuracy) {
	if (anchor.size() <= 2)
		return anchor;

	vector<ofVec3f> end;

	for (float i = 0.f; i < accuracy; ++i) {
		float t = i / accuracy;

		vector<ofVec3f> temp(anchor);

		while (temp.size() > 1) {
			vector<ofVec3f> temp2;
			for (unsigned int j = 1; j < temp.size(); ++j)
				temp2.push_back(ofVec3f(interpolate(temp[j - 1].x, temp[j].x, t),
					interpolate(temp[j - 1].y, temp[j].y, t),
					interpolate(temp[j-1].z,temp[j].z,t))
					);
					
			temp.swap(temp2);
		}
		end.push_back(temp.front());
             	}
	return end;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	bLearnBackground = true;
	if (key == ' ') {
		pintarS = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == ' ') {
		pintarS = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (pintarS) {
		controlPts.push_back(ofVec3f(x, y, 1.0));
		cout << x << y << " ";
	}

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
