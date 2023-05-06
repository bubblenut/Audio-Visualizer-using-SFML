#include "Spectre.h"

using namespace sf;

Spectre::Spectre(double sample_rate_audio)
    : AbstractMode(sample_rate_audio) {    
    fft.LazyInit(sample_rate_audio);
}

void Spectre::update(vector<double>& audio_in) {
    //fft щас вызову уххх бля
    //rectH[i] = fft.out[i] * const;
    auto audio_spectre = fft.Calculate(audio_in);
    rectH.resize(audio_spectre->size());
    for (int i = 0; i < audio_spectre->size(); ++i) {
        double re = (*audio_spectre)[i].real();
        double im = (*audio_spectre)[i].imag();
        rectH[i] = sqrt(re * re + im * im);
    }
    //каждый раз высота обновляется

}

void Spectre::draw(RenderWindow& window) {
    double W = WIDTH / static_cast<double>(rectH.size());
    for (int i = 20; i < rectH.size(); ++i) {
        RectangleShape rect(Vector2f(W - 3, rectH[i]));
        rect.setFillColor(sf::Color::White);
        rect.setPosition(Vector2f(i * W, HEIGHT - rectH[i]));
        window.draw(rect);
    }
}