#pragma once

#include "BaseAudioProcessor.h"

#include <alsa/asoundlib.h>

#include <fstream>

#include <string>

using namespace std;

class PcmAudioProcessor : public BaseAudioProcessor {
public:
    PcmAudioProcessor(const string& deviceName = "default");

    vector<double> Read() override;
    vector<double> Read(size_t size) override;
    void Start() override;
private:
    ofstream log;
    void* Buffer;
    snd_pcm_t* PcmDevice;
    snd_pcm_uframes_t BufferSize;
    int Sbits;
    double PowSbits;
    unsigned int SampleRate;
};
