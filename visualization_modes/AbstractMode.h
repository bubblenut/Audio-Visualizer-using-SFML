#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class AbstractMode
{
public:
    AbstractMode(const vector<double>& audio_in, double sample_rate_audio, int sample_rate_fft);

    virtual ~AbstractMode() {};
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update() = 0;

protected:
    const vector<double>& audio;
    double sample_rate_audio;
    int sample_rate_fft;    
};
