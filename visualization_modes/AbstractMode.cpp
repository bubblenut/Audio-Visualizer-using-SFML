#include "AbstractMode.h"

using namespace std;
using namespace sf;

AbstractMode::AbstractMode(const vector<double>& audio_in, double sample_rate_audio, int sample_rate_fft) :
audio(audio_in),
sample_rate_audio(sample_rate_audio),
sample_rate_fft(sample_rate_fft) {}

