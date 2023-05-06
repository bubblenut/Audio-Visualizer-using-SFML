#include "PcmAudioProcessor.h"

#include <iostream>
#include <exception>
#include <cmath>

using namespace std;

#define CHECK_PCM_ERROR(error) \
if (error < 0) { \
    throw runtime_error(snd_strerror(error)); \
} else { \
    cout << "Success" << endl; \
}

PcmAudioProcessor::PcmAudioProcessor(const string& deviceName) 
{
    int err;
    snd_pcm_hw_params_t *hwParams;

    cout << "PCM open: ";
    err = snd_pcm_open(&PcmDevice, deviceName.data(), SND_PCM_STREAM_CAPTURE, SND_PCM_NONBLOCK);
    CHECK_PCM_ERROR(err);

    cout << "HW params malloc: ";
    err = snd_pcm_hw_params_malloc(&hwParams);
    CHECK_PCM_ERROR(err);

    cout << "HW params any: ";
    err = snd_pcm_hw_params_any (PcmDevice, hwParams);
    CHECK_PCM_ERROR(err);

    cout << "Set rate resample: ";
    unsigned int resample = 1;
    err = snd_pcm_hw_params_set_rate_resample(PcmDevice, hwParams, resample);
    CHECK_PCM_ERROR(err);
    
    cout << "HW set access: ";
    err = snd_pcm_hw_params_set_access(PcmDevice, hwParams, SND_PCM_ACCESS_RW_INTERLEAVED);
    CHECK_PCM_ERROR(err);
    
    cout << "HW set format: ";
    err = snd_pcm_hw_params_set_format(PcmDevice, hwParams, SND_PCM_FORMAT_S16_LE);
    CHECK_PCM_ERROR(err);
    
    cout << "HW set channels: ";
    err = snd_pcm_hw_params_set_channels(PcmDevice, hwParams, 1);
    CHECK_PCM_ERROR(err);
    
    snd_pcm_uframes_t setBufferSize = 11140000;
    err = snd_pcm_hw_params_set_buffer_size_max(PcmDevice, hwParams, &setBufferSize);
    CHECK_PCM_ERROR(err);
    
    cout << "HW set rate near: ";
    unsigned int actualRate = 44100;
    err = snd_pcm_hw_params_set_rate_near(PcmDevice, hwParams, &actualRate, 0);
    CHECK_PCM_ERROR(err);
    
    cout << "Set HW params: ";
    err = snd_pcm_hw_params(PcmDevice, hwParams);
    CHECK_PCM_ERROR(err);
    
    snd_pcm_hw_params_get_buffer_size(hwParams, &BufferSize);
    SampleRate = actualRate;
    Sbits = snd_pcm_hw_params_get_sbits(hwParams);

    snd_pcm_hw_params_free(hwParams);

    cout << "PCM prepare: ";
    err = snd_pcm_prepare(PcmDevice);
    CHECK_PCM_ERROR(err);

    Buffer = malloc(BufferSize * Sbits / 8);
    PowSbits = pow(2, Sbits);
}

double PcmAudioProcessor::GetSampleRate() const {
    return SampleRate;
}

vector<double> PcmAudioProcessor::Read() {
    while (snd_pcm_avail(PcmDevice) < 0) {}
    auto count = snd_pcm_readi(PcmDevice, Buffer, SampleRate);

    if (count < 0) {
        return {};
    }

    vector<double> result(count);
    for (int i = 0; i < count; ++i) {
        result[i] = static_cast<int16_t*>(Buffer)[i] / PowSbits;
    }

    return result;
}

vector<double> PcmAudioProcessor::Read(size_t size) {
    vector<double> result;

    while (result.size() < size) {
        while (snd_pcm_avail(PcmDevice) < 0) {}
        auto count = snd_pcm_readi(PcmDevice, Buffer, size - result.size());

        if (count > 0) {
            for (int i = 0; i < count; ++i) {
                result.push_back(static_cast<int16_t*>(Buffer)[i] / PowSbits);
            }
        }
    }
    return result;
}

void PcmAudioProcessor::Start() {

}
