#include "PulseAudioProcessor.h"

#include <iostream>
#include <exception>
#include <cmath>

using namespace std;

#define RETRY_COUNT 5

PulseAudioProcessor::PulseAudioProcessor()
    : SampleRate(44100)
{
    pa_sample_spec ss;
    
    ss.format = PA_SAMPLE_S16LE;
    ss.channels = 1;
    ss.rate = SampleRate;

    int error = -1;
    for (size_t i = 0; i < RETRY_COUNT; ++i) {
        if (error == 0) {
            break;
        }
        Device = pa_simple_new(NULL,
                        "audio_visualizer",
                        PA_STREAM_RECORD,
                        "bluez_sink.4C_79_6E_F3_78_38.a2dp_sink.monitor",
                        "audio_visualizer",
                        &ss,
                        NULL,
                        NULL,
                        &error
                        );
    }
    cout << error << endl;
    Buffer = malloc(100000);
    PowSbits = pow(2, 16);
}

PulseAudioProcessor::~PulseAudioProcessor() {
    free(Buffer);
    pa_simple_free(Device);
}

double PulseAudioProcessor::GetSampleRate() const {
    return SampleRate;
}

vector<double> PulseAudioProcessor::Read() {
    if (PrevTime == 0) {
        Clock.restart();
    }
    double t = Clock.getElapsedTime().asSeconds();
    size_t size = (t - PrevTime) * SampleRate;
    PrevTime = t;

    return Read(size);
}

vector<double> PulseAudioProcessor::Read(size_t size) {
    bool succ = false;
    for (size_t i = 0; i < RETRY_COUNT; ++i) {
        if (pa_simple_read(Device, Buffer, size * sizeof(int16_t), NULL) == 0) {
            succ = true;
            break;
        }
    }

    if (!succ) {
        return {};
    }

    vector<double> result;

    for (int i = 0; i < size; ++i) {
        result.push_back(static_cast<int16_t*>(Buffer)[i] / PowSbits);
    }
    return result;
}
