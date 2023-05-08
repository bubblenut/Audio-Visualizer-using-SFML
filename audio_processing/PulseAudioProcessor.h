#pragma once

#include "BaseAudioProcessor.h"

#include <pulse/pulseaudio.h>
#include <pulse/simple.h>

#include <SFML/Graphics.hpp>

class PulseAudioProcessor : public BaseAudioProcessor {
public:
    PulseAudioProcessor();
    ~PulseAudioProcessor();

    double GetSampleRate() const override;
    vector<double> Read() override;
    vector<double> Read(size_t size) override;
private:
    double PowSbits;
    pa_simple* Device;
    const double SampleRate;
    void* Buffer;
};
