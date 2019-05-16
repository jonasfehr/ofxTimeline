#include "ofOpenALSoundPlayer_TimelineAdditions.h"


#if defined (TARGET_OF_IOS) || defined (TARGET_OSX)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

//------------------------------------------------------------
ofOpenALSoundPlayer_TimelineAdditions::ofOpenALSoundPlayer_TimelineAdditions(){
    octaves         = 0;
    duration		= 0;

}

// ----------------------------------------------------------------------------
ofOpenALSoundPlayer_TimelineAdditions::~ofOpenALSoundPlayer_TimelineAdditions(){

}

// ----------------------------------------------------------------------------
float ofOpenALSoundPlayer_TimelineAdditions::getDuration() const{
    return duration;
}

// ----------------------------------------------------------------------------
int ofOpenALSoundPlayer_TimelineAdditions::getNumChannels() const{
    return channels;
}

// ----------------------------------------------------------------------------
vector<short> & ofOpenALSoundPlayer_TimelineAdditions::getBuffer(){
    return buffer;
}

// ----------------------------------------------------------------------------
vector<float>& ofOpenALSoundPlayer_TimelineAdditions::getCurrentBuffer(int _size)
{
    if(int(currentBuffer.size()) != _size)
    {
        currentBuffer.resize(_size);
    }
    currentBuffer.assign(currentBuffer.size(),0);

    int pos;
    for(int k = 0; k < int(sources.size())/channels; ++k)
    {
        alGetSourcei(sources[k*channels],AL_SAMPLE_OFFSET,&pos);
        for(int i = 0; i < channels; ++i)
        {
            for(int j = 0; j < _size; ++j)
            {
                if(pos+j<(int)buffer.size())
                {
                    currentBuffer[j] += float(buffer[(pos+j)*channels+i])/65534.0f;
                }
                else
                {
                    currentBuffer[j] = 0;
                }
            }
        }
    }
    return currentBuffer;
}

// ----------------------------------------------------------------------------
vector<float>& ofOpenALSoundPlayer_TimelineAdditions::getBufferForFrame(int _frame, float _fps, int _size)
{
    if(int(currentBuffer.size()) != _size)
    {
        currentBuffer.resize(_size);
    }
    currentBuffer.assign(currentBuffer.size(),0);

    int pos = _frame*float(samplerate)/_fps;
    for(int k = 0; k < int(sources.size())/channels; ++k)
    {
        for(int i = 0; i < channels; ++i)
        {
            for(int j = 0; j < _size; ++j)
            {
                if(pos+j<(int)buffer.size())
                {
                    currentBuffer[j] += float(buffer[(pos+j)*channels+i])/65534.0f;
                }
                else
                {
                    currentBuffer[j] = 0;
                }
            }
        }
    }
    return currentBuffer;
}

// ----------------------------------------------------------------------------
vector<float>& ofOpenALSoundPlayer_TimelineAdditions::getAverages(){

    if(averages.size() > 0){
        getSpectrum(bins.size());
        float max = 0;
        for (int i = 0; i < octaves; i++){
            float lowFreq, hiFreq, freqStep;
            if (i == 0){
                lowFreq = 0;
            }
            else{
                lowFreq = (samplerate / 2) / powf(2, octaves - i);
            }

            hiFreq = (samplerate / 2) / powf(2, octaves - i - 1);
            freqStep = (hiFreq - lowFreq) / avgPerOctave;
            float f = lowFreq;
            for (int j = 0; j < avgPerOctave; j++){
                int offset = j + i * avgPerOctave;
                averages[offset] = calculateAverage(f, f + freqStep);
                max = MAX(max,averages[offset]);
                f += freqStep;
            }
        }
    }

    return averages;
}

// ----------------------------------------------------------------------------
int ofOpenALSoundPlayer_TimelineAdditions::freqToIndex(float freq) {
    if (freq < bandWidth / 2) return 0;
    if (freq > samplerate / 2 - window.size() / 2) return bins.size() - 1;
    float fraction = freq / samplerate;
    return int( floor(window.size() * fraction + .5) );
}

// ----------------------------------------------------------------------------
float ofOpenALSoundPlayer_TimelineAdditions::calculateAverage(float lowFreq, float hiFreq) {
    int lowBound = freqToIndex(lowFreq);
    int hiBound = freqToIndex(hiFreq);
    float avg = 0;
    for (int i = lowBound; i <= hiBound; i++) {
        avg += bins[i];
    }
    avg /= (hiBound - lowBound + 1);
    return avg;
}

// ----------------------------------------------------------------------------
void ofOpenALSoundPlayer_TimelineAdditions::setLogAverages(int minBandwidth, int bandsPerOctave){
    if(!isLoaded()){
        return;
    }

    currentMinBandwidth = minBandwidth;
    currentBandsPerOctave = bandsPerOctave;

    float nyquist = (float) samplerate / 2.0f;
    octaves = 1;
    while ((nyquist /= 2) > minBandwidth){
        octaves++;
    }

    avgPerOctave = bandsPerOctave;
    averages.resize(octaves * bandsPerOctave);
}

// ----------------------------------------------------------------------------
int ofOpenALSoundPlayer_TimelineAdditions::getMinBandwidth() const{
    return currentMinBandwidth;
}

// ----------------------------------------------------------------------------
int ofOpenALSoundPlayer_TimelineAdditions::getBandsPerOctave() const{
    return currentBandsPerOctave;
}
