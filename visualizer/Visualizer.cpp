#include "Visualizer.h"

#include <iostream>

#include "../visualization_modes/Spectre.h"
#include "../visualization_modes/Amplitude.h"

using namespace std;
using namespace sf;

Visualizer::Visualizer() : Reader() {
    ContextSettings settings;
	settings.antialiasingLevel = 4;
	
	const VideoMode desktop = VideoMode::getDesktopMode();
	window.create(VideoMode(WIDTH, HEIGHT, desktop.bitsPerPixel), "Visualizrr",Style::Default, settings);
	window.setFramerateLimit(FPS);
}

void::Visualizer::run() {
	//установка иконки приложения
	sf::Image icon;
	icon.loadFromFile("icons/icon_particles.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	//создается AuidioProcessor, FFT, базовый Mode
	Reader.Start();
	Spectre spectre(Reader.GetSampleRate());
	Amplitude amplitude(Reader.GetSampleRate());
	vector<double> data;

	//AuidioProcessor читает музыку в audio

	//audio передается в обработчик FFT
 
	while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if (data.empty()) {
			data = Reader.Read(spectre.GetReadSize());
		} else {
			auto tmp = Reader.Read();
			data.insert(data.end(), tmp.begin(), tmp.end());
			data.erase(data.begin(), data.begin() + tmp.size());
		}

	//FFT принимает находит нужный фрагмент аудио и начинает обрабатыввать его

	//FFT возвращает обработанные данные в любой Mode

	//Mode отрисовывает обработанные данные согласно своим настройкам, вызывает перегруженный draw

		window.clear();

		spectre.update(data);
		amplitude.update(data);

		spectre.draw(window);
		amplitude.draw(window);

		window.display();
	}
}
