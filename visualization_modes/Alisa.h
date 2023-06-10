#pragma once

#include "AbstractMode.h"

using namespace sf;

class Alisa : public AbstractMode
{
private:
    vector<Vector2f> qPositions;
    vector<int> qColors;
    Vector2f qSize;
public:
    Alisa (double sample_rate_audio, shared_ptr<FFT> fftPtr_);
    void draw(sf::RenderWindow& window) override;
    void update(vector<double>& audio_in) override;
};