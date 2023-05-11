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
        rectH[i] = log(sqrt(re * re + im * im)) * 100;

    }    
}

void Spectre::draw(RenderWindow& window) {
    double W = WIDTH / static_cast<double>(rectH.size() - 5000);
    int colorJump = static_cast<int>((rectH.size() - 500) / 256);
    for (size_t i = 0; i < rectH.size() - 5000; ++i) {
        RectangleShape rect(Vector2f(W - 3, W - 3));
        rect.setFillColor(Color::White);
        rect.setPosition(Vector2f(i * W, HEIGHT * 7 / 8 - rectH[i]));
        if (i % 2 == 0) {
            rect.setFillColor(sf::Color(i / colorJump, 0 , 255 - i / colorJump));
        } else {
            rect.setFillColor(sf::Color(i / colorJump, 100 , 255 - i / colorJump, 150));
        }
        window.draw(rect);
    }
}
