#include "Spectre.h"

using namespace sf;

Spectre::Spectre(const vector<double>& audio_in, double sample_rate_audio, int sample_rate_fft)
    : AbstractMode(audio_in, sample_rate_audio, sample_rate_fft) {    
    fft.LazyInit(sample_rate_audio);
}

void Spectre::update() {
    //fft щас вызову уххх бля
    //rectH[i] = fft.out[i] * const;
    auto audio_spectre = fft.Calculate(audio);
    rectH.resize(audio_spectre->size());
    for (int i = 0; i < audio_spectre->size(); ++i) {
        double re = (*audio_spectre)[i].real();
        double im = (*audio_spectre)[i].imag();
        rectH[i] = sqrt(re * re + im * im);
    }
    //каждый раз высота обновляется

}

void Spectre::draw(RenderWindow& window) {
    for (int i = 0; i < rectH.size(); ++i) {
        RectangleShape rect(Vector2f(10, rectH[i]));
        rect.setFillColor(sf::Color::White);
        rect.setPosition(Vector2f(i * 7, HEIGHT - rectH[i]));
        window.draw(rect);
    }
}