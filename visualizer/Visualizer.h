#pragma once

#include "../visualization_modes/AbstractMode.h"
#include "../audio_processing/PcmAudioProcessor.h"
#include "../audio_processing/FileAudioProcessor.h"
#include "../audio_processing/PulseAudioProcessor.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define WIDTH 2160
#define HEIGHT 1440
#define FPS 55

class Visualizer
{
private:
    sf::RenderWindow window;

    PulseAudioProcessor Reader;
public:
//в конструкторе инициализируется окно рендеринга и аудиопроцессор
    Visualizer();

//тут происходит контроль над модами и обработка действий пользователя
    void run();
};
