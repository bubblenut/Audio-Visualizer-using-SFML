#include "FileAudioProcessor.h"

#include <audiorw.hpp>

FileAudioProcessor::FileAudioProcessor(const string& filePath)
    : Offset(0), PrevTime(0)
{
    Audio = audiorw::read(filePath, SampleRate);
}

double FileAudioProcessor::GetSampleRate() const {
    return SampleRate;
}

vector<double> FileAudioProcessor::Read() {
    double time = Clock.getElapsedTime().asSeconds();
    vector<double> result(Audio[0].begin() + (SampleRate * PrevTime), Audio[0].begin() + (SampleRate * time));
    Offset = SampleRate * time;
    PrevTime = time;
    return result;
}

vector<double> FileAudioProcessor::Read(size_t size) {
    vector<double> result(Audio[0].begin() + Offset, Audio[0].begin() + Offset + size);
    Offset += size;
    PrevTime = Clock.getElapsedTime().asSeconds();
    return result;
}

void FileAudioProcessor::Start() {
    Clock.restart();
}
