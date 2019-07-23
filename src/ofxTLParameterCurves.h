//
//  ofxTLParameterCurves.hpp
//  example-parameterCurves
//
//  Created by Jonas Fehr on 23/07/2019.
//

#ifndef ofxTLParameterCurves_hpp
#define ofxTLParameterCurves_hpp

#include <stdio.h>
#include "ofxTLCurves.h"
#include "ofMain.h"

class ofxTLParameterCurves : public ofxTLCurves{
public:
    ofxTLParameterCurves(ofParameter<float> * param){
        this->parameter = param;
        ofAddListener(ofEvents().update, this, &ofxTLParameterCurves::update);
    }
    
    ~ofxTLParameterCurves(){
        ofRemoveListener(ofEvents().update, this, &ofxTLParameterCurves::update);
    }
    
    void update(ofEventArgs & args){
        *parameter = getValue();
    }
    
    ofParameter<float> *parameter;
};

#endif /* ofxTLParameterCurves_hpp */

