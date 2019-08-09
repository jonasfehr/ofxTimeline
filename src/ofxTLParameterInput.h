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
#include "ofMain.h"

class ofxTLParameterFloat : public ofxTLCurves{
public:
    ofxTLParameterFloat(ofParameter<float> * param);
    
    ~ofxTLParameterFloat();
    
    void update(ofEventArgs & args);
    
    ofParameter<float> *parameter;
};

class ofxTLParameterInt : public ofxTLCurves{
public:
    ofxTLParameterInt(ofParameter<int> * param);
    
    ~ofxTLParameterInt();
    
    void update(ofEventArgs & args);
    
    ofParameter<int> *parameter;
};

class ofxTLParameterBool : public ofxTLSwitches{
public:
    ofxTLParameterBool(ofParameter<bool> * param);
    
    ~ofxTLParameterBool();
    
    void update(ofEventArgs & args);
    
    ofParameter<bool> *parameter;
};

#endif /* ofxTLParameterInput_hpp */

