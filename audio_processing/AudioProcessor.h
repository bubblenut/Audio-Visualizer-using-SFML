#pragma once
#include <audiorw.hpp>

using namespace std;

class AudioProcessor
{
private:
    vector<double> audio;
    double sample_rate;
public:
    AudioProcessor() {}
    ~AudioProcessor() {}
};