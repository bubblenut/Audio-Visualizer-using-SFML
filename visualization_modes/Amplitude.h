#pragma once

#include "AbstractMode.h"

class Amplitude : public AbstractMode
{
private:
    sf::VertexArray points;
public:
    Amplitude(const vector<double>& audio_in, double sample_rate_audio, int sample_rate_fft);
    void draw(sf::RenderWindow& window) override;
    void update() override;
};
