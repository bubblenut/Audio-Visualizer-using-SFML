#pragma once

#include "AbstractMode.h"
#include "../math/FFT.h"

class Spectre : public AbstractMode
{
private:
    vector<double> rectH;
    FFT fft;
public:
    Spectre(const vector<double>& audio_in, double sample_rate_audio, int sample_rate_fft);
    void draw(sf::RenderWindow& window) override;
    void update() override;
};