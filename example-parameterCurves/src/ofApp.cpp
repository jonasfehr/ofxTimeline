/**
 * ofxTimeline -- AudioWaveform Example
 * openFrameworks graphical timeline addon
 *
 * Copyright (c) 2011-2012 James George http://www.jamesgeorge.org
 * Development Supported by YCAM InterLab http://interlab.ycam.jp/en/ +
 *
 * http://github.com/YCAMinterLab
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
	
	glEnable(GL_DEPTH_TEST);
	ofEnableLighting();
	
	light.setPosition(ofGetWidth()*.5, ofGetHeight()*.25, 0);
	light.enable();		
    
	timeline.setup();
    timeline.setFrameRate(30);
	timeline.setDurationInFrames(90);
	timeline.setLoopType(OF_LOOP_NORMAL);
    
	//each call to "add keyframes" add's another track to the timeline
	timeline.addCurves("Rotate X", ofRange(0, 360));
	timeline.addCurves("Rotate Y", ofRange(0, 360));
    
	//Flags are little markers that you can attach text to
    //They are only useful when listening to bangFired() events
    //so that you know when one has passed
	timeline.addColors("Colors");

    //setting framebased to true results in the timeline never skipping frames
    //and also speeding up with the 
    //try setting this to true and see the difference
    timeline.setFrameBased(false);
    
    timelineViewPort.set(100,100, 800, 500);
    timeline.setOffset(timelineViewPort.getTopLeft());
    timeline.setWidth(timelineViewPort.getWidth());
    //timeline.setHeight(timelineViewPort.getHeight());
	
    floatParam.set("test", 0.5, 0., 3.);
    timeline.addFloatParameter(floatParam);

    panel.setup();
    panel.add(floatParam);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(.15*255);
	ofPushMatrix();
	
	ofPushStyle();
    //set the color to whatever the last color we encountered was
	ofSetColor(timeline.getColor("Colors"));
	
    //translate to the center of the screen
	ofTranslate(ofGetWidth()*.5, ofGetHeight()*.66, 40);
    
    //Read the values out of the timeline and use them to change the viewport rotation
    ofRotateDeg(timeline.getValue("Rotate X"), 1, 0, 0);
    ofRotateDeg(timeline.getValue("Rotate Y"), 0, 1, 0);
	
    ofDrawBox(0,0,0, 200);
	
	ofPopMatrix();

	ofPopStyle();
	
	timeline.draw();
    
    panel.draw();
    
    cout << floatParam << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
	
