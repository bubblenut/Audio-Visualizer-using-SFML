#include "AbstractMode.h"

#include <iostream>

using namespace std;
using namespace sf;

AbstractMode::AbstractMode(double sample_rate_audio, shared_ptr<FFT> _fftPtr)
    : sample_rate_audio(sample_rate_audio), fftPtr(_fftPtr)
{}
