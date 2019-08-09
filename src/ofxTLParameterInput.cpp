//
//  ofxTLParameterInput.cpp
//  ByensPuls
//
//  Created by Jonas Fehr on 24/07/2019.
//

#include "ofxTLParameterInput.h"
#include "ofxTimeline.h"

ofxTLParameterFloat::ofxTLParameterFloat(ofParameter<float> * param){
    this->parameter = param;
    ofAddListener(ofEvents().update, this, &ofxTLParameterFloat::update);
}

ofxTLParameterFloat::~ofxTLParameterFloat(){
    ofRemoveListener(ofEvents().update, this, &ofxTLParameterFloat::update);
}

void ofxTLParameterFloat::update(ofEventArgs & args){
    ofxTimeline* tl = getTimeline();
    if(tl->getIsPlaying()) *parameter = getValue();
}





ofxTLParameterInt::ofxTLParameterInt(ofParameter<int> * param){
    this->parameter = param;
    ofAddListener(ofEvents().update, this, &ofxTLParameterInt::update);
}

ofxTLParameterInt::~ofxTLParameterInt(){
    ofRemoveListener(ofEvents().update, this, &ofxTLParameterInt::update);
}

void ofxTLParameterInt::update(ofEventArgs & args){
    if(timeline->getIsPlaying()) *parameter = (int)getValue();
}




ofxTLParameterBool::ofxTLParameterBool(ofParameter<bool> * param){
    this->parameter = param;
    ofAddListener(ofEvents().update, this, &ofxTLParameterBool::update);
}

ofxTLParameterBool::~ofxTLParameterBool(){
    ofRemoveListener(ofEvents().update, this, &ofxTLParameterBool::update);
}

void ofxTLParameterBool::update(ofEventArgs & args){
    if(timeline->getIsPlaying()) *parameter = isOn();
}
