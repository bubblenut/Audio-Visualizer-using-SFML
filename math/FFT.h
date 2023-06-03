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
//деструктор перегружен для очистки памяти
    ~FFT();

//легаси функция для аккуратной инициализации стартовых данных БПФ 
//таких как частоты дискр. степени 2, плана и вычисления размера окна ханна
    void LazyInit(double sampleRateD);

//преобразование Фурье проиходит в этой функции
    void Calculate(vector<double>& input);

//функция возвращает частоту дискр степени 2
    size_t GetReadSize() const;

//получение результата ффт
    shared_ptr<vector<complex<double>>> GetResult();
private:
//в этой функции работает оконное сглаживание
    void CalculateWindowHann(const vector<double>& input);

    vector<double> _WindowHann;
    fftw_complex* OutFFT;
    fftw_plan Plan;
    size_t SampleRate = 1;
    shared_ptr<vector<complex<double>>> FftResult;
};
