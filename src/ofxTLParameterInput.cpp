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
}

ofxTLParameterFloat::~ofxTLParameterFloat(){
    if(isEnabled()) disable();
}

void ofxTLParameterFloat::enable(){
    ofxTLTrack::enable();
//    parameter->newListener(this, &ofxTLParameterFloat::addKey);
    ofAddListener(ofEvents().update, this, &ofxTLParameterFloat::update);
    ofAddListener(events().playheadScrubbed, this, &ofxTLParameterFloat::updateScrub);
}

void ofxTLParameterFloat::disable(){
    ofxTLTrack::enable();
//    parameter->removeListener(this, &ofxTLParameterFloat::addKey);
    ofRemoveListener(ofEvents().update, this, &ofxTLParameterFloat::update);
    ofRemoveListener(events().playheadScrubbed, this, &ofxTLParameterFloat::updateScrub);
}

void ofxTLParameterFloat::addKey(float & v){
    if(!getTimeline()->getIsPlaying()) addKeyframe(v);
}

void ofxTLParameterFloat::update(ofEventArgs & args){
    ofxTimeline* tl = getTimeline();
    if(tl->getIsPlaying()) *parameter = getValue();
}

void ofxTLParameterFloat::updateScrub(ofxTLPlaybackEventArgs & args){
    if(parameter != NULL) parameter->setWithoutEventNotifications(getValue());
}




ofxTLParameterInt::ofxTLParameterInt(ofParameter<int> * param){
    this->parameter = param;
}

ofxTLParameterInt::~ofxTLParameterInt(){
    if(isEnabled()) disable();
}

void ofxTLParameterInt::enable(){
    ofxTLTrack::enable();
//    parameter->addListener(this, &ofxTLParameterInt::addKey);
    ofAddListener(ofEvents().update, this, &ofxTLParameterInt::update);
    ofAddListener(events().playheadScrubbed, this, &ofxTLParameterInt::updateScrub);
}

void ofxTLParameterInt::disable(){
    ofxTLTrack::enable();
//    parameter->removeListener(this, &ofxTLParameterInt::addKey);
    ofRemoveListener(ofEvents().update, this, &ofxTLParameterInt::update);
    ofRemoveListener(events().playheadScrubbed, this, &ofxTLParameterInt::updateScrub);
}

void ofxTLParameterInt::addKey(int & v){
    if(!getTimeline()->getIsPlaying()) addKeyframe(v);
}

void ofxTLParameterInt::update(ofEventArgs & args){
    if(timeline->getIsPlaying()) *parameter = (int)getValue();
}

void ofxTLParameterInt::updateScrub(ofxTLPlaybackEventArgs & args){
    if(parameter != NULL) parameter->setWithoutEventNotifications((int)getValue());
}




ofxTLParameterBool::ofxTLParameterBool(ofParameter<bool> * param){
    this->parameter = param;
}

ofxTLParameterBool::~ofxTLParameterBool(){
    if(isEnabled()) disable();
}

void ofxTLParameterBool::enable(){
    ofxTLTrack::enable();
//    parameter->addListener(this, &ofxTLParameterBool::addKey);
    ofAddListener(ofEvents().update, this, &ofxTLParameterBool::update);
    ofAddListener(events().playheadScrubbed, this, &ofxTLParameterBool::updateScrub);
}

void ofxTLParameterBool::disable(){
    ofxTLTrack::enable();
//    parameter->removeListener(this, &ofxTLParameterBool::addKey);
    ofRemoveListener(ofEvents().update, this, &ofxTLParameterBool::update);
    ofRemoveListener(events().playheadScrubbed, this, &ofxTLParameterBool::updateScrub);
}

void ofxTLParameterBool::addKey(bool & v){
    if(!getTimeline()->getIsPlaying()){
        if(parameter->get()){
            ofxTLSwitch* switchKey = new ofxTLSwitch();
            switchKey->textField.setFont(timeline->getFont());
            
            //in the case of a click, start at the mouse positiion
            //if this is being restored from XML, the next call to restore will override this with what is in the XML
            switchKey->timeRange.min = currentTrackTime();
            switchKey->timeRange.max = currentTrackTime()+5000;
            switchKey->startSelected = false;
            switchKey->endSelected   = false; //true so you can drag the range to start with
            
            //a bit of a hack, but if
            placingSwitch = NULL;
        
//            getKeyframes().push_back(switchKey);
        }
    }
}

void ofxTLParameterBool::update(ofEventArgs & args){
    if(timeline->getIsPlaying()) *parameter = isOn();
}

void ofxTLParameterBool::updateScrub(ofxTLPlaybackEventArgs & args){
    if(parameter != NULL) parameter->setWithoutEventNotifications(isOn());
}




ofxTLParameterString::ofxTLParameterString(ofParameter<string> * param){
    this->parameter = param;
}

ofxTLParameterString::~ofxTLParameterString(){
    if(isEnabled()) disable();
}

void ofxTLParameterString::enable(){
    ofxTLTrack::enable();
//    parameter->addListener(this, &ofxTLParameterBool::addKey);
    ofAddListener(ofEvents().update, this, &ofxTLParameterString::update);
    ofAddListener(events().playheadScrubbed, this, &ofxTLParameterString::updateScrub);
//    ofAddListener(events().bangFired, this, &ofxTLParameterString::updateString);
}

void ofxTLParameterString::disable(){
    ofxTLTrack::enable();
//    parameter->removeListener(this, &ofxTLParameterBool::addKey);
    ofRemoveListener(ofEvents().update, this, &ofxTLParameterString::update);
    ofRemoveListener(events().playheadScrubbed, this, &ofxTLParameterString::updateScrub);
//    ofRemoveListener(events().bangFired, this, &ofxTLParameterString::updateString);

}

void ofxTLParameterString::addKey(string & v){
    if(!getTimeline()->getIsPlaying()){
//   NOT IMPLEMENTED
    }
}

void ofxTLParameterString::update(ofEventArgs & args){
//    if(timeline->getIsPlaying()) *parameter = isOn();
}

void ofxTLParameterString::updateScrub(ofxTLPlaybackEventArgs & args){
//    if(parameter != NULL) parameter->setWithoutEventNotifications(isOn());
}

void ofxTLParameterString::updateString(ofxTLBangEventArgs & args){
    if(parameter != NULL) parameter->set(args.flag);
//    if(parameter != NULL) parameter->setWithoutEventNotifications(args.flag);
}

void ofxTLParameterString::bangFired(ofxTLKeyframe* key){
    if(parameter != NULL) parameter->set(((ofxTLFlag*)key)->textField.text);
    ofxTLFlags::bangFired(key);
}
