#pragma once

#include <vector>

using namespace std;

class BaseAudioProcessor
{
public:
    virtual vector<double> Read() = 0;
    virtual vector<double> Read(size_t size) = 0;
    virtual void Start() = 0;

    virtual ~BaseAudioProcessor() {}
};
