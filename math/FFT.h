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
private:
    vector<double> _WindowHann;
    void CalculateWindowHann(const vector<double>& input);
    fftw_complex* outFFT;
    fftw_plan Plan;
    int SampleRate = 1;
};
