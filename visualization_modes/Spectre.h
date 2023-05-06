#pragma once

#include "AbstractMode.h"
#include "../math/FFT.h"

class Spectre : public AbstractMode
{
private:
    vector<double> rectH;
    FFT fft;
public:
    Spectre(double sample_rate_audio);
    void draw(sf::RenderWindow& window) override;
    void update(vector<double>& audio_in) override;
};