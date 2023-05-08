#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

using namespace std;

class BaseAudioProcessor
{
public:
    virtual double GetSampleRate() const = 0;
    virtual vector<double> Read() = 0;
    virtual vector<double> Read(size_t size) = 0;
    virtual void Start() {
        Clock.restart();
    }

    virtual ~BaseAudioProcessor() {}
protected:
    sf::Clock Clock;
    double PrevTime = 0;
};
