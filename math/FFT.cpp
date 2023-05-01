#include "FFT.h"

using namespace std;

FFT::~FFT() {
    delete[] out_complex_ptr;
}

void FFT::lazy_init(double sample_rate_d) {
    sample_rate = 1;
    while (sample_rate <= sample_rate_d) {
        sample_rate *= 2;
    }
    sample_rate /= 2;

    out_complex_ptr = new fftw_complex[sample_rate];

    window_hann.resize(sample_rate);
    out.resize(sample_rate);
}

void FFT::initialize(double sample_rate_in,
        const vector<double>& audio,
        const sf::Clock& clock) {
    //вычислить sample_rate степени 2
    //заполнить in и window_hann

    float time = 0;
    if (in.size() != sample_rate) {
            int prev_idx = -1;
            while (in.size() != sample_rate) {
                int ind = clock.getElapsedTime().asSeconds() * sample_rate_in;
                if (prev_idx != ind) {
                    FFT::in.push_back(audio[ind]);
                    prev_idx = ind;
                }
            }
    } else {
        int delta = (clock.getElapsedTime().asSeconds() - time) * sample_rate_in;
        FFT::in.insert(FFT::in.end(), audio.begin() + time * sample_rate_in, audio.begin() + time * sample_rate_in + delta);
        FFT::in.erase(FFT::in.begin(), FFT::in.begin() + delta);
        time = clock.getElapsedTime().asSeconds();
    }

    for (int i = 0; i < in.size(); ++i) {
        double multiplier = 0.5 * (1 - cos(2 * M_PI * i / (sample_rate - 1)));
        FFT::window_hann[i] = multiplier * FFT::in[i];
    }

    //выполняем план и очищаем память
    fftw_plan p = fftw_plan_dft_r2c_1d(window_hann.size(), window_hann.data(), out_complex_ptr, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);        
    fftw_cleanup();

    for (int j = 0; j < in.size(); ++j) {
        FFT::out[j] = {out_complex_ptr[j][0], out_complex_ptr[j][1]};
    }
}

vector<complex<double>> FFT::getOut() {
    return FFT::out;
}

vector<double> FFT::getHeight() {
    vector<double> h(out.size());
    for (int i = 0; i < FFT::out.size(); ++i) {
        double re = out[i].real();
        double im = out[i].imag();
        h[i] = sqrt(re * re + im * im);
    }
    return h;
}

vector<double> FFT::getWindowHann() {
    return FFT::window_hann;
}