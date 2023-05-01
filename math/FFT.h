#pragma once
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <fftw3.h>
#include <numeric>
#include <SFML/Graphics.hpp>

using namespace std;

class FFT
{
private:
    //входные даннные

    vector<double> in;

    //техническая информация

    vector<double> window_hann;
    fftw_complex* out_complex_ptr;
    fftw_plan p;
    int sample_rate = 1;

    //выходные данные

    vector<complex<double>> out;
public:
    ~FFT();

    void lazy_init(double sample_rate_d);

    void initialize(double sample_rate_in,
        const vector<double>& audio,
        const sf::Clock& clock);

    vector<complex<double>> getOut();

    vector<double> getHeight();
    
    vector<double> getWindowHann();
};
