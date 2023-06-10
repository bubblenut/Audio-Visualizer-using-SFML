#pragma once
#include "AbstractMode.h"
#include "../math/FFT.h"

using namespace sf;
class Rave : public AbstractMode {
private:
    vector<double> Hz;

    CircleShape CenterCircle;
public:
    Rave(double sample_rate_audio, shared_ptr<FFT> fftPtr_);
    void draw(sf::RenderWindow& window) override;
    void update(vector<double>& audio_in) override;
};