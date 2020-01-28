//
//  ofxTLParameterInput.h
//  example-parameterCurves
//
//  Created by Jonas Fehr on 23/07/2019.
//

#ifndef ofxTLParameterInput_hpp
#define ofxTLParameterInput_hpp

#include <stdio.h>
#include "ofxTLCurves.h"
#include "ofxTLSwitches.h"
#include "ofxTLFlags.h"
#include "ofxTLPage.h"
#include "ofMain.h"

class ofxTLParameterFloat : public ofxTLCurves{
public:
    ofxTLParameterFloat(ofParameter<float> * param);
    
    ~ofxTLParameterFloat();
    
    void enable();
    void disable();
    
    void addKey(float & v);
    
    void update(ofEventArgs & args);
    void updateScrub(ofxTLPlaybackEventArgs & args);
    
    ofParameter<float> *parameter;
};

class ofxTLParameterInt : public ofxTLCurves{
public:
    ofxTLParameterInt(ofParameter<int> * param);
    
    ~ofxTLParameterInt();
    
    void enable();
    void disable();
    
    void addKey(int & v);
    
    void update(ofEventArgs & args);
    void updateScrub(ofxTLPlaybackEventArgs & args);
    
    ofParameter<int> *parameter;
};

class ofxTLParameterBool : public ofxTLSwitches{
public:
    ofxTLParameterBool(ofParameter<bool> * param);
    
    ~ofxTLParameterBool();
    
    void enable();
    void disable();
    
    void addKey(bool & v);
    
    void update(ofEventArgs & args);
    void updateScrub(ofxTLPlaybackEventArgs & args);
    
    ofParameter<bool> *parameter;
};

class ofxTLParameterString : public ofxTLFlags{
public:
    ofxTLParameterString(ofParameter<string> * param);
    
    ~ofxTLParameterString();
    
    void enable();
    void disable();
    
    void addKey(string & v);
    
    void update(ofEventArgs & args);
    void updateScrub(ofxTLPlaybackEventArgs & args);
    void updateString(ofxTLBangEventArgs & args);

    void bangFired(ofxTLKeyframe* key);
    
    ofParameter<string> *parameter;
};

#endif /* ofxTLParameterInput_hpp */

