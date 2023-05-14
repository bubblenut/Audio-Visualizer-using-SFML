#include "Visualizer.h"

#include <iostream>
#include <algorithm>


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
	window.setKeyRepeatEnabled(false);
}

void::Visualizer::run() {
	//установка иконки приложения 

	sf::Image icon;
	icon.loadFromFile("icons/icon_particles.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//создается AuidioProcessor и контейнер куда будет вноситься аудио

	Reader.Start();
	vector<double> data;

	//инициализация модов отрисовки

	Amplitude* amplitude = new Amplitude(Reader.GetSampleRate());
	Spectre* spectre = new Spectre(Reader.GetSampleRate());
	
	//список вкл/откл отрисовки, хранит моды в порядке добавления
	vector<AbstractMode*> avaliableModes;
	avaliableModes.push_back(amplitude);

	//AuidioProcessor читает музыку в audio

	//audio передается в обработчик FFT
 
	while(window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}


			//вкл/выкл моды с клавиатуры
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Num1) {
					auto it = find(avaliableModes.begin(), avaliableModes.end(), amplitude);

					if (it != avaliableModes.end()) {
						avaliableModes.erase(it);
					} else {
						avaliableModes.push_back(amplitude);
					}
				} else if (event.key.code == sf::Keyboard::Num2) {
					auto it = find(avaliableModes.begin(), avaliableModes.end(), spectre);

					if (it != avaliableModes.end()) {
						avaliableModes.erase(it);
					} else {
						avaliableModes.push_back(spectre);
					}
				}
			}
		}

		if (data.empty()) {
			data = Reader.Read(spectre->GetReadSize());
		} else {
			auto tmp = Reader.Read();
			data.insert(data.end(), tmp.begin(), tmp.end());
			data.erase(data.begin(), data.begin() + tmp.size());
		}

		window.clear();
		//у всех включенных модов вызывается апдейт и отрисовка
		for (auto& mode : avaliableModes) {
			mode->update(data);
			mode->draw(window);
		}
		window.display();
	}
}
