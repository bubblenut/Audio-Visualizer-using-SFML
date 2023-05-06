#include "Visualizer.h"

using namespace std;
using namespace sf;

Visualizer::Visualizer() {
    ContextSettings settings;
	settings.antialiasingLevel = 4;
	
	const VideoMode desktop = VideoMode::getDesktopMode();
	window.create(VideoMode(WIDTH, HEIGHT, desktop.bitsPerPixel), "Visualizrr",Style::Default, settings);
	window.setFramerateLimit(FPS);
}

void::Visualizer::run() {

	//создается AuidioProcessor, FFT, базовый Mode
	//fft.lazy_init();
	//AuidioProcessor читает музыку в audio

	//audio передается в обработчик FFT
 
	while(window.isOpen()) {
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
				return;
        }

	//FFT принимает находит нужный фрагмент аудио и начинает обрабатыввать его

	//FFT возвращает обработанные данные в любой Mode

	//Mode отрисовывает обработанные данные согласно своим настройкам, вызывает перегруженный draw

		window.clear();
		mode->update();
		mode->draw(window);
		window.display();
	}
}