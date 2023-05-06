#pragma once

#include "../visualizer/Visualizer.h"
#include "../math/FFT.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class AbstractMode
{
public:
    AbstractMode(double sample_rate_audio);

    virtual ~AbstractMode() {};
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(vector<double>& audio_in) = 0;
    virtual size_t GetReadSize() const;

protected:
    FFT fft;
    vector<double> audio;
    double sample_rate_audio;
};
