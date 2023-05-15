#pragma once

#include <vector>

//отслеживание звука будет при помощи библиотеки sfml
#include <SFML/Graphics.hpp>

using namespace std;

class BaseAudioProcessor
{
public:
//функция, чтобы узнать частоту дискретизации
    virtual double GetSampleRate() const = 0;

//две разные функции для чтения
    virtual vector<double> Read() = 0;
    virtual vector<double> Read(size_t size) = 0;

//функция для обнуления времени
    virtual void Start() {
        Clock.restart();
    }

//предусмотрена перегрузка деструктора
    virtual ~BaseAudioProcessor() {}
protected:
    sf::Clock Clock;
    double PrevTime = 0;
};
