#include "FFT.h"

#include <exception>
#include <iostream>

FFT::~FFT() {
    delete[] OutFFT;
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
    FftResult = make_shared<vector<complex<double>>>(SampleRate / 2 + 1);
}

void FFT::CalculateWindowHann(const vector<double>& input) {
    if (input.size() != SampleRate) {
        throw runtime_error("input size don't equal sampleRate size");
    }

    const auto N = input.size();

    for (size_t i = 0; i < N; ++i) {
        auto multiplier = 0.5 * (1 - cos(2 * M_PI * i / (SampleRate - 1)));
        _WindowHann[i] = multiplier * input[i];
    }
}

void FFT::Calculate(vector<double>& input) {
    CalculateWindowHann(input);
    fftw_execute_dft_r2c(Plan, input.data(), OutFFT);
    fftw_cleanup();

    for (size_t i = 0; i < SampleRate / 2 + 1; ++i) {
        (*FftResult)[i] = {OutFFT[i][0], OutFFT[i][1]};
    }
}

size_t FFT::GetReadSize() const {
    return SampleRate;
}

shared_ptr<vector<complex<double>>> FFT::GetResult() {
    return FftResult;
}
