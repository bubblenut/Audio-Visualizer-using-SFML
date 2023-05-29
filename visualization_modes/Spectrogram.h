#pragma once

#include "AbstractMode.h"
#include "../math/FFT.h"

class Spectrogram : public AbstractMode
{
private:
    vector<double> rectH;
    FFT fft;
    double RowPosition;
    vector<vector<double>> Matrix;
    int Start, End;
    bool ChangeStrategy = false;
public:
    Spectrogram(double sample_rate_audio);
    void draw(sf::RenderWindow& window) override;
    void update(vector<double>& audio_in) override;
};
