#include "FFT.h"

FFT::~FFT() {
    delete[] OutFFT;
    fftw_destroy_plan(Plan);
    fftw_cleanup();
}

void FFT::LazyInit(double sampleRateD) {
    SampleRate = 1;
    while (SampleRate <= sampleRateD) {
        SampleRate *= 2;
    }
    SampleRate /= 2;

    OutFFT = new fftw_complex[SampleRate / 2 + 1];
    _WindowHann.resize(SampleRate);

    Plan = fftw_plan_dft_r2c_1d(SampleRate, nullptr, OutFFT, FFTW_ESTIMATE);
}

void FFT::CalculateWindowHann(const vector<double>& input) {
    const auto N = input.size();

    for (size_t i = 0; i < N; ++i) {
        auto multiplier = 0.5 * (1 - cos(2 * M_PI * i / (SampleRate - 1)));
        _WindowHann[i] = multiplier * input[i];
    }
}

unique_ptr<vector<complex<double>>> FFT::Calculate(vector<double>& input) {
    unique_ptr<vector<complex<double>>> result = make_unique<vector<complex<double>>>(SampleRate / 2 + 1);
    CalculateWindowHann(input);
    fftw_execute_dft_r2c(Plan, input.data(), OutFFT);
    fftw_cleanup();

    for (size_t i = 0; i < SampleRate / 2 + 1; ++i) {
        (*result)[i] = {OutFFT[i][0], OutFFT[i][1]};
    }

    return std::move(result);
}
