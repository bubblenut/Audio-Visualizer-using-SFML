#include "AbstractMode.h"

#include <iostream>

using namespace std;
using namespace sf;

AbstractMode::AbstractMode(double sample_rate_audio)
    : sample_rate_audio(sample_rate_audio)
{
    fft.LazyInit(sample_rate_audio);
}

size_t AbstractMode::GetReadSize() const {
    return fft.GetReadSize();
}