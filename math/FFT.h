#pragma once

#include <vector>
#include <complex>
#include <cmath>
#include <memory>

#include <fftw3.h>

using namespace std;

class FFT
{
public:
    ~FFT();

    void LazyInit(double sampleRateD);
    unique_ptr<vector<complex<double>>> Calculate(vector<double>& input);
    size_t GetReadSize() const;
private:
    void CalculateWindowHann(const vector<double>& input);

    vector<double> _WindowHann;
    fftw_complex* OutFFT;
    fftw_plan Plan;
    size_t SampleRate = 1;
};
