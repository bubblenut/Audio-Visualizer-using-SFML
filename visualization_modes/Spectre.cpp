#include "Spectre.h"

using namespace sf;

Spectre::Spectre(double sample_rate_audio)
    : AbstractMode(sample_rate_audio) {    
    fft.LazyInit(sample_rate_audio);
}

void Spectre::update(vector<double>& audio_in) {
    auto audio_spectre = fft.Calculate(audio_in);
    rectH.resize(audio_spectre->size());
    for (size_t i = 0; i < audio_spectre->size(); ++i) {
        double re = (*audio_spectre)[i].real();
        double im = (*audio_spectre)[i].imag();
        double h = sqrt(re * re + im * im);
        //double normalizedH = 2 / (2 + pow(M_E, -1 * h));
        double normalizedH = log10(max(h, 0.));
        rectH[i] = normalizedH * 250;

        //rectH[i] = min(1000., h);
    }
}

void Spectre::draw(RenderWindow& window) {

    // sf::Shader effect;
    // effect.loadFromFile("bloom.glsl", sf::Shader::Fragment);

    double W = WIDTH / static_cast<double>(rectH.size() - 5000) / 2;
    int colorJump = static_cast<int>((rectH.size() - 2000) / 256);

    //левая половина
    for (size_t i = 0; i < (rectH.size() - 5000); ++i) {
        RectangleShape rect(Vector2f(3.5, 3.5));

        rect.setFillColor(Color::White);
        //на какую высоту от низа экрана надо обрезать спектр
        float lowBorder = 130;
        float rectX = i * W;
        float rectY = min(static_cast<double>(HEIGHT - lowBorder), HEIGHT * 3 / 4 - rectH[i]);
        rect.setPosition(Vector2f(rectX, rectY));
        if (i % 2 == 0) {
            rect.setFillColor(sf::Color(i / colorJump, 0 , 255 - i / colorJump));
        } else {
            rect.setFillColor(sf::Color(i / colorJump, 100 , 255 - i / colorJump, 150));
        }
        RectangleShape rectSym(rect);
        rectSym.setPosition(WIDTH - rectX, rectY);
        window.draw(rect);
        window.draw(rectSym);
    }
}
