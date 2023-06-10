#pragma once

#include "../visualizer/Visualizer.h"
#include "../math/FFT.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

using namespace std;

class AbstractMode
{
public:
//конструктор будет вызывать LazyInit у объекта fft
    AbstractMode(double sample_rate_audio, shared_ptr<FFT> fftPtr_);

    virtual ~AbstractMode() {};

//перегруженная из SFML функция draw для отрисовки эффектов на экране
    virtual void draw(sf::RenderWindow& window) = 0;

//функция обновления состояние каждый кадр
    virtual void update(vector<double>& audio_in) = 0;

protected:
//математический объект
    shared_ptr<FFT> fftPtr;

//данные для отрисовки
    vector<double> audio;

//частота дискретизации
    double sample_rate_audio;
};
