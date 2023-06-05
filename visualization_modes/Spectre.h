#pragma once

#include "AbstractMode.h"
#include "../math/FFT.h"

class Spectre : public AbstractMode
{
private:
    vector<double> rectH;
public:
    Spectre(double sample_rate_audio, shared_ptr<FFT> fftPtr_);
    void draw(sf::RenderWindow& window) override;
    void update(vector<double>& audio_in) override;
};
