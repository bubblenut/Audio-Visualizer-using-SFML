#pragma once

#include "../visualization_modes/AbstractMode.h"
#include "../audio_processing/PcmAudioProcessor.h"
#include "../audio_processing/FileAudioProcessor.h"
#include "../audio_processing/PulseAudioProcessor.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define WIDTH 1000
#define HEIGHT 800
#define FPS 55

class Visualizer
{
private:
    sf::RenderWindow window;

    string active_audio;

    string active_mode;
    //void initialize_mode(const string& mode, const string& audio);

    //unique_ptr<AbstractMode> mode;

    PulseAudioProcessor Reader;
public:
    Visualizer();
    void run();    
};
