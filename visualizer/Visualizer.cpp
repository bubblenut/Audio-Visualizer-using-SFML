#include "Visualizer.h"

#include <iostream>
#include <algorithm>


#include "../visualization_modes/Spectre.h"
#include "../visualization_modes/Amplitude.h"
#include "../visualization_modes/Rave.h"
#include "../visualization_modes/Alisa.h"

using namespace std;
using namespace sf;

#define bgPic "icons/3840x2160.jpg"

Visualizer::Visualizer() : Reader() {
    ContextSettings settings;
	settings.antialiasingLevel = 4;
	
	const VideoMode desktop = VideoMode::getDesktopMode();
	window.create(VideoMode(WIDTH, HEIGHT, desktop.bitsPerPixel), "Visualizrr",Style::Default, settings);
	//window.setFramerateLimit(FPS);
	window.setKeyRepeatEnabled(false);
}

//void controlModeDrawing(AbstractMode* mode, vector<AbstractMode*> vec);

void::Visualizer::run() {
	//установка иконки приложения

	sf::Image icon;
	icon.loadFromFile("icons/icon_particles.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//создается AuidioProcessor и контейнер куда будет вноситься аудио

	Reader.Start();
	vector<double> data;

	shared_ptr<FFT> fftPtr = make_shared<FFT>();
	fftPtr->LazyInit(Reader.GetSampleRate());

	//инициализация модов отрисовки

	Amplitude* amplitude = new Amplitude(Reader.GetSampleRate(), fftPtr);
	Spectre* spectre = new Spectre(Reader.GetSampleRate(), fftPtr);
	Rave* rave = new Rave(Reader.GetSampleRate(), fftPtr);
	Alisa* alisa = new Alisa(Reader.GetSampleRate(), fftPtr);
	
	//список вкл/откл отрисовки, хранит моды в порядке добавления
	vector<AbstractMode*> avaliableModes;
	avaliableModes.push_back(amplitude);

	//AuidioProcessor читает музыку в audio

	//audio передается в обработчик FFT
 
	sf::Clock clock;
	float prevTime = 0;


	//setting background
	sf::Texture textureBg;
	textureBg.loadFromFile(bgPic);
	sf::Sprite background;
	background.setPosition(0,0);
	float scaleX = 2160. / 3840.;
	float scaleY = 1440. / 2160.;
	cout << scaleX << " " << scaleY << '\n';
	background.setScale({scaleX, scaleY});
	background.setTexture(textureBg);
	//background.setScale(1.01 * WIDTH / 1920, 1.01 * HEIGHT / 1080);

	while(window.isOpen()) {
		// float time = clock.getElapsedTime().asMilliseconds();
		// clock.restart();
		// cout << time << endl;
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
				} else if (event.key.code == sf::Keyboard::Num3) {
					auto it = find(avaliableModes.begin(), avaliableModes.end(), rave);

					if (it != avaliableModes.end()) {
						avaliableModes.erase(it);
					} else {
						avaliableModes.push_back(rave);
					}
				} else if (event.key.code == sf::Keyboard::Num4) {
					auto it = find(avaliableModes.begin(), avaliableModes.end(), alisa);

					if (it != avaliableModes.end()) {
						avaliableModes.erase(it);
					} else {
						avaliableModes.push_back(alisa);
					}
				}
			}
		}

		if (data.empty()) {
			data = Reader.Read(fftPtr->GetReadSize());
		} else {
			auto tmp = Reader.Read();
			data.insert(data.end(), tmp.begin(), tmp.end());
			data.erase(data.begin(), data.begin() + tmp.size());
		}

		fftPtr->Calculate(data);

		window.clear();
		window.draw(background);
		RectangleShape darkrect({WIDTH, HEIGHT});
		darkrect.setFillColor(sf::Color(1, 1, 1, 240));
		window.draw(darkrect);
		//у всех включенных модов вызывается апдейт и отрисовка
		for (auto& mode : avaliableModes) {
			mode->update(data);
			mode->draw(window);
		}
		window.display();
	}
}
