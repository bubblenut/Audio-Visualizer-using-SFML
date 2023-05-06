#pragma once

#include "BaseAudioProcessor.h"

#include <string>

#include <SFML/Graphics.hpp>

using namespace std;

class FileAudioProcessor : public BaseAudioProcessor {
public:
    FileAudioProcessor(const string& filePath);

    double GetSampleRate() const override;
    vector<double> Read() override;
    vector<double> Read(size_t size) override;
    void Start() override;
private:
    sf::Clock Clock;
    double PrevTime;
    size_t Offset;
    double SampleRate;
    vector<vector<double>> Audio;
};
