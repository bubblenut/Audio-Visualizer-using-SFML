#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../visualization_modes/AbstractMode.h"
#include "../audio_processing/PcmAudioProcessor.h"

#define WIDTH 1000
#define HEIGHT 800
#define FPS 55

using namespace std;

class Visualizer
{
private:
    sf::RenderWindow window;

    string active_audio;

    string active_mode;
    //void initialize_mode(const string& mode, const string& audio);

    //unique_ptr<AbstractMode> mode;

    PcmAudioProcessor Reader;
public:
    Visualizer();
    void run();    
};