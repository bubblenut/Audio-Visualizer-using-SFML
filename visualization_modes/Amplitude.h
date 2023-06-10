#pragma once

#include "AbstractMode.h"

class Amplitude : public AbstractMode
{
private:
    sf::VertexArray points;
public:
    Amplitude(double sample_rate_audio, shared_ptr<FFT> fftPtr_);
    void draw(sf::RenderWindow& window) override;
    void update(vector<double>& audio_in) override;
};
