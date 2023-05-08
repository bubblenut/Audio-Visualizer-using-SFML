#pragma once

#include "BaseAudioProcessor.h"

#include <string>

#include <SFML/Graphics.hpp>

#include <alsa/asoundlib.h>

using namespace std;

class PcmAudioProcessor : public BaseAudioProcessor {
public:
    PcmAudioProcessor(const string& deviceName = "default");

    double GetSampleRate() const override;
    vector<double> Read() override;
    vector<double> Read(size_t size) override;
private:
    void* Buffer;
    snd_pcm_t* PcmDevice;
    snd_pcm_uframes_t BufferSize;
    int Sbits;
    double PowSbits;
    unsigned int SampleRate;
};
