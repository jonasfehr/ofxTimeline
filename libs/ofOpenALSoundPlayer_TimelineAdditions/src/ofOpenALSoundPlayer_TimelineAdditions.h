#pragma once

#include "ofMain.h"
#include "ofOpenALSoundPlayer_Timeline.h"


// --------------------- player functions:
class ofOpenALSoundPlayer_TimelineAdditions : public ofOpenALSoundPlayer_Timeline {

	public:

		ofOpenALSoundPlayer_TimelineAdditions();
		virtual ~ofOpenALSoundPlayer_TimelineAdditions();

        float getDuration() const;
        int getNumChannels() const;

        vector<short> & getBuffer();
        vector<float>& getCurrentBuffer(int _size);
        vector<float>& getBufferForFrame(int _frame, float _fps, int _size);
        vector<float>& getAverages();
        void setLogAverages(int minBandwidth, int bandsPerOctave);
        int getMinBandwidth() const;
        int getBandsPerOctave() const;
        float calculateAverage(float lowFreq, float hiFreq);
        int freqToIndex(float freq);

	protected:
        vector<float> currentBuffer;
        vector<float> averages;
        int avgPerOctave;
        int octaves;
        int currentMinBandwidth;
        int currentBandsPerOctave;
        float bandWidth;

};
